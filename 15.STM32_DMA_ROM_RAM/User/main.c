#include "USART.h"
#include <string.h>
#include "TIM14.h"
#include "TIM8.h"
#include "TIM4.h"
#include "TIM1.h"
#include "DMA_ROM2RAM.h"

const uint8_t p[] = {10, 20, 30, 40};
uint8_t r[4] = {0};
uint8_t TCFLAG = 0;

int main(void)
{
    USART_Init_(115200);

    // 看看变量地址
    printf("p = %p, r = %p\n", p, r);
    printf("p = %d, r = %d\n", &p, &r);
    printf("p = %d, r = %d\n", (uint32_t)p, (uint32_t)r);
    DMA_ROM2RAM_Init_();
    DMA_ROM2RAM_T((uint32_t)p, (uint32_t)r, 4);
    while (1)
    {
        if (TCFLAG)
        {
            for (uint8_t i = 0; i < 4; i ++)
            {
                printf("r = %d\n", r[i]);
            }
            TCFLAG = 0;
        }
    }
}
