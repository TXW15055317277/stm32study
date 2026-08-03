#include "USART.h"
#include <string.h>
#include "TIM14.h"
#include "TIM8.h"
#include "DELAY.h"

int main(void)
{
    USART_Init_(115200);
    TIM14_Init_();
    TIM8_Init_();


    while(1)
    {
        printf("T = %.2f us, f = %.2f Hz\n", TIM8_Get_T(), TIM8_Get_Freq());
        delay_s(1);
    }
}
