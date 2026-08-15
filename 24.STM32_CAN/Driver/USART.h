#ifndef __USART_H
#define __USART_H

#include "stm32f4xx.h"
#include <stdio.h>
#include "DMA_UART.h"

void USART_Init_(uint32_t Baudrate);
void USART_Transmit(uint8_t message);
void USART_String_tx(uint8_t *str, uint8_t size);
void USART1_IRQHandler(void);
int fputc(int ch, FILE * file);

#endif
