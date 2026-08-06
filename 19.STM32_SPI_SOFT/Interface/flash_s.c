#include "flash_s.h"

void FLASH_SOFT_Init(void)
{
    SPI_SOFT_Init_();
}

void FLASH_SOFT_MESSAGE(uint8_t * ID1, uint16_t * ID2)
{
    SPI_SOFT_START();

    SPI_SOFT_SWAP(0x9F);
    * ID1 = SPI_SOFT_SWAP(0xFF);
    * ID2 = 0;
    * ID2 |= SPI_SOFT_SWAP(0xFF) << 8;
    * ID2 |= SPI_SOFT_SWAP(0xFF) & 0xFF;
    SPI_SOFT_STOP();
    FLASH_SOFT_NOTBUSY();
}

void FLASH_SOFT_WRITE_ENABLE(void)
{
    SPI_SOFT_START();
    SPI_SOFT_SWAP(0x06);
    SPI_SOFT_STOP();
    FLASH_SOFT_NOTBUSY();
}

void FLASH_SOFT_WRITE_DISABLE(void)
{
    SPI_SOFT_START();
    SPI_SOFT_SWAP(0x04);
    SPI_SOFT_STOP();
    FLASH_SOFT_NOTBUSY();
}

void FLASH_SOFT_NOTBUSY(void)
{
    SPI_SOFT_START();
    SPI_SOFT_SWAP(0x05);
    while (SPI_SOFT_SWAP(0xFF) & 0x01)
    {}
    SPI_SOFT_STOP();
}
void FLASH_SOFT_ERASE(uint8_t block, uint8_t sector_page)
{
    SPI_SOFT_START();
    SPI_SOFT_SWAP(0x20);
    SPI_SOFT_SWAP(block);
    SPI_SOFT_SWAP(sector_page);
    SPI_SOFT_SWAP(0x00);
    SPI_SOFT_STOP();
    FLASH_SOFT_NOTBUSY();
}

void FLASH_SOFT_WRITE(uint8_t block, uint8_t sector_page, uint8_t inneraddr, uint8_t *data, uint16_t size)
{
    SPI_SOFT_START();
    FLASH_SOFT_WRITE_ENABLE();

    SPI_SOFT_START();
    FLASH_SOFT_NOTBUSY();
    SPI_SOFT_START();
    SPI_SOFT_SWAP(0x02);
    SPI_SOFT_SWAP(block);
    SPI_SOFT_SWAP(sector_page);
    SPI_SOFT_SWAP(inneraddr);
    for (uint16_t i = 0; i < size; i++)
    {
        SPI_SOFT_SWAP(*data);
        data++;
    }
    SPI_SOFT_STOP();
    FLASH_SOFT_NOTBUSY();
}

void FLASH_SOFT_READ(uint8_t block, uint8_t sector_page, uint8_t inneraddr, uint8_t *buffer, uint16_t len)
{
    SPI_SOFT_START();
    FLASH_SOFT_NOTBUSY();
    SPI_SOFT_START();
    SPI_SOFT_SWAP(0x03);
    SPI_SOFT_SWAP(block);
    SPI_SOFT_SWAP(sector_page);
    SPI_SOFT_SWAP(inneraddr);
    for (uint16_t i = 0; i < len; i++)
    {
        *buffer = SPI_SOFT_SWAP(0xFF);
        buffer++;
    }
    SPI_SOFT_STOP();
    FLASH_SOFT_NOTBUSY();
}
