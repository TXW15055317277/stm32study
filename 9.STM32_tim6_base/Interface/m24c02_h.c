#include "m24c02_h.h"
#include "DELAY.h"

void EEPROM_Init(void)
{
    I2C_Init_H();
}

void EEPROM_WriteByte(uint8_t addr, uint8_t byte)
{
    if (I2C_Start_H() == OK)
    {
        if (I2C_SendAddr_H(W_ADDR) == OK)
        {
            if (I2C_SendByte_H(addr) == OK)
            {
                if (I2C_SendByte_H(byte) == OK)
                {
                    I2C_Stop_H();
                    delay_ms(5);
                }
            }
        }
    }
}

uint8_t EEPROM_ReadByte(uint8_t addr)
{
    uint8_t byte;
    if (I2C_Start_H() == OK)
    {
        if (I2C_SendAddr_H(W_ADDR) == OK)
        {
            if (I2C_SendByte_H(addr) == OK)
            {
                if (I2C_Start_H() == OK)
                {
                    if (I2C_SendAddr_H(R_ADDR) == OK)
                    {
                        I2C_NACK_H();
                        I2C_Stop_H();
                        byte = I2C_ReadByte_H();
                    }
                }
            }
        }
    }
    return byte;
}

void EEPROM_WriteBytes(uint8_t addr, uint8_t * bytes, uint8_t size)
{
    uint8_t i = 0;
    if (I2C_Start_H() == OK)
    {
        if (I2C_SendAddr_H(W_ADDR) == OK)
        {
            if (I2C_SendByte_H(addr) == OK)
            {
                for (i = 0; i < size; i++)
                {
                    I2C_SendByte_H(bytes[i]);
                }
                I2C_Stop_H();
                delay_ms(5);
            }
        }
    }
}
void EEPROM_ReadBytes(uint8_t addr, uint8_t * buffer, uint8_t size)
{
    uint8_t i = 0;
    if (I2C_Start_H() == OK)
    {
        if (I2C_SendAddr_H(W_ADDR) == OK)
        {
            if (I2C_SendByte_H(addr) == OK)
            {
                if (I2C_Start_H() == OK)
                {
                    if (I2C_SendAddr_H(R_ADDR) == OK)
                    {
                        I2C_ACK_H();
                        for (i = 0; i < size; i++)
                        {
                            if (i >= size - 1)
                            {
                                I2C_NACK_H();
                                I2C_Stop_H();
                            }
                            buffer[i] = I2C_ReadByte_H();
                        }
                    }
                }
            }
        }
    }
}
