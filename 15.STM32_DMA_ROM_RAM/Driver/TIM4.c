#include "TIM4.h"

void TIM4_Init_(void)
{
    // 时钟开启
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    // GPIO复用
    GPIOD->AFR[1] &= ~(0xF << 16);
    GPIOD->AFR[1] |= GPIO_AF_TIM4 << 16;
    GPIOD->MODER |= GPIO_MODER_MODER12_1;
    GPIOD->MODER &= ~GPIO_MODER_MODER12_0;
    GPIOD->OTYPER &= ~GPIO_OTYPER_OT_12;
    GPIOD->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR12;
    GPIOD->PUPDR |= GPIO_PUPDR_PUPDR12_0;
    GPIOD->PUPDR &= GPIO_PUPDR_PUPDR12_1;

    // 定时器配置，预分频系数83，则频率为1Mhz；周期100us，占空比50%
    TIM4->PSC = 84 - 1;
    TIM4->ARR = 100 - 1;
    TIM4->CCR1 = 50;

    // 配置为向上计数
    TIM4->CR1 &= TIM_CR1_DIR;

    // TI1选择
    TIM4->CR2 &= ~TIM_CR2_TI1S;
    
    // 捕获比较模式设置
    TIM4->CCMR1 &= ~TIM_CCMR1_CC1S;
    TIM4->CCMR1 &= ~TIM_CCMR1_OC1M_0;
    TIM4->CCMR1 |= TIM_CCMR1_OC1M_1;
    TIM4->CCMR1 |= TIM_CCMR1_OC1M_2;

    // 使能和极性选择
    TIM4->CCER |= TIM_CCER_CC1E;
    TIM4->CCER &= ~TIM_CCER_CC1P;
    TIM4->CR1 |= TIM_CR1_CEN;
}

void TIM4_SetDutyCycle(uint8_t dutycycle)
{
    TIM4->CCR1 = dutycycle;
}
