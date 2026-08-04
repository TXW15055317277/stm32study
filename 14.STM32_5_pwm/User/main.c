#include "USART.h"
#include <string.h>
#include "TIM14.h"
#include "TIM8.h"
#include "TIM4.h"
#include "TIM1.h"
#include "DELAY.h"

int main(void)
{
    USART_Init_(115200);
    TIM8_Init_();
    TIM1_Init_();
}
