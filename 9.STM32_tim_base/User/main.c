#include "USART.h"
#include "m24c02_h.h"
#include <string.h>
#include "LED.h"
#include "TIM6.h"


uint8_t buffer[100] = {0};
uint8_t size = 0;

int main(void)
{
    USART_Init_(115200);
    LED_Init();
    TIM6_Init_();
    while(1)
    {
        LED_ON(LED_GREEN);
        TIM6_delay_s(1);
        LED_OFF(LED_GREEN);
        TIM6_delay_s(1);
    }
}
