#include "flash_h.h"

void FLASH_HARDWARE_Init_(void)
{
    SPI_HARD_Init_();
}

void FLASH_HARDWARE_MESSAGE(uint8_t *ID1, uint16_t *ID2)
{
    SPI_HARD_START();

    uint8_t t = 0x9F;
    uint8_t t_ = 0xFF;
    uint8_t temp = 0;
    SPI_DMA_START((uint32_t)&t, (uint32_t)&temp);
    SPI_DMA_START((uint32_t)&t_, (uint32_t)&temp);
    *ID1 = temp;
    *ID2 = 0;
    SPI_DMA_START((uint32_t)&t_, (uint32_t)&temp);
    *ID2 |= temp << 8;
    SPI_DMA_START((uint32_t)&t_, (uint32_t)&temp);
    *ID2 |= temp & 0xFF;
    SPI_HARD_STOP();
    FLASH_HARDWARE_NOTBUSY();
}

void FLASH_HARDWARE_WRITE_ENABLE(void)
{
    uint8_t t = 0x06;
    uint8_t temp = 0;
    SPI_HARD_START();
    SPI_DMA_START((uint32_t)&t, (uint32_t)&temp);
    SPI_HARD_STOP();
    FLASH_HARDWARE_NOTBUSY();
}

void FLASH_HARDWARE_WRITE_DISABLE(void)
{
    uint8_t t = 0x04;
    uint8_t temp = 0;
    SPI_HARD_START();
    SPI_DMA_START((uint32_t)&t, (uint32_t)&temp);
    SPI_HARD_STOP();
    FLASH_HARDWARE_NOTBUSY();
}

void FLASH_HARDWARE_NOTBUSY(void)
{
    SPI_HARD_START();
    uint8_t t = 0x05;
    uint8_t _ = 0xFF;
    uint8_t temp = 0;
    uint8_t busy = 1;
    SPI_DMA_START((uint32_t)&t, (uint32_t)&temp);
    while (busy)
    {
        SPI_DMA_START((uint32_t)&_, (uint32_t)&temp);
        if ((temp & 0x01) == 0)
        {
            busy = 0;
        }
    }
    SPI_HARD_STOP();
}

void FLASH_HARDWARE_ERASE(uint8_t block, uint8_t sector_page)
{
    SPI_HARD_START();
    uint8_t t = 0x20;
    uint8_t temp = 0x00;
    uint8_t _ = 0xFF;
    SPI_DMA_START((uint32_t)&t, (uint32_t)&temp);
    SPI_DMA_START((uint32_t)&block, (uint32_t)&temp);
    SPI_DMA_START((uint32_t)&sector_page, (uint32_t)&temp);
    SPI_DMA_START((uint32_t)&_, (uint32_t)&temp);
    SPI_HARD_STOP();
    FLASH_HARDWARE_NOTBUSY();
}

void FLASH_HARDWARE_WRITE(uint8_t block, uint8_t sector_page, uint8_t inneraddr, uint8_t *data, uint16_t size)
{
    uint8_t t = 0x02;
    uint8_t temp = 0x00;
    FLASH_HARDWARE_WRITE_ENABLE();
    SPI_HARD_START();
    SPI_DMA_START((uint32_t)&t, (uint32_t)&temp);
    SPI_DMA_START((uint32_t)&block, (uint32_t)&temp);
    SPI_DMA_START((uint32_t)&sector_page, (uint32_t)&temp);
    SPI_DMA_START((uint32_t)&inneraddr, (uint32_t)&temp);
    for (uint8_t i = 0; i < size; i++)
    {
        SPI_DMA_START((uint32_t)data, (uint32_t)&temp);
        data++;
    }
    SPI_HARD_STOP();
    FLASH_HARDWARE_NOTBUSY();
}

void FLASH_HARDWARE_READ(uint8_t block, uint8_t sector_page, uint8_t inneraddr, uint8_t *buffer, uint16_t len)
{
    uint8_t t = 0x03;
    uint8_t temp = 0x00;
    uint8_t _ = 0xFF;
    FLASH_HARDWARE_WRITE_ENABLE();
    SPI_HARD_START();
    SPI_DMA_START((uint32_t)&t, (uint32_t)&temp);
    SPI_DMA_START((uint32_t)&block, (uint32_t)&temp);
    SPI_DMA_START((uint32_t)&sector_page, (uint32_t)&temp);
    SPI_DMA_START((uint32_t)&inneraddr, (uint32_t)&temp);
    for (uint8_t i = 0; i < len; i++)
    {
        SPI_DMA_START((uint32_t)_, (uint32_t)&temp);
        *buffer = temp;
        buffer++;
    }
    SPI_HARD_STOP();
    FLASH_HARDWARE_NOTBUSY();
}
