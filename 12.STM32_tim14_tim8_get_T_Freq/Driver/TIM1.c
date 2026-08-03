#include "TIM1.h"

void TIM1_Init_(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

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

    //频率168Mhz/168=1000000hz，周期1us，计数周期为100us
    TIM1->PSC = 168 - 1;
    TIM1->ARR = 100 - 1;

    //通道3的CCR值
    TIM1->CCR3 = 50;

    //配置通道3为输出比较
    TIM1->CCMR2 &= ~TIM_CCMR2_CC3S;

    //通道3比较模式,110
    TIM1->CCMR2 |= TIM_CCMR2_OC3M_2;
    TIM1->CCMR2 |= TIM_CCMR2_OC3M_1;
    TIM1->CCMR2 &= ~TIM_CCMR2_OC3M_0;

    //通道3高电平有效
    TIM1->CCER &= ~TIM_CCER_CC3P;

    //使能通道3和补偿输出通道(坑在LCD背光是被补偿输出控制的)
    TIM1->CCER |= TIM_CCER_CC3E;
    TIM1->CCER |= TIM_CCER_CC3NE;

    //使能定时器
    TIM1->CR1 |= TIM_CR1_CEN;
    TIM1->BDTR |= TIM_BDTR_MOE;
}

void TIM1_SetDutyCycle(uint8_t dutycycle)
{
    TIM1->CCR3 = dutycycle;
}
