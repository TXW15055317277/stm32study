#include "m24c02.h"

void EEPROM_Init(void)
{
    I2C_Init_();
}

void EEPROM_WriteByte(uint8_t addr, uint8_t byte)
{
    uint8_t ack;
    I2C_START();
    I2C_SendByte(W_ADDR);
    ack = I2C_Wait4ack();
    if (ack == ACK)
    {
        I2C_SendByte(addr);
        I2C_Wait4ack();
        I2C_SendByte(byte);
        I2C_Wait4ack();
        I2C_STOP();
    }
    delay_ms(5);
}

uint8_t EEPROM_ReadByte(uint8_t addr)
{
    uint8_t byte;
    I2C_START();
    I2C_SendByte(W_ADDR);
    I2C_Wait4ack();
    I2C_SendByte(addr);
    I2C_Wait4ack();
    I2C_START();
    I2C_SendByte(R_ADDR);
    I2C_Wait4ack();
    byte = I2C_ReadByte();
    I2C_Nack();
    I2C_STOP();
    return byte;
}

void EEPROM_WriteBytes(uint8_t addr, uint8_t * bytes, uint8_t size)
{
    uint8_t i = 0;
    I2C_START();
    I2C_SendByte(W_ADDR);
    I2C_Wait4ack();
    I2C_SendByte(addr);
    I2C_Wait4ack();
    for (i = 0; i < size; i++)
    {
        I2C_SendByte(bytes[i]);
        I2C_Wait4ack();
    }
    I2C_STOP();
    delay_ms(5);
}

void EEPROM_ReadBytes(uint8_t addr, uint8_t * buffer, uint8_t size)
{
    uint8_t i = 0;
    I2C_START();
    I2C_SendByte(W_ADDR);
    I2C_Wait4ack();
    I2C_SendByte(addr);
    I2C_Wait4ack();
    I2C_START();
    I2C_SendByte(R_ADDR);
    I2C_Wait4ack();
    for (i = 0; i < size; i++)
    {
        buffer[i] = I2C_ReadByte();
        if (i < size - 1)
        {
            I2C_Ack();
        }
    }
    I2C_Nack();
    I2C_STOP();
}
