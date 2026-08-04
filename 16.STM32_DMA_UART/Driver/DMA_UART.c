#include "DMA_UART.h"
extern uint8_t rece[1];

void DMA_UART_Init_(void)
{
    // 打开DMA时钟
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    // 中断时钟
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // 打开传输完成中断
    DMA2_Stream7->CR |= DMA_SxCR_TCIE;
    // 选择传输方向存储器到外设（01，TX）
    DMA2_Stream7->CR |= DMA_SxCR_DIR_0;
    DMA2_Stream7->CR &= ~DMA_SxCR_DIR_1;
    // 存储器地址递增,串口地址不变
    DMA2_Stream7->CR &= ~DMA_SxCR_PINC;
    DMA2_Stream7->CR |= DMA_SxCR_MINC;
    // 存储器字长8位
    DMA2_Stream7->CR &= ~DMA_SxCR_PSIZE;
    DMA2_Stream7->CR &= ~DMA_SxCR_MSIZE;
    // 优先级最高
    DMA2_Stream7->CR |= DMA_SxCR_PL;
    // 选择通道4
    DMA2_Stream7->CR &= ~DMA_SxCR_CHSEL_0;
    DMA2_Stream7->CR &= ~DMA_SxCR_CHSEL_1;
    DMA2_Stream7->CR |= DMA_SxCR_CHSEL_2;

    // 打开传输完成中断
    DMA2_Stream5->CR |= DMA_SxCR_TCIE;
    // 选择传输方向外设到存储器（00，RX）
    DMA2_Stream5->CR &= ~DMA_SxCR_DIR_0;
    DMA2_Stream5->CR &= ~DMA_SxCR_DIR_1;
    // 存储器地址递增，串口位置不变
    DMA2_Stream5->CR &= ~DMA_SxCR_PINC;
    DMA2_Stream5->CR |= DMA_SxCR_MINC;
    // 存储器字长8位
    DMA2_Stream5->CR &= ~DMA_SxCR_PSIZE;
    DMA2_Stream5->CR &= ~DMA_SxCR_MSIZE;
    // 优先级最高
    DMA2_Stream5->CR |= DMA_SxCR_PL;
    // 循环模式
    DMA2_Stream5->CR |= DMA_SxCR_CIRC;
    // 选择通道4
    DMA2_Stream5->CR &= ~DMA_SxCR_CHSEL_0;
    DMA2_Stream5->CR &= ~DMA_SxCR_CHSEL_1;
    DMA2_Stream5->CR |= DMA_SxCR_CHSEL_2;

    // 串口使能DMA
    USART1->CR3 |= USART_CR3_DMAT;
    USART1->CR3 |= USART_CR3_DMAR;

    //设置分组，从011->100->101->110->111，分别为xxxx,xxx.y,xx.yy,x.yyy,yyyy
    SCB->AIRCR &= ~SCB_AIRCR_PRIGROUP_Msk;
    SCB->AIRCR |= 3U << 8;
    //设置优先级1111
    NVIC->IP[DMA2_Stream7_IRQn] |= 15 << 4;
    //ISER寄存器为32位，因此将序号右移5位为除以32，确定在哪个寄存器，后面则是取低5位，将对应序号的使能位置1
    NVIC->ISER[(((uint32_t)(int32_t)DMA2_Stream7_IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)DMA2_Stream7_IRQn) & 0x1FUL));
    NVIC->IP[DMA2_Stream5_IRQn] |= 15 << 4;
    //ISER寄存器为32位，因此将序号右移5位为除以32，确定在哪个寄存器，后面则是取低5位，将对应序号的使能位置1
    NVIC->ISER[(((uint32_t)(int32_t)DMA2_Stream5_IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)DMA2_Stream5_IRQn) & 0x1FUL));
}

void DMA_UART_TX(uint32_t maddr, uint32_t paddr, uint32_t size)
{
    // 指定外设
    DMA2_Stream7->PAR = paddr;
    // RAM地址
    DMA2_Stream7->M0AR = maddr;
    // 传输多少数据
    DMA2_Stream7->NDTR = size;
    while ((USART1->SR & USART_SR_TXE) == 0)
    {}
    // 使能DMA，立即开始传输
    DMA2_Stream7->CR |= DMA_SxCR_EN;
}

void DMA_UART_RX(uint32_t paddr, uint32_t maddr, uint32_t size)
{
    // 指定外设
    DMA2_Stream5->PAR = paddr;
    // RAM地址
    DMA2_Stream5->M0AR = maddr;
    // 传输多少数据
    DMA2_Stream5->NDTR = size;
    // 使能DMA，立即开始传输
    DMA2_Stream5->CR |= DMA_SxCR_EN;
}


void DMA2_Stream7_IRQHandler(void)
{
    if ((DMA2->HISR & DMA_HISR_TCIF7) != 0)
    {
        DMA2->HIFCR |= DMA_HIFCR_CTCIF7;
        DMA2_Stream7->CR &= ~DMA_SxCR_EN;
    }
}

void DMA2_Stream5_IRQHandler(void)
{
    if ((DMA2->HISR & DMA_HISR_TCIF5) != 0)
    {

        DMA2->HIFCR |= DMA_HIFCR_CTCIF5;
        printf("%c", rece[0]);
        // DMA2_Stream5->CR &= ~DMA_SxCR_EN;
    }
}
