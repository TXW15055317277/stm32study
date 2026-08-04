#include "TIM14.h"

void TIM14_Init_(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;

    //AFR[1]表示引脚9所在的AFR（0-7为[0]），左移4位表示PF9
    GPIOF->AFR[1] |= GPIO_AF_TIM14 << 4;
    GPIOF->MODER |= GPIO_MODER_MODER9_1;
    GPIOF->MODER &= ~GPIO_MODER_MODER9_0;
    GPIOF->OTYPER &= ~GPIO_OTYPER_OT_9;
    GPIOF->PUPDR |= GPIO_PUPDR_PUPDR9_0;
    GPIOF->PUPDR &= ~GPIO_PUPDR_PUPDR9_1;
    GPIOF->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_0 | GPIO_OSPEEDER_OSPEEDR9_1;

    //频率84Mhz/84=1000000hz，周期1us，计数周期为100us
    TIM14->PSC = 84 - 1;
    TIM14->ARR = 100 - 1;

    //通道1的CCR值
    TIM14->CCR1 = 50;

    //配置通道1为输出比较
    TIM14->CCMR1 &= ~TIM_CCMR1_CC1S;

    //通道1比较模式,110
    TIM14->CCMR1 |= TIM_CCMR1_OC1M_2;
    TIM14->CCMR1 |= TIM_CCMR1_OC1M_1;
    TIM14->CCMR1 &= ~TIM_CCMR1_OC1M_0;

    //通道1低电平有效
    TIM14->CCER |= TIM_CCER_CC1P;

    //使能通道1
    TIM14->CCER |= TIM_CCER_CC1E;

    //使能定时器
    TIM14->CR1 |= TIM_CR1_CEN;
}

void TIM14_SetDutyCycle(uint8_t dutycycle)
{
    TIM14->CCR1 = dutycycle;
}
