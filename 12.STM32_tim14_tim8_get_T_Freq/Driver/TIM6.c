#include "TIM6.h"

volatile uint32_t Count = 0;

void TIM6_Init_(void)
{
    //开启中断所需时钟
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    //开启tim6时钟
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

    //APB1分频系数为4，因此为168/4×2=84Mhz,这样tim6频率为1000000hz
    TIM6->PSC = 84 - 1;

    //选择计数值为1000-1,这样每1ms产生一个中断
    TIM6->ARR = 1000 - 1;

    //开启中断使能
    TIM6->DIER |= TIM_DIER_UIE;

    //设置分组，从011->100->101->110->111，分别为xxxx,xxx.y,xx.yy,x.yyy,yyyy
    SCB->AIRCR &= ~SCB_AIRCR_PRIGROUP_Msk;
    SCB->AIRCR |= 3U << 8;

    //设置优先级1111
    NVIC->IP[TIM6_DAC_IRQn] |= 15 << 4;
    //ISER寄存器为32位，因此将序号右移5位为除以32，确定在哪个寄存器，后面则是取低5位，将对应序号的使能位置1
    NVIC->ISER[(((uint32_t)(int32_t)TIM6_DAC_IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)TIM6_DAC_IRQn) & 0x1FUL));

    //开启tim6
    TIM6->CR1 |= TIM_CR1_CEN;

    Count = 0;
}

void TIM6_delay_ms(uint16_t ms)
{
    Count = 0;
    while(Count < ms)
    {}
}

void TIM6_delay_s(uint16_t s)
{
    while(s--)
    {
        TIM6_delay_ms(1000);
    }
}

void TIM6_DAC_IRQHandler(void)
{
    TIM6->SR &= ~TIM_SR_UIF;
    printf("Count = %d", Count);
    Count++;
}
