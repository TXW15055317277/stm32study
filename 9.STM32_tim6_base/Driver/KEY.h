#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx.h"

#define WK_UP GPIO_IDR_IDR_0
#define KEY0 GPIO_IDR_IDR_4
#define KEY1 GPIO_IDR_IDR_3
#define KEY2 GPIO_IDR_IDR_2


void KEY_Init(void);
uint8_t KEY_Scan(uint32_t KEY);

#endif
