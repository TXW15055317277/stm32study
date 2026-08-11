#ifndef __LCD_H
#define __LCD_H

#include "stm32f4xx.h"
#include "FSMC_LCD.h"
#include "DELAY.h"
#include "stdio.h"
#include "lcdfont.h"

// 定义读写地址
#define SRAM_bank1_4 0x6C000000
#define LCD_addr_cmd (uint16_t *)SRAM_bank1_4
// FSMC 16-bit access: external A6 maps to MCU byte offset 0x80
#define LCD_addr_data (uint16_t *)(LCD_addr_cmd + (1 << 6))

// 定义宽和高
#define LCD_W 240
#define LCD_H 320

// 定义颜色
//RGB565  R(5bit) G(6bit) B(5bit)
#define WHITE     0xFFFF   //R=31,G=63,B=31 白
#define BLACK     0x0000   //R=0, G=0, B=0   黑
#define BLUE      0x001F   //R=0, G=0, B=31  蓝
#define BRED      0xF81F   //R=31,G=0, B=31  紫红
#define GRED      0xFFE0   //R=31,G=63,B=0   黄
#define GBLUE     0x07FF   //R=0, G=63,B=31  青
#define RED       0xF800   //R=31,G=0, B=0   红
#define MAGENTA   0xF81F   //R=31,G=0, B=31  品红
#define GREEN     0x07E0   //R=0, G=63,B=0   绿
#define CYAN      0x7FFF   //R=15,G=63,B=31  青色
#define YELLOW    0xFFE0   //R=31,G=63,B=0   黄色
#define BROWN     0xBC40   //棕色
#define BRRED     0xFC07   //棕红色
#define GRAY      0x8430   //灰色

// 写命令
void LCD_WRITE_CMD(uint16_t LCD_CMD);

// 写数据
void LCD_WRITE_DATA(uint16_t LCD_DATA);

// 读数据
uint16_t LCD_READ_DATA(void);

// 读取ID
uint32_t LCD_READ_ID(void);

// 颜色填充
void LCD_Fill_Full_Screen(uint16_t color);

// 初始化序列
void LCD_RefreshConfig(void);

// RESET
void LCD_RESET(void);

// 读取状态
uint32_t LCD_ReadStatus(void);

// 读取某点颜色
uint16_t LCD_ReadPixel(uint16_t x, uint16_t y);

// 选择区域
void LCD_SET_AREA(uint16_t x_start, uint16_t y_start, uint16_t w, uint16_t h);

// 显示一个英文字符
void LCD_SHOW_ASCII(uint16_t x_start, uint16_t y_start, uint16_t char_size, uint8_t char_c, uint16_t color_c, uint16_t color_b);




#endif
