#include "USART.h"
#include "LCD.h"

uint8_t string[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

int main(void)
{
    USART_Init_(115200);
    FSMC_LCD_Init_();
    LCD_RefreshConfig();

    LCD_SHOW_ASCII(0, 0, 32, 'A', BLACK, WHITE);
    LCD_SHOW_STRING(160, 0, 32, string, 10, BLACK, WHITE);

}
