#include "flash_h.h"

void FLASH_HARDWARE_Init_(void)
{
    SPI_HARD_Init_();
}

void FLASH_HARDWARE_MESSAGE(uint8_t *ID1, uint16_t *ID2)
{
    SPI_HARD_START();

    SPI_HARD_SWAP(0x9F);
    *ID1 = SPI_HARD_SWAP(0xFF);
    *ID2 = 0;
    *ID2 |= SPI_HARD_SWAP(0xFF) << 8;
    *ID2 |= SPI_HARD_SWAP(0xFF) & 0xFF;
    SPI_HARD_STOP();
    FLASH_HARDWARE_NOTBUSY();
}

void FLASH_HARDWARE_WRITE_ENABLE(void)
{
    SPI_HARD_START();
    SPI_HARD_SWAP(0x06);
    SPI_HARD_STOP();
    FLASH_HARDWARE_NOTBUSY();
}

void FLASH_HARDWARE_WRITE_DISABLE(void)
{
    SPI_HARD_START();
    SPI_HARD_SWAP(0x04);
    SPI_HARD_STOP();
    FLASH_HARDWARE_NOTBUSY();
}

void FLASH_HARDWARE_NOTBUSY(void)
{
    SPI_HARD_START();
    SPI_HARD_SWAP(0x05);
    while (SPI_HARD_SWAP(0xFF) & 0x01)
    {}
    SPI_HARD_STOP();
}

void FLASH_HARDWARE_ERASE(uint8_t block, uint8_t sector_page)
{
    SPI_HARD_START();
    SPI_HARD_SWAP(0x20);
    SPI_HARD_SWAP(block);
    SPI_HARD_SWAP(sector_page);
    SPI_HARD_SWAP(0x00);
    SPI_HARD_STOP();
    FLASH_HARDWARE_NOTBUSY();
}

void FLASH_HARDWARE_WRITE(uint8_t block, uint8_t sector_page, uint8_t inneraddr, uint8_t *data, uint16_t size)
{
    FLASH_HARDWARE_WRITE_ENABLE();
    SPI_HARD_START();
    SPI_HARD_SWAP(0x02);
    SPI_HARD_SWAP(block);
    SPI_HARD_SWAP(sector_page);
    SPI_HARD_SWAP(inneraddr);
    for (uint8_t i = 0; i < size; i++)
    {
        SPI_HARD_SWAP(*data);
        data++;
    }
    SPI_HARD_STOP();
    FLASH_HARDWARE_NOTBUSY();
}

void FLASH_HARDWARE_READ(uint8_t block, uint8_t sector_page, uint8_t inneraddr, uint8_t *buffer, uint16_t len)
{
    SPI_HARD_START();
    SPI_HARD_SWAP(0x03);
    SPI_HARD_SWAP(block);
    SPI_HARD_SWAP(sector_page);
    SPI_HARD_SWAP(inneraddr);
    for (uint8_t i = 0; i < len; i++)
    {
        *buffer = SPI_HARD_SWAP(0xFF);
        buffer++;
    }
    SPI_HARD_STOP();
    FLASH_HARDWARE_NOTBUSY();
}
