#include "I2C_Hardware.h"

void I2C_Init_H(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    GPIOB->MODER |= GPIO_MODER_MODER8_1 | GPIO_MODER_MODER9_1;
    GPIOB->MODER &= ~(GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);
    GPIOB->OTYPER |= GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_9;
    GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8 | GPIO_OSPEEDER_OSPEEDR8;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR8_0 | GPIO_PUPDR_PUPDR9_0;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR8_1 | GPIO_PUPDR_PUPDR9_1;
    GPIOB->AFR[1] |= GPIO_AF_I2C1;
    GPIOB->AFR[1] |= GPIO_AF_I2C1 << 4;

    //选择频率
    I2C1->CR2 |= 42;
    //不选择SMBUS模式
    I2C1->CR1 &= I2C_CR1_SMBUS;
    //选择标准速率
    I2C1->CCR &= ~I2C_CCR_FS;
    //100kb/s下，每个T（high）为5us，42Mhz下，周期为1/42us，因此为5/（1/42）
    I2C1->CCR |= 210;
    //上升沿最多为1000us，因此在42Mhz下，最多有42个周期，为保留裕量，+1
    I2C1->TRISE |= 43;
    I2C1->CR1 |= I2C_CR1_PE;
}

uint8_t I2C_Start_H(void)
{
    uint16_t timeout = 0xFFFF;
    I2C1->CR1 |= I2C_CR1_START;

    while((I2C1->SR1 & I2C_SR1_SB) == 0 && timeout)
    {
        timeout--;
    }
    return timeout ? OK : FAIL;
}

void I2C_Stop_H(void)
{
    I2C1->CR1 |= I2C_CR1_STOP;
}

void I2C_ACK_H(void)
{
    I2C1->CR1 |= I2C_CR1_ACK;
}

void I2C_NACK_H(void)
{
    I2C1->CR1 &= ~I2C_CR1_ACK;
}

uint8_t I2C_SendAddr_H(uint8_t addr)
{
    uint16_t timeout = 0xFFFF;
    //将地址放入数据寄存器
    I2C1->DR = addr;
    while((I2C1->SR1 & I2C_SR1_ADDR) == 0 && timeout)
    {
        timeout--;
    }
    //访问SR2清除标志位
    if (timeout > 0)
    {
        I2C1->SR2;
    }
    
    return timeout? OK : FAIL;
}

uint8_t I2C_SendByte_H(uint8_t byte)
{
    uint16_t timeout = 0xFFFF;
    //等待发送空（TXE）
    while((I2C1->SR1 & I2C_SR1_TXE) == 0 && timeout)
    {
        timeout--;
    }
    //将地址放入数据寄存器
    I2C1->DR = byte;
    
    timeout = 0xFFFF;
    //等待响应（BTF）
    while((I2C1->SR1 & I2C_SR1_BTF) == 0 && timeout)
    {
        timeout--;
    }
    return timeout? OK : FAIL;
}

uint8_t I2C_ReadByte_H(void)
{
    uint16_t timeout = 0xFFFF;
    //等待接收满（RXNE）
    while((I2C1->SR1 & I2C_SR1_RXNE) == 0 && timeout)
    {
        timeout--;
    }

    return timeout? I2C1->DR : FAIL;
}
