#ifndef __TIM6_H
#define __TIM6_H

#include "stm32f4xx.h"
#include <stdio.h>

void TIM6_Init_(void);
void TIM6_delay_ms(uint16_t ms);
void TIM6_delay_s(uint16_t s);
void TIM6_DAC_IRQHandler(void);

#endif
