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
#include "ADC_DMA.h"

uint16_t data[6] = {0};

int main(void)
{
    USART_Init_(115200);
    TIM6_Init_();
    ADC_MULTI_Init_();
    ADC_MULTI_START_();
    while (1)
    {
        printf("V1=%.4f\n", data[0] * 3.3 / 4095);
        printf("V2=%.4f\n", data[1] * 3.3 / 4095);
        printf("V3=%.4f\n", data[2] * 3.3 / 4095);
        printf("V4=%.4f\n", data[3] * 3.3 / 4095);
        printf("V5=%.4f\n", data[4] * 3.3 / 4095);
        printf("V6=%.4f\n", data[5] * 3.3 / 4095);
        TIM6_delay_s(1);
    }
}
