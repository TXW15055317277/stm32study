#include "I2C.h"

void I2C_Init_(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    GPIOB->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0;
    GPIOB->MODER &= ~(GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1);
    GPIOB->OTYPER |= GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_9;
    GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8 | GPIO_OSPEEDER_OSPEEDR9;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR8_0 | GPIO_PUPDR_PUPDR9_0;
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR8_1 | GPIO_PUPDR_PUPDR9_1);
    GPIOB->ODR &= ~(GPIO_ODR_ODR_8 | GPIO_ODR_ODR_9);
}

void I2C_START(void)
{
    SCL_HIGH;
    SDA_HIGH;
    I2C_DELAY;

    SDA_LOW;
    I2C_DELAY;
}

void I2C_STOP(void)
{
    SCL_HIGH;
    SDA_LOW;
    I2C_DELAY;

    SDA_HIGH;
    I2C_DELAY;
}

void I2C_Ack(void)
{
    SCL_LOW;
    SDA_HIGH;
    I2C_DELAY;

    SDA_LOW;
    I2C_DELAY;

    SCL_HIGH;
    I2C_DELAY;

    SCL_LOW;
    I2C_DELAY;

    SDA_HIGH;
    I2C_DELAY;
}

void I2C_Nack(void)
{
    SCL_LOW;
    SDA_HIGH;
    I2C_DELAY;

    SCL_HIGH;
    I2C_DELAY;

    SCL_LOW;
    I2C_DELAY;
}

uint8_t I2C_Wait4ack(void)
{
    uint16_t ack;
    SCL_LOW;
    SDA_HIGH;
    I2C_DELAY;

    SCL_HIGH;
    I2C_DELAY;

    ack = READ_SDA;

    SCL_LOW;
    I2C_DELAY;

    if (ack == 0)
    {
        return ACK;
    }
    else
    {
        return NACK;
    }
}

void I2C_SendByte(uint8_t Byte)
{
    uint8_t i = 0;
    for (i = 0; i < 8; i++)
    {
        uint8_t t = (Byte << i) & 0x80;
        SCL_LOW;
        SDA_LOW;
        I2C_DELAY;

        if (t)
        {
            SDA_HIGH;
        }
        else
        {
            SDA_LOW;
        }
        I2C_DELAY;

        SCL_HIGH;
        I2C_DELAY;

        SCL_LOW;
        I2C_DELAY;
    }
}

uint8_t I2C_ReadByte(void)
{
    uint8_t byte = 0x00;
    uint8_t i = 0;
    for (i = 0; i < 8; i++)
    {
        SCL_LOW;
        I2C_DELAY;

        SCL_HIGH;
        I2C_DELAY;

        if (READ_SDA)
        {
            byte |= 1 << (7 - i);
        }
        else
        {
            byte &= ~(1 << (7 - i));
        }

        SCL_LOW;
        I2C_DELAY;
    }
    return byte;
}
