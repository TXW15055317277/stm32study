#include "USART.h"
#include "FSMC_SRAM_s.h"


int main(void)
{
    USART_Init_(115200);
    FSMC_Init_s();
    uint16_t *test = (uint16_t *)0x68000000;
    *test = 123;
    uint16_t *test1 = (uint16_t *)0x68000002;
    *test1 = 456;
    printf("test = %d, @%p\n", *test, test);
    printf("test1 = %d, @%p\n", *test1, test1);
}
