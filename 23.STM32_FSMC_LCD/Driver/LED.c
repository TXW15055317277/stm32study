#include "LED.h"


void LED_Init(void)
{
    RCC -> AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
    GPIOF -> MODER |= GPIO_MODER_MODER9_0 | GPIO_MODER_MODER10_0;
    GPIOF -> MODER &= ~ (GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1);
    GPIOF -> OTYPER &= ~ (GPIO_OTYPER_OT_9 | GPIO_OTYPER_OT_10);
    GPIOF -> OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_0 | GPIO_OSPEEDER_OSPEEDR9_1 | GPIO_OSPEEDER_OSPEEDR10_0 | GPIO_OSPEEDER_OSPEEDR10_1;
    GPIOF -> PUPDR &= ~(GPIO_PUPDR_PUPDR9_1 | GPIO_PUPDR_PUPDR10_1);
    GPIOF -> PUPDR |= GPIO_PUPDR_PUPDR9_0 | GPIO_PUPDR_PUPDR10_0;
    LED_OFF(LED_GREEN);
    LED_OFF(LED_RED);
}

void LED_ON(uint16_t LED)
{
    GPIOF->ODR &= ~LED;
}

void LED_OFF(uint16_t LED)
{
    GPIOF->ODR |= LED;
}

void LED_Toggle(uint16_t LED)
{
    if ((GPIOF->ODR & LED) == 0)
    {
        LED_OFF(LED);
    }
    else
    {
        LED_ON(LED);
    }
}

void LED_ON_ALL(uint16_t LEDs[], uint8_t size)
{
    uint8_t i;
    for(i = 0; i < size; i++)
    {
        LED_ON(LEDs[i]);
    }
}

void LED_OFF_ALL(uint16_t LEDs[], uint8_t size)
{
    uint8_t i;
    for(i = 0; i < size; i++)
    {
        LED_OFF(LEDs[i]);
    }
}
