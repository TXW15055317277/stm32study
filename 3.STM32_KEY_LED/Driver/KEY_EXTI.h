#ifndef __KEY_EXTI_H
#define __KEY_EXTI_H

#include "stm32f4xx.h"

void KEY_EXTI_Init(void);
void EXTI0_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI2_IRQHandler(void);

#endif
