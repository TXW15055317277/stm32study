#include "stm32f4xx.h"
#include "LED.h"
#include "DELAY.h"

int main(void)
{
  uint16_t LEDs[2] = {LED_GREEN, LED_RED};
  LED_Init();
  while(1)
  {
    LED_Toggle(LED_GREEN);
    delay_s(10);
    LED_Toggle(LED_GREEN);
    LED_Toggle(LED_RED);
    delay_s(10);
    LED_ON_ALL(LEDs, 2);
    delay_s(10);
    LED_OFF_ALL(LEDs, 2);
		delay_s(10);
  }
}
