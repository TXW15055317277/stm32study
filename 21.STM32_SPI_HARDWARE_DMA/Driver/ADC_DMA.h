#ifndef __ADC_DMA_H
#define __ADC_DMA_H

#include "stm32f4xx.h"
#include "USART.h"
#include "stdio.h"

void ADC_MULTI_Init_(void);
void ADC_MULTI_START_(void);
void DMA2_Stream0_IRQHandler(void);

#endif
