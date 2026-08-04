#include "TIM1.h"

void TIM1_Init_(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    //开启中断所需时钟
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    //AFR[1]表示引脚15所在的AFR（0-7为[0]），左移28位表示PB15
    GPIOB->AFR[1] |= GPIO_AF_TIM1 << 28;
    GPIOB->MODER |= GPIO_MODER_MODER15_1;
    GPIOB->MODER &= ~GPIO_MODER_MODER15_0;
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT_15;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR15_0;
    GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR15_1;
    GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR15_0 | GPIO_OSPEEDER_OSPEEDR15_1;

    //计数方向
    TIM1->CR1 &= ~TIM_CR1_DIR;

    //频率168Mhz/16800=10000hz，周期100us，计数周期为1s
    TIM1->PSC = 16800 - 1;
    TIM1->ARR = 10000 - 1;

    //通道3的CCR值
    TIM1->CCR3 = 5000;

    //配置通道3为输出比较
    TIM1->CCMR2 &= ~TIM_CCMR2_CC3S;

    //通道3比较模式,110
    TIM1->CCMR2 |= TIM_CCMR2_OC3M_2;
    TIM1->CCMR2 |= TIM_CCMR2_OC3M_1;
    TIM1->CCMR2 &= ~TIM_CCMR2_OC3M_0;

    //通道3高电平有效
    TIM1->CCER &= ~TIM_CCER_CC3P;

    // 设置5次PWM
    TIM1->RCR = 5 - 1;

    //使能通道3和补偿输出通道(坑在LCD背光是被补偿输出控制的)
    TIM1->CCER |= TIM_CCER_CC3E;
    TIM1->CCER |= TIM_CCER_CC3NE;

    // 将以上配置刷新进定时器
    TIM1->EGR |= TIM_EGR_UG;

    // 重要！如果不手动清除，会导致后面立马进中断
    TIM1->SR &= ~TIM_SR_UIF;

    // 打开中断
    TIM1->DIER |= TIM_DIER_UIE;

    //使能定时器
    TIM1->CR1 |= TIM_CR1_CEN;
    TIM1->BDTR |= TIM_BDTR_MOE;

    //设置分组，从011->100->101->110->111，分别为xxxx,xxx.y,xx.yy,x.yyy,yyyy
    SCB->AIRCR &= ~SCB_AIRCR_PRIGROUP_Msk;
    SCB->AIRCR |= 3U << 8;
    //设置优先级1111
    NVIC->IP[TIM1_UP_TIM10_IRQn] |= 15 << 4;
    //ISER寄存器为32位，因此将序号右移5位为除以32，确定在哪个寄存器，后面则是取低5位，将对应序号的使能位置1
    NVIC->ISER[(((uint32_t)(int32_t)TIM1_UP_TIM10_IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)TIM1_UP_TIM10_IRQn) & 0x1FUL));
}

void TIM1_SetDutyCycle(uint8_t dutycycle)
{
    TIM1->CCR3 = dutycycle;
}

void TIM1_UP_TIM10_IRQHandler(void)
{
    if (TIM1->SR & TIM_SR_UIF)
    {
        TIM1->SR &= ~TIM_SR_UIF;
        TIM1->CR1 &= ~TIM_CR1_CEN;
    }
}
