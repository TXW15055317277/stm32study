#ifndef __SPI_SOFT_H
#define __SPI_SOFT_H

#include "stm32f4xx.h"
#include "DELAY.h"

#define CS_START (GPIOB->ODR &= ~GPIO_ODR_ODR_14)
#define CS_STOP (GPIOB->ODR |= GPIO_ODR_ODR_14)
#define SCL_HIGH (GPIOB->ODR |= GPIO_ODR_ODR_3)
#define SCL_LOW (GPIOB->ODR &= ~GPIO_ODR_ODR_3)
#define MOSI_HIGH (GPIOB->ODR |= GPIO_ODR_ODR_5)
#define MOSI_LOW (GPIOB->ODR &= ~GPIO_ODR_ODR_5)
#define READ_MISO (GPIOB->IDR & GPIO_IDR_IDR_4)

void SPI_SOFT_Init_(void);
void SPI_SOFT_START(void);
void SPI_SOFT_STOP(void);

uint8_t SPI_SOFT_SWAP(uint8_t Byte);

#endif
