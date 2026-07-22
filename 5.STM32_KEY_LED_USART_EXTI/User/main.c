#include "USART.h"


uint8_t buffer[100] = {0};
uint8_t size = 0;

int main(void)
{
	USART_Init_(115200);
	printf("hello, world!\n");
	while (1)
	{}
}
