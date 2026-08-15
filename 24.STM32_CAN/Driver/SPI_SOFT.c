#include "SPI_SOFT.h"

void SPI_SOFT_Init_(void)
{
    // 打开GPIOB时钟
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // 输出模式配置
    GPIOB->MODER |= GPIO_MODER_MODER3_0;
    GPIOB->MODER &= ~GPIO_MODER_MODER3_1;
    GPIOB->MODER &= ~GPIO_MODER_MODER4_0;
    GPIOB->MODER &= ~GPIO_MODER_MODER4_1;
    GPIOB->MODER |= GPIO_MODER_MODER5_0;
    GPIOB->MODER &= ~GPIO_MODER_MODER5_1;
    GPIOB->MODER |= GPIO_MODER_MODER14_0;
    GPIOB->MODER &= ~GPIO_MODER_MODER14_1;
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT_3;
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT_4;
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT_5;
    GPIOB->OTYPER &= ~GPIO_OTYPER_OT_14;
    GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3 | GPIO_OSPEEDER_OSPEEDR4 | GPIO_OSPEEDER_OSPEEDR5 | GPIO_OSPEEDER_OSPEEDR14;
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR3_0 | GPIO_PUPDR_PUPDR4_0 | GPIO_PUPDR_PUPDR5_0 | GPIO_PUPDR_PUPDR14_0;
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR3_1 | GPIO_PUPDR_PUPDR4_1 | GPIO_PUPDR_PUPDR5_1 | GPIO_PUPDR_PUPDR14_1);
    GPIOB->ODR &= ~(GPIO_ODR_ODR_3 | GPIO_ODR_ODR_5);
    GPIOB->ODR |= GPIO_ODR_ODR_14;
    delay_us(5);
}

void SPI_SOFT_START(void)
{
    CS_START;
}

void SPI_SOFT_STOP(void)
{
    CS_STOP;
}

uint8_t SPI_SOFT_SWAP(uint8_t Byte)
{
    uint8_t r_Byte = 0x00;

    for (uint8_t i = 0; i < 8; i ++)
    {
        // 第一个上升沿之前准备好数据
        uint8_t t = (Byte << i) & 0x80;
        if (t)
        {
            MOSI_HIGH;
        }
        else
        {
            MOSI_LOW;
        }
        // 延迟一小会儿，等待数据稳定，等时钟上升沿就被从设备读取走了
        delay_us(5);
        
        // 上升沿时读取数据
        SCL_HIGH;       
        if (READ_MISO)
        {

            r_Byte |= 1 << (7 - i);
        }
        else
        {
            r_Byte &= ~(1 << (7 - i));
        }
        // 读完后准备拉低，等待下一次数据传输
        delay_us(5);
        SCL_LOW;
    }
    return r_Byte;    
}
