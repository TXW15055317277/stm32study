#include "ADC.h"

extern uint16_t data[1];

void ADC_SINGLE_Init_(void)
{
    // 开启时钟
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    
    // 模拟输入模式
    GPIOA->MODER |= GPIO_MODER_MODER5;

    // ADC预分频，最高36，这里为4分频，84/4=21Mhz
    ADC->CCR |= ADC_CCR_ADCPRE_0;
    ADC->CCR |= ADC_CCR_ADCPRE_1;

    // 选择看门狗通道5
    ADC1->CR1 &= ~ADC_CR1_AWDCH_4;
    ADC1->CR1 &= ~ADC_CR1_AWDCH_3;
    ADC1->CR1 |= ADC_CR1_AWDCH_2;
    ADC1->CR1 &= ~ADC_CR1_AWDCH_1;
    ADC1->CR1 |= ADC_CR1_AWDCH_0;

    // 关闭扫描模式，选择12位分辨率
    ADC1->CR1 &= ~ADC_CR1_SCAN;
    ADC1->CR1 &= ~ADC_CR1_RES;
    
    // 循环模式
    ADC1->CR2 |= ADC_CR2_CONT;

    // 每个通道完成EOC置1
    ADC1->CR2 &= ~ADC_CR2_EOCS;

    // 数据右对齐
    ADC1->CR2 &= ~ADC_CR2_ALIGN;

    // 禁止触发检测
    ADC1->CR2 &= ~ADC_CR2_EXTEN;

    // 采样时间
    ADC1->SMPR2 &= ~ADC_SMPR2_SMP5;
    ADC1->SMPR2 |= ADC_SMPR2_SMP5_0;

    // 设为0，表示只有一个通道
    ADC1->SQR1 &= ~ADC_SQR1_L;

    // 第一个扫描设置为通道5
    ADC1->SQR3 &= ADC_SQR3_SQ1;
    ADC1->SQR3 |= 5 << 0;

    // 使能DMA以及EOC中断
    ADC1->CR2 |= ADC_CR2_DMA;
    ADC1->CR2 |= ADC_CR2_DDS;
    USART1->CR3 |= USART_CR3_DMAR;
    USART1->CR3 |= USART_CR3_DMAT;
    ADC1->CR1 |= ADC_CR1_EOCIE;

    // DMA相关
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    // 传输完成使能
    DMA2_Stream0->CR |= DMA_SxCR_TCIE;

    // 外设到存储器，这里把串口当作存储器
    DMA2_Stream0->CR &= DMA_SxCR_DIR;

    // 循环模式
    DMA2_Stream0->CR |= DMA_SxCR_CIRC;

    // 外设地址不变，内存地址+1
    DMA2_Stream0->CR &= ~DMA_SxCR_PINC;
    DMA2_Stream0->CR |= DMA_SxCR_MINC;

    // 数据大小设置为半字
    DMA2_Stream0->CR |= DMA_SxCR_PSIZE_0;
    DMA2_Stream0->CR &= ~DMA_SxCR_PSIZE_1;
    DMA2_Stream0->CR |= DMA_SxCR_MSIZE_0;
    DMA2_Stream0->CR &= ~DMA_SxCR_MSIZE_1;

    // 优先级最高
    DMA2_Stream0->CR |= DMA_SxCR_PL;

    // 选择通道0
    DMA2_Stream0->CR &= ~DMA_SxCR_CHSEL;

    //设置分组，从011->100->101->110->111，分别为xxxx,xxx.y,xx.yy,x.yyy,yyyy
    SCB->AIRCR &= ~SCB_AIRCR_PRIGROUP_Msk;
    SCB->AIRCR |= 3U << 8;
    //设置优先级1111
    NVIC->IP[DMA2_Stream0_IRQn] |= 15 << 4;
    //ISER寄存器为32位，因此将序号右移5位为除以32，确定在哪个寄存器，后面则是取低5位，将对应序号的使能位置1
    NVIC->ISER[(((uint32_t)(int32_t)DMA2_Stream0_IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)DMA2_Stream0_IRQn) & 0x1FUL));

}

void ADC_SINGLE_START_(void)
{
    ADC1->CR2 |= ADC_CR2_ADON;
    ADC1->CR2 |= ADC_CR2_SWSTART;
    // 指定外设
    DMA2_Stream0->PAR = (uint32_t)&(ADC1->DR);
    // RAM地址
    DMA2_Stream0->M0AR = (uint32_t)&data;
    // 传输多少数据
    DMA2_Stream0->NDTR = 1;
    // 使能DMA，立即开始传输
    DMA2_Stream0->CR |= DMA_SxCR_EN;
}

void DMA2_Stream0_IRQHandler(void)
{
    if ((DMA2->LISR & DMA_LISR_TCIF0) != 0)
    {
        DMA2->LIFCR |= DMA_LIFCR_CTCIF0;
    }
}
