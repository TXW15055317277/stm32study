#include "TIM8.h"

volatile uint32_t now = 0;
volatile uint32_t last = 0;
volatile uint32_t T = 0;

void TIM8_Init_(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;

    //开启中断所需时钟
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    // 配置 PC6 为 TIM8 CH1 输入捕获
    GPIOC->AFR[0] &= ~(0xF << 24);
    GPIOC->AFR[0] |= GPIO_AF_TIM8 << 24;
    GPIOC->MODER |= GPIO_MODER_MODER6_1;
    GPIOC->MODER &= ~GPIO_MODER_MODER6_0;
    GPIOC->OTYPER &= ~GPIO_OTYPER_OT_6;
    GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR6;
    GPIOC->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_0 | GPIO_OSPEEDER_OSPEEDR6_1;

    //计数方向
    TIM8->CR1 &= ~TIM_CR1_DIR;

    // TIM8 在 APB2 上，计数时钟通常为 168MHz，因此 PSC=168-1 可得到 1MHz 计数频率，即 1us 分辨率
    TIM8->PSC = 168 - 1;
    TIM8->ARR = 65535;

    // 配置TI1输入选择
    TIM8->CR2 &= ~TIM_CR2_TI1S;

    //配置通道1为输入,直连通道TI1
    TIM8->CCMR1 &= ~TIM_CCMR1_CC1S_1;
    TIM8->CCMR1 |= TIM_CCMR1_CC1S_0;

    //通道1预分频
    TIM8->CCMR1 &= ~TIM_CCMR1_IC1PSC;

    // 滤波器配置
    TIM8->CCMR1 &= ~TIM_CCMR1_IC1F;

    //通道1检测上升沿
    TIM8->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);

    //中断使能
    TIM8->DIER |= TIM_DIER_CC1IE;

    //使能定时器
    TIM8->CCER |= TIM_CCER_CC1E;
    TIM8->CR1 |= TIM_CR1_CEN;
    TIM8->BDTR |= TIM_BDTR_MOE;

    //设置分组，从011->100->101->110->111，分别为xxxx,xxx.y,xx.yy,x.yyy,yyyy
    SCB->AIRCR &= ~SCB_AIRCR_PRIGROUP_Msk;
    SCB->AIRCR |= 3U << 8;
    //设置优先级1111
    NVIC->IP[TIM8_CC_IRQn] |= 15 << 4;
    //ISER寄存器为32位，因此将序号右移5位为除以32，确定在哪个寄存器，后面则是取低5位，将对应序号的使能位置1
    NVIC->ISER[(((uint32_t)(int32_t)TIM8_CC_IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)TIM8_CC_IRQn) & 0x1FUL));
}

double TIM8_Get_T(void)
{
    return (double)(T);
}

double TIM8_Get_Freq(void)
{
    return (T == 0) ? 0.0 : 1000000.0 / T;
}

void TIM8_CC_IRQHandler(void)
{
    if ((TIM8->SR & TIM_SR_CC1IF) != 0)
    {
        TIM8->SR &= ~TIM_SR_CC1IF;
        now = TIM8->CCR1;
        T = now - last;
        last = now;
    }
}
