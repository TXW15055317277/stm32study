#ifndef __DMA_ROM2RAM_H
#define __DMA_ROM2RAM_H

#include "stm32f4xx.h"

void DMA_ROM2RAM_Init_(void);
void DMA_ROM2RAM_T(uint32_t paddr, uint32_t maddr, uint32_t size);
void DMA2_Stream0_IRQHandler(void);

#endif
