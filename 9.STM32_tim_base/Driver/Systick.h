#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f4xx.h"

void Systick_Init_(void);
void SysTick_delay_us(uint32_t us);
void SysTick_delay_ms(uint32_t ms);
void SysTick_delay_s(uint32_t s);
void SysTick_Handler(void);

#endif
