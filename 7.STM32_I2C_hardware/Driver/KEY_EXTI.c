#include "KEY_EXTI.h"
#include "DELAY.h"
#include "LED.h"

void KEY_EXTI_Init(void)
{
    LED_Init();
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    //开启中断所需时钟
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    RCC->APB2ENR |= RCC_APB2ENR_EXTIEN;
    
    GPIOA->MODER &= ~GPIO_MODER_MODER0;
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0;
    GPIOA->PUPDR |= GPIO_PUPDR_PUPDR0_1;
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR0_0;
    //选择EXTI0和PA相连
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
    //上升沿
    EXTI->RTSR |= EXTI_RTSR_TR0;
    //不屏蔽EXTI0
    EXTI->IMR |= EXTI_IMR_MR0;

    GPIOE->MODER &= ~GPIO_MODER_MODER4;
    GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR4;
    GPIOE->PUPDR |= GPIO_PUPDR_PUPDR4_0;
    GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR4_1;
    SYSCFG->EXTICR[1] |= SYSCFG_EXTICR2_EXTI4_PE;
    EXTI->FTSR |= EXTI_FTSR_TR4;
    EXTI->IMR |= EXTI_IMR_MR4;

    GPIOE->MODER &= ~GPIO_MODER_MODER3;
    GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR3;
    GPIOE->PUPDR |= GPIO_PUPDR_PUPDR3_0;
    GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR3_1;
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PE;
    EXTI->FTSR |= EXTI_FTSR_TR3;
    EXTI->IMR |= EXTI_IMR_MR3;
    
    GPIOE->MODER &= ~GPIO_MODER_MODER2;
    GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2;
    GPIOE->PUPDR |= GPIO_PUPDR_PUPDR2_0;
    GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR2_1;
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI2_PE;
    EXTI->FTSR |= EXTI_FTSR_TR2;
    EXTI->IMR |= EXTI_IMR_MR2;

    //设置分组，从011->100->101->110->111，分别为xxxx,xxx.y,xx.yy,x.yyy,yyyy
    SCB->AIRCR &= ~SCB_AIRCR_PRIGROUP_Msk;
    SCB->AIRCR |= 3U << 8;
    //设置优先级1111
    NVIC->IP[EXTI0_IRQn] |= 15 << 4;
    //ISER寄存器为32位，因此将序号右移5位为除以32，确定在哪个寄存器，后面则是取低5位，将对应序号的使能位置1
    NVIC->ISER[(((uint32_t)(int32_t)EXTI0_IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)EXTI0_IRQn) & 0x1FUL));
    NVIC->IP[EXTI4_IRQn] |= 14 << 4;
    NVIC->ISER[(((uint32_t)(int32_t)EXTI4_IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)EXTI4_IRQn) & 0x1FUL));
    NVIC->IP[EXTI3_IRQn] |= 13 << 4;
    NVIC->ISER[(((uint32_t)(int32_t)EXTI3_IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)EXTI3_IRQn) & 0x1FUL));
    NVIC->IP[EXTI2_IRQn] |= 12 << 4;
    NVIC->ISER[(((uint32_t)(int32_t)EXTI2_IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)EXTI2_IRQn) & 0x1FUL));
}

void EXTI0_IRQHandler(void)
{
    EXTI->PR |= EXTI_PR_PR0;
    delay_ms(20);
    if ((GPIOA->IDR & GPIO_IDR_IDR_0) != 0)
    {
        while((GPIOA->IDR & GPIO_IDR_IDR_0) != 0);
        LED_Toggle(LED_GREEN);
    }
}
