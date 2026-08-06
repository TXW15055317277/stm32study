#include "USART.h"
#include <string.h>
#include "flash_s.h"
#include "DELAY.h"

uint16_t adc_data[6] = {0};
uint8_t data[1] = {0};
uint8_t ID1;
uint16_t ID2;
uint8_t data_flash[8] = {'z', 'y', 'q', '1', '2', '3', '4', '5'};
uint16_t size_flash = 8;
uint8_t buffer_flash[8] = {0};
uint16_t len_flash = 8;

int main(void)
{
    USART_Init_(115200);
    FLASH_SOFT_Init();
    FLASH_SOFT_MESSAGE(&ID1, &ID2);
    printf("制造商=%#x, 芯片=%#x\n", ID1, ID2);
    FLASH_SOFT_WRITE_ENABLE();
    FLASH_SOFT_ERASE(0xFF, 0xFF);
    FLASH_SOFT_WRITE(0xFF, 0xFF, 0x00, data_flash, size_flash);
    FLASH_SOFT_READ(0xFF, 0xFF, 0x00, buffer_flash, len_flash);
    printf("buffer = %c, %c, %c, %c, %c, %c, %c, %c\n", buffer_flash[0], buffer_flash[1], buffer_flash[2], buffer_flash[3], buffer_flash[4], buffer_flash[5], buffer_flash[6], buffer_flash[7]);
}
