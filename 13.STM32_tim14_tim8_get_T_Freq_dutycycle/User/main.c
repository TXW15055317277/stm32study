#include "USART.h"
#include <string.h>
#include "TIM14.h"
#include "TIM8.h"
#include "TIM4.h"
#include "DELAY.h"

int main(void)
{
    USART_Init_(115200);
    TIM14_Init_();
    TIM8_Init_();
    TIM4_Init_();
    TIM4_SetDutyCycle(36);
    printf("hello\n");


    while(1)
    {
        printf("T = %.2f us, f = %.2f Hz, duty = %.2f %%\n", TIM8_Get_T(), TIM8_Get_Freq(), TIM8_Get_DutyCycle() * 100);
        delay_s(1);
    }
}
