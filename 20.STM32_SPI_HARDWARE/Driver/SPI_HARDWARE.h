#ifndef SPI_HARDWARE_H
#define SPI_HARDWARE_H

#include "stm32f4xx.h"
#include <stdio.h>

void SPI_HARD_Init_(void);
// 一定要先写后读，否则会卡在第一次发送的RXNE上面，刚开始RXNE就是没有值，因此一直为0
uint8_t SPI_HARD_SWAP(uint8_t Byte);
void SPI_HARD_START(void);
void SPI_HARD_STOP(void);

#endif
