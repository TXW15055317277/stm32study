#ifndef __M24C02_H
#define __M24C02_H

#include "I2C.h"

#define W_ADDR 0xA0
#define R_ADDR 0xA1

extern uint8_t buffer[100];
extern uint8_t size;

void EEPROM_Init(void);
void EEPROM_WriteByte(uint8_t addr, uint8_t byte);
uint8_t EEPROM_ReadByte(uint8_t addr);
void EEPROM_WriteBytes(uint8_t addr, uint8_t * bytes, uint8_t size);
void EEPROM_ReadBytes(uint8_t addr, uint8_t * buffer, uint8_t size);

#endif
