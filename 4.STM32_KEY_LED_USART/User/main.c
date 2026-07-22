#include "USART.h"
#include "DELAY.h"
#include <string.h>

uint8_t buffer[100] = {0};
uint8_t size = 0;

int main(void)
{
	USART_Init_(115200);
	printf("hello, world!\n");
	while (1)
	{
		USART_String_rx(buffer, &size);
		USART_String_tx(buffer, size);
	}
}
