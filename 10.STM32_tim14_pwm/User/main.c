#include "USART.h"
#include "TIM6.h"
#include <string.h>

#include "TIM14.h"


uint8_t buffer[100] = {0};
uint8_t size = 0;

int main(void)
{
    USART_Init_(115200);
    TIM6_Init_();
    TIM14_Init_();
    uint8_t dutycycle = 0;
    uint8_t dir = 0;
    while(1)
    {
        if (dir == 0)
        {
            dutycycle++;
            if (dutycycle >= 99)
            {
                dir = 1;
            }
        }
        else
        {
            dutycycle--;
            if (dutycycle <= 1)
            {
                dir = 0;
            }
        }
        TIM14_SetDutyCycle(dutycycle);
        TIM6_delay_ms(20);
    }
}
