#include "USART.h"

void USART_Init_(uint32_t Baudrate)
{
	float USARTDIV;
	unsigned int  DIV_M;
	unsigned int  DIV_F;
	
	USARTDIV = 84000000.0f / 16.0f / Baudrate;
	DIV_M = (uint32_t)USARTDIV;
	DIV_F = (USARTDIV - DIV_M)*16+0.5f;
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;


	GPIOA->AFR[1] |= (GPIO_AF_USART1 << 4);
	GPIOA->AFR[1] |= (GPIO_AF_USART1 << 8);
	GPIOA->MODER |= GPIO_MODER_MODER9_1;
	GPIOA->MODER &= ~GPIO_MODER_MODER9_0;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_9;
	GPIOA->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR9_0 | GPIO_OSPEEDER_OSPEEDR9_1);
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR9_0;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR9_1;

	GPIOA->MODER |= GPIO_MODER_MODER10_1;
	GPIOA->MODER &= ~GPIO_MODER_MODER10_0;
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_10;
	GPIOA->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR10_0 | GPIO_OSPEEDER_OSPEEDR10_1);
	GPIOA->PUPDR |= GPIO_PUPDR_PUPDR10_0;
	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR10_1;

	USART1->BRR = DIV_M<<4 | DIV_F;
	USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;
	USART1->CR1 |= USART_CR1_RXNEIE | USART_CR1_IDLEIE;
	USART1->CR1 &= ~USART_CR1_M;
	USART1->CR1 &= ~USART_CR1_PCE;
	USART1->CR2 &= ~USART_CR2_STOP;
	USART1->CR1 |= USART_CR1_UE;
	
	//开启中断时钟
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	RCC->APB2ENR |= RCC_APB2ENR_EXTIEN;

	//设置分组，从011->100->101->110->111，分别为xxxx,xxx.y,xx.yy,x.yyy,yyyy
	SCB->AIRCR &= ~SCB_AIRCR_PRIGROUP_Msk;
	SCB->AIRCR |= 3U << 8;
	//设置优先级1111
	NVIC->IP[USART1_IRQn] |= 0 << 4;
	//ISER寄存器为32位，因此将序号右移5位为除以32，确定在哪个寄存器，后面则是取低5位，将对应序号的使能位置1
	NVIC->ISER[(((uint32_t)(int32_t)USART1_IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)(int32_t)USART1_IRQn) & 0x1FUL));
}

void USART_Transmit(uint8_t message)
{
    while ((USART1->SR & USART_SR_TXE) == 0)
    {}
    USART1->DR = message;
}

void USART_String_tx(uint8_t *str, uint8_t size)
{
	uint8_t i;
	for (i = 0; i < size; i++)
	{
		USART_Transmit(str[i]);
	}
}

void USART1_IRQHandler(void)
{
	if (USART1->SR & USART_SR_RXNE)
	{
		buffer[size] = USART1->DR;
		size++;
	}
	else if (USART1->SR & USART_SR_IDLE)
	{
		USART1->SR;
		USART1->DR;
		USART_String_tx(buffer, size);
		size = 0;
	}
}

int fputc(int ch, FILE * file)
{
	USART_Transmit(ch);
	return ch;
}
