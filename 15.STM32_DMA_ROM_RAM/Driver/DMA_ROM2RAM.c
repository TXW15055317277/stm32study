#include "DMA_ROM2RAM.h"

extern uint8_t TCFLAG;

void DMA_ROM2RAM_Init_(void)
{
    // 打开DMA时钟
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    // 打开传输完成中断
    DMA2_Stream0->CR |= DMA_SxCR_TCIE;
    // 选择传输方向存储器到存储器
    DMA2_Stream0->CR |= DMA_SxCR_DIR_1;
    DMA2_Stream0->CR &= ~DMA_SxCR_DIR_0;
    // 存储器地址递增
    DMA2_Stream0->CR |= DMA_SxCR_PINC;
    DMA2_Stream0->CR |= DMA_SxCR_MINC;
    // 存储器字长8位
    DMA2_Stream0->CR &= ~DMA_SxCR_PSIZE;
    DMA2_Stream0->CR &= ~DMA_SxCR_MSIZE;
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

void DMA_ROM2RAM_T(uint32_t paddr, uint32_t maddr, uint32_t size)
{
    // 指定ROM地址
    DMA2_Stream0->PAR = paddr;
    // RAM地址
    DMA2_Stream0->M0AR = maddr;
    // 传输多少数据
    DMA2_Stream0->NDTR = size;
    // 使能DMA，立即开始传输
    DMA2_Stream0->CR |= DMA_SxCR_EN;
}

void DMA2_Stream0_IRQHandler(void)
{
    if ((DMA2->LISR & DMA_LISR_TCIF0) != 0)
    {
        DMA2->LIFCR |= DMA_LIFCR_CTCIF0;
        TCFLAG = 1;
        DMA2_Stream0->CR &= ~DMA_SxCR_EN;
    }
}
