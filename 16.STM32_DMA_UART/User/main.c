#include "USART.h"
#include <string.h>
#include "TIM14.h"
#include "TIM8.h"
#include "TIM4.h"
#include "TIM1.h"
#include "DMA_UART.h"
#include "LED.h"


uint8_t ram[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
uint8_t rece[1] = {0};


int main(void)
{
    USART_Init_(115200);
    DMA_UART_Init_();

    printf("hello! DMA!\n");
    DMA_UART_TX((uint32_t)&ram, (uint32_t)&(USART1->DR), 8);
    DMA_UART_RX((uint32_t)&(USART1->DR), (uint32_t)&rece, 1);
    while (1)
    {}
}
