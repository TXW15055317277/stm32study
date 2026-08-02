#include "Systick.h"

volatile uint32_t g_SysTick_Count = 0;

void Systick_Init_(void)
{
    SysTick->CTRL = 0;
    SysTick->VAL = 0;

    // 每1us产生一次中断
    SysTick->LOAD = 168 - 1;

    // 分别使能时钟源（不分频）、使能中断、使能开关
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;

    g_SysTick_Count = 0;
}

void SysTick_delay_us(uint32_t us)
{
    g_SysTick_Count = 0;
    while (g_SysTick_Count < us)
    {
    }
}

void SysTick_delay_ms(uint32_t ms)
{
    while (ms--)
    {
        SysTick_delay_us(1000);
    }
}

void SysTick_delay_s(uint32_t s)
{
    while (s--)
    {
        SysTick_delay_ms(1000);
    }
}

void SysTick_Handler(void)
{
    g_SysTick_Count++;
}
