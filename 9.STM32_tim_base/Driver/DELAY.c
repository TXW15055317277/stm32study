#include "DELAY.h"

void delay_ms(uint32_t ms)
{
    while(ms--)
    {
        delay_us(1000);
    }
}

void delay_us(uint32_t us)
{
    SysTick->LOAD = 168 * us;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
    {}
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void delay_s(uint32_t s)
{
    while(s--)
    {
        delay_ms(1000);
    }
}
