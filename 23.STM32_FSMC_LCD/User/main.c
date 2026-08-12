#include "USART.h"
#include "LCD.h"

int main(void)
{
    USART_Init_(115200);
    FSMC_LCD_Init_();
    LCD_RefreshConfig();

    LCD_SHOW_STRING(16, 0, 32, "zhangyuqing\ntaoxuewen", BLACK, WHITE);
    LCD_FILL_CIRCLE(120, 160, 50, GREEN);

}
