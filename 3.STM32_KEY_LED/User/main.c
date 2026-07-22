#include "stm32f4xx.h"
#include "LED.h"
#include "DELAY.h"
#include "KEY.h"
#include "KEY_EXTI.h"

int main(void)
{
  KEY_EXTI_Init();
	while(1);
}
