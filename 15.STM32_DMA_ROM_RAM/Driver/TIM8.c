#include "TIM8.h"

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

    // 从模式选择
    TIM8->SMCR |= TIM_SMCR_SMS_2;
    TIM8->SMCR &= ~TIM_SMCR_SMS_1;
    TIM8->SMCR &= ~TIM_SMCR_SMS_0;
    TIM8->SMCR |= TIM_SMCR_TS_0;
    TIM8->SMCR &= ~TIM_SMCR_TS_1;
    TIM8->SMCR |= TIM_SMCR_TS_2;

    //配置通道1为输入,直连通道TI1
    TIM8->CCMR1 &= ~TIM_CCMR1_CC1S_1;
    TIM8->CCMR1 |= TIM_CCMR1_CC1S_0;

    //通道2输入，选择通道TI1
    TIM8->CCMR1 &= ~TIM_CCMR1_CC2S_0;
    TIM8->CCMR1 |= TIM_CCMR1_CC2S_1;

    //通道1,2预分频
    TIM8->CCMR1 &= ~TIM_CCMR1_IC1PSC;
    TIM8->CCMR1 &= ~TIM_CCMR1_IC2PSC;

    // 滤波器配置
    TIM8->CCMR1 &= ~TIM_CCMR1_IC1F;
    TIM8->CCMR1 &= ~TIM_CCMR1_IC2F;

    //通道1检测上升沿
    TIM8->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC1NP);

    //通道2检测下降沿
    TIM8->CCER &= ~TIM_CCER_CC2NP;
    TIM8->CCER |= TIM_CCER_CC2P;

    //使能定时器
    TIM8->CCER |= TIM_CCER_CC1E;
    TIM8->CCER |= TIM_CCER_CC2E;
    TIM8->CR1 |= TIM_CR1_CEN;
    TIM8->BDTR |= TIM_BDTR_MOE;
}

double TIM8_Get_T(void)
{
    return (double)(TIM8->CCR1 + 1);
}

double TIM8_Get_Freq(void)
{
    return ((TIM8->CCR1) == 0) ? 0.0 : 1000000.0 / (TIM8->CCR1 + 1);
}

double TIM8_Get_DutyCycle(void)
{
    return (TIM8->CCR2 * 1.0 + 1) / (TIM8->CCR1 + 1);
}
