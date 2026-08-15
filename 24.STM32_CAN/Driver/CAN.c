#include "CAN.h"

void CAN_INIT_(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    GPIOA->AFR[1] |= (uint8_t)GPIO_AF_CAN1 << 12;
    GPIOA->AFR[1] |= (uint8_t)GPIO_AF_CAN1 << 16;
    GPIOA->MODER |= GPIO_MODER_MODER11_1 | GPIO_MODER_MODER12_1;
    GPIOA->MODER &= ~(GPIO_MODER_MODER11_0 | GPIO_MODER_MODER12_0);
    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_11 | GPIO_OTYPER_OT_12);
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR11 | GPIO_OSPEEDER_OSPEEDR12;
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR11 | GPIO_PUPDR_PUPDR12);

    // 初始化CAN1
    CAN1->MCR |= CAN_MCR_INRQ;
    while ((CAN1->MSR & CAN_MSR_INAK) == 0)
    {}
    CAN1->MCR &= ~CAN_MCR_SLEEP;
    while ((CAN1->MSR & CAN_MSR_SLAK) != 0)
    {}
    // 自动离线
    CAN1->MCR |= CAN_MCR_ABOM;
    // 自动唤醒
    CAN1->MCR |= CAN_MCR_AWUM;
    // 优先级由ID决定，不由顺序决定
    CAN1->MCR &= ~CAN_MCR_TXFP;
    //新消息覆盖旧消息
    CAN1->MCR &= ~CAN_MCR_RFLM;
    // 失败重发
    CAN1->MCR &= ~CAN_MCR_NART;
    // BTR时序设置
    CAN1->BTR &= ~CAN_BTR_BRP;
    CAN1->BTR |= 41 << 0;
    // 时间段1设置
    CAN1->BTR &= ~CAN_BTR_TS1;
    CAN1->BTR |= 4 << 16;
    // 时间段2
    CAN1->BTR &= ~CAN_BTR_TS2;
    CAN1->BTR |= 3 << 20;
    // 静默环回
    CAN1->BTR |= CAN_BTR_SILM | CAN_BTR_LBKM;
    // 退出初始化
    CAN1->MCR &= ~CAN_MCR_INRQ;
    while ((CAN1->MSR & CAN_MSR_INAK) != 0)
    {}
}

void CAN_TXMsg_(uint16_t ID, uint8_t data_len, uint8_t *data)
{
    while ((CAN1->TSR & CAN_TSR_TME0) == 0)
    {}
    
    CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_RTR;
    CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_IDE;
    CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_STID;
    CAN1->sTxMailBox[0].TIR |= (uint16_t)ID << 21;
    CAN1->sTxMailBox[0].TDTR &= ~CAN_TDT0R_DLC;
    CAN1->sTxMailBox[0].TDTR |= data_len;
    CAN1->sTxMailBox[0].TDTR &= ~CAN_TDT0R_TGT;
    CAN1->sTxMailBox[0].TDLR = 0;
    CAN1->sTxMailBox[0].TDHR = 0;
    for (uint8_t i = 0; i < data_len; i++)
    {
        if (i < 4)
        {
            CAN1->sTxMailBox[0].TDLR |= (uint32_t)*data++ << i * 8;
        }
        else
        {
            CAN1->sTxMailBox[0].TDHR |= (uint32_t)*data++ << (i - 4) * 8;
        }
    }
    CAN1->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ;
    while ((CAN1->TSR & CAN_TSR_TXOK0) == 0)
    {}
}

void CAN_RXMsg_(Msg_ *Msg_RX, uint8_t *data_num)
{

    *data_num = (uint8_t)(CAN1->RF0R & CAN_RF0R_FMP0);
    for (uint8_t i = 0; i < *data_num; i++)
    {
        Msg_RX->ID = ((CAN1->sFIFOMailBox[0].RIR >> 21) & 0x07FF);
        Msg_RX->data_len = (uint8_t)(CAN1->sFIFOMailBox->RDTR & CAN_RDT0R_DLC);
        for (uint8_t j = 0; j < Msg_RX->data_len; j++)
            if (j < 4)
            {
                Msg_RX->data[j] = ((CAN1->sFIFOMailBox[0].RDLR >> j * 8) & 0xFF);
            }
            else
            {
                Msg_RX->data[j] = ((CAN1->sFIFOMailBox[0].RDHR >> (j - 4) * 8) & 0xFF);
            }
        CAN1->RF0R |= CAN_RF0R_RFOM0;
        Msg_RX++;
    }
}

void CAN_Filter_Init_(void)
{
    // 进入初始化
    CAN1->FMR |= CAN_FMR_FINIT;
    // 筛选器0选择屏蔽模式
    CAN1->FM1R &= ~CAN_FM1R_FBM0;
    // 选择一个32位过滤器
    CAN1->FS1R |= CAN_FS1R_FSC0;
    // 过滤器通过的分配到FIFO0
    CAN1->FFA1R &= ~CAN_FFA1R_FFA0;
    // FR1为希望的ID值，FR2为哪一位需要一致
    // 注意的是，高位11位才是标准ID，且也有IDE和RTR需要配置
    CAN1->sFilterRegister[0].FR1 = (uint32_t)0x00000010 << 21;
    CAN1->sFilterRegister[0].FR1 &= ~(1 << 1);
    CAN1->sFilterRegister[0].FR1 &= ~(1 << 2);
    CAN1->sFilterRegister[0].FR2 = (uint32_t)0x00000010<< 21;
    // 筛选器激活
    CAN1->FA1R |= CAN_FA1R_FACT0;
    // 过滤器工作
    CAN1->FMR &= ~CAN_FMR_FINIT;
}
