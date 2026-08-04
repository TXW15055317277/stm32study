#ifndef __TIM8_H
#define __TIM8_H

#include "stm32f4xx.h"
#include <stdio.h>

void TIM8_Init_(void);
double TIM8_Get_T(void);
double TIM8_Get_Freq(void);
double TIM8_Get_DutyCycle(void);

#endif
