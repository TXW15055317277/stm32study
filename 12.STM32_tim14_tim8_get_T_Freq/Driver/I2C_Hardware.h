#ifndef __I2C_HARDWARE_H
#define __I2C_HARDWARE_H

#include "stm32f4xx.h"

#define OK 0
#define FAIL 1

void I2C_Init_H(void);
uint8_t I2C_Start_H(void);
void I2C_Stop_H(void);
void I2C_ACK_H(void);
void I2C_NACK_H(void);
uint8_t I2C_SendAddr_H(uint8_t addr);
uint8_t I2C_SendByte_H(uint8_t byte);
uint8_t I2C_ReadByte_H(void);

#endif
