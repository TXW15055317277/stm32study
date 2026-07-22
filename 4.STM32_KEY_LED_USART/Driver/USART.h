#ifndef __USART_H
#define __USART_H

#include "stm32f4xx.h"
#include <stdio.h>

void USART_Init_(uint32_t Baudrate);
uint8_t USART_Receive(void);
void USART_Transmit(uint8_t message);
void USART_String_rx(uint8_t buffer[], uint8_t *size);
void USART_String_tx(uint8_t *str, uint8_t size);
int fputc(int ch, FILE *file);

#endif
