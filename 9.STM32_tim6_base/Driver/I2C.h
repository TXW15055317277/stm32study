#ifndef __I2C_H
#define __I2C_H

#include "stm32f4xx.h"
#include "DELAY.h"

#define ACK 0
#define NACK 1

#define SCL_HIGH (GPIOB->ODR |= GPIO_ODR_ODR_8)
#define SCL_LOW (GPIOB->ODR &= ~GPIO_ODR_ODR_8)
#define SDA_HIGH (GPIOB->ODR |= GPIO_ODR_ODR_9)
#define SDA_LOW (GPIOB->ODR &= ~GPIO_ODR_ODR_9)

#define READ_SDA (GPIOB->IDR & GPIO_IDR_IDR_9)

#define I2C_DELAY delay_us(10)

void I2C_Init_(void);
void I2C_START(void);
void I2C_STOP(void);
void I2C_Ack(void);
void I2C_Nack(void);
uint8_t I2C_Wait4ack(void);
void I2C_SendByte(uint8_t Byte);
uint8_t I2C_ReadByte(void);
#endif
