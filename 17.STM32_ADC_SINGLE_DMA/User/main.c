#include "USART.h"
#include <string.h>
#include "TIM6.h"
#include "TIM14.h"
#include "TIM8.h"
#include "TIM4.h"
#include "TIM1.h"
#include "DMA_UART.h"
#include "LED.h"
#include "ADC.h"

uint16_t data[1] = {0};

int main(void)
{
    USART_Init_(115200);
    TIM6_Init_();
    ADC_SINGLE_Init_();
    ADC_SINGLE_START_();
    while (1)
    {
        printf("当前电压=%.4f\n", data[0] * 3.3 / 4095);
        TIM6_delay_s(1);
    }
}
