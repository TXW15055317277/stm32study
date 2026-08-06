#ifndef __FLASH_H_H
#define __FLASH_H_H

#include "stm32f4xx.h"
#include "SPI_HARDWARE.h"

void FLASH_HARDWARE_Init_(void);
// 获取Flash信息测试
void FLASH_HARDWARE_MESSAGE(uint8_t * ID1, uint16_t * ID2);
// 打开写使能
void FLASH_HARDWARE_WRITE_ENABLE(void);
// 关闭写使能
void FLASH_HARDWARE_WRITE_DISABLE(void);
// 等待忙标志位为0
void FLASH_HARDWARE_NOTBUSY(void);
// 擦除数据
void FLASH_HARDWARE_ERASE(uint8_t block, uint8_t sector_page);
// 写入数据
void FLASH_HARDWARE_WRITE(uint8_t block, uint8_t sector_page, uint8_t inneraddr, uint8_t *data, uint16_t size);
// 读取数据
void FLASH_HARDWARE_READ(uint8_t block, uint8_t sector_page, uint8_t inneraddr, uint8_t *buffer, uint16_t len);


#endif
