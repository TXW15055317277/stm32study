#ifndef SPI_HARDWARE_H
#define SPI_HARDWARE_H

#include "stm32f4xx.h"
#include <stdio.h>

void SPI_HARD_Init_(void);

void SPI_DMA_START(uint32_t t_maddr, uint32_t r_maddr);
void SPI_HARD_START(void);
void SPI_HARD_STOP(void);

#endif
