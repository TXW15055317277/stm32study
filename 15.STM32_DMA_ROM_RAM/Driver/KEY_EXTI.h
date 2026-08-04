#ifndef __KEY_EXTI_H
#define __KEY_EXTI_H

#include "stm32f4xx.h"
#include "TIM1.h"
#include "DELAY.h"
#include "LED.h"
#include <stdio.h>

extern uint8_t dutycycle;

void KEY_EXTI_Init(void);
void EXTI0_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI3_IRQHandler(void);

#endif
