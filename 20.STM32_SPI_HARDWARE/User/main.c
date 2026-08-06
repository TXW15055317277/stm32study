#include "USART.h"
#include <string.h>
#include "DELAY.h"
#include "flash_h.h"

uint8_t ID1 = 0;
uint16_t ID2 = 0;
uint8_t spi_data[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', };
uint8_t spi_buffer[8] = {0};
uint16_t spi_size = 8;
uint16_t spi_len = 8;

int main(void)
{
    USART_Init_(115200);
    FLASH_HARDWARE_Init_();
    FLASH_HARDWARE_MESSAGE(&ID1, &ID2);
    printf("ID1 = %#x, ID2 = %#x\n", ID1, ID2);
    FLASH_HARDWARE_WRITE_ENABLE();
    FLASH_HARDWARE_ERASE(0xFF, 0xFF);
    FLASH_HARDWARE_WRITE(0xFF, 0xFF, 0x00, spi_data, spi_size);
    FLASH_HARDWARE_READ(0xFF, 0xFF, 0x00, spi_buffer, spi_len);
    printf("buffer = %c, %c, %c, %c, %c, %c, %c, %c\n", spi_buffer[0], spi_buffer[1], spi_buffer[2], spi_buffer[3], spi_buffer[4], spi_buffer[5], spi_buffer[6], spi_buffer[7]);
}
