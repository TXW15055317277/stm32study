#ifndef __DMA_UART_H
#define __DMA_UART_H

#include "stm32f4xx.h"
#include "USART.h"
#include <stdio.h>

void DMA_UART_Init_(void);
void DMA_UART_TX(uint32_t maddr, uint32_t paddr, uint32_t size);
void DMA_UART_RX(uint32_t paddr, uint32_t maddr, uint32_t size);
void DMA2_Stream7_IRQHandler(void);
void DMA2_Stream5_IRQHandler(void);

#endif
