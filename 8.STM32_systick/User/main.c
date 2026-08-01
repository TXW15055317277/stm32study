#include "USART.h"
#include "m24c02_h.h"
#include <string.h>
#include "LED.h"
#include "Systick.h"


uint8_t buffer[100] = {0};
uint8_t size = 0;

int main(void)
{
    LED_Init();
    Systick_Init_();
    while(1)
    {
        LED_ON(LED_GREEN);
        SysTick_delay_s(1);
        LED_OFF(LED_GREEN);
        SysTick_delay_s(1);
    }
}
