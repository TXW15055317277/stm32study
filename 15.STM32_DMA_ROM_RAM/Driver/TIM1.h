#ifndef __TIM1_H
#define __TIM1_H

#include "stm32f4xx.h"
#include <stdio.h>

void TIM1_Init_(void);
void TIM1_SetDutyCycle(uint8_t dutycycle);
void TIM1_UP_TIM10_IRQHandler(void);

#endif
