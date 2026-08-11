#include "USART.h"
#include "LCD.h"

int main(void)
{
    USART_Init_(115200);
    FSMC_LCD_Init_();
    LCD_RefreshConfig();

    LCD_SHOW_ASCII(0, 0, 12, 'a', BLACK, WHITE);
}
