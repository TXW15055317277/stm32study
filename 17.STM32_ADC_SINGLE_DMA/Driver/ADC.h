#ifndef __ADC_H
#define __ADC_H

#include "stm32f4xx.h"
#include "USART.h"
#include "stdio.h"

void ADC_SINGLE_Init_(void);
void ADC_SINGLE_START_(void);
void DMA2_Stream0_IRQHandler(void);

#endif
