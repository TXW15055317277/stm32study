#include "USART.h"
#include <string.h>
#include "KEY_EXTI.h"
#include "TIM14.h"
#include "TIM1.h"


uint8_t buffer[100] = {0};
uint8_t size = 0;
uint8_t dutycycle = 50;

int main(void)
{
    USART_Init_(115200);
    TIM14_Init_();
    TIM1_Init_();
    LED_Init();
    KEY_EXTI_Init();

    while(1)
    {}
}
