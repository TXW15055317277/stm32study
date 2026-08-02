#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"

#define LED_GREEN GPIO_ODR_ODR_10
#define LED_RED GPIO_ODR_ODR_9

void LED_Init(void);
void LED_ON(uint16_t LED);
void LED_OFF(uint16_t LED);
void LED_Toggle(uint16_t LED);
void LED_ON_ALL(uint16_t LEDs[], uint8_t size);
void LED_OFF_ALL(uint16_t LEDs[], uint8_t size);

#endif
