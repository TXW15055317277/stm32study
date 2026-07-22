#include "KEY.h"
#include "DELAY.h"

void KEY_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    GPIOA->MODER &= ~GPIO_MODER_MODER0;
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0;
    GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_1;
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR0_0;
    GPIOE->MODER &= ~GPIO_MODER_MODER4;
    GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4;
    GPIOE->PUPDR |= GPIO_PUPDR_PUPDR4_0;
    GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR4_1;
    GPIOE->MODER &= ~GPIO_MODER_MODER3;
    GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3;
    GPIOE->PUPDR |= GPIO_PUPDR_PUPDR3_0;
    GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR3_1;
    GPIOE->MODER &= ~GPIO_MODER_MODER2;
    GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2;
    GPIOE->PUPDR |= GPIO_PUPDR_PUPDR2_0;
    GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR2_1;
}

uint8_t KEY_Scan(uint32_t KEY)
{
    uint8_t KEY_NUM = 0;
    if (KEY == WK_UP)
    {
        if ((GPIOA->IDR & WK_UP) == 0)
        {}
        else
        {
            delay_ms(20);
            if ((GPIOA->IDR & WK_UP) != 0)
            {
                while((GPIOA->IDR & WK_UP) != 0)
                KEY_NUM = 1;
            }
        }
    }
    else
    {
        if ((GPIOE->IDR & KEY) == 0)
        {            
            delay_ms(20);
            if ((GPIOE->IDR & KEY) == 0)
            {
                while((GPIOE->IDR & KEY) == 0)
                KEY_NUM = 1;
            }
        }
        else
        {}
    }
    return KEY_NUM;
}
