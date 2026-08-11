#include "LCD.h"

void LCD_WRITE_CMD(uint16_t LCD_CMD)
{
    *LCD_addr_cmd = LCD_CMD;
}

void LCD_WRITE_DATA(uint16_t LCD_DATA)
{
    *LCD_addr_data = LCD_DATA;
}

uint16_t LCD_READ_DATA(void)
{
    return *LCD_addr_data;
}

void LCD_RefreshConfig(void)
{
    LCD_WRITE_CMD(0xCF);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0xC1);
    LCD_WRITE_DATA(0X30);
    LCD_WRITE_CMD(0xED);
    LCD_WRITE_DATA(0x64);
    LCD_WRITE_DATA(0x03);
    LCD_WRITE_DATA(0X12);
    LCD_WRITE_DATA(0X81);
    LCD_WRITE_CMD(0xE8);
    LCD_WRITE_DATA(0x85);
    LCD_WRITE_DATA(0x10);
    LCD_WRITE_DATA(0x7A);
    LCD_WRITE_CMD(0xCB);
    LCD_WRITE_DATA(0x39);
    LCD_WRITE_DATA(0x2C);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x34);
    LCD_WRITE_DATA(0x02);
    LCD_WRITE_CMD(0xF7);
    LCD_WRITE_DATA(0x20);
    LCD_WRITE_CMD(0xEA);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_CMD(0xC0);/*Powercontrol*/
    LCD_WRITE_DATA(0x1B);/*VRH[5:0]*/
    LCD_WRITE_CMD(0xC1);/*Powercontrol*/
    LCD_WRITE_DATA(0x01);/*SAP[2:0];BT[3:0]*/
    LCD_WRITE_CMD(0xC5);/*VCMcontrol*/
    LCD_WRITE_DATA(0x30);/*3F*/
    LCD_WRITE_DATA(0x30);/*3C*/
    LCD_WRITE_CMD(0xC7);/*VCMcontrol2*/
    LCD_WRITE_DATA(0XB7);
    LCD_WRITE_CMD(0x36);/*MemoryAccessControl*/
    LCD_WRITE_DATA(0x08);/* 竖屏240x320: 去掉MX镜像(MX=0,MY=0,MV=0), 保留RGB顺序bit3 */
    LCD_WRITE_CMD(0x3A);
    LCD_WRITE_DATA(0x55);
    LCD_WRITE_CMD(0xB1);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x1A);
    LCD_WRITE_CMD(0xB6);/*DisplayFunctionControl*/
    LCD_WRITE_DATA(0x0A);
    LCD_WRITE_DATA(0xA2);
    LCD_WRITE_CMD(0xF2);/*3GammaFunctionDisable*/
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_CMD(0x26);/*Gammacurveselected*/
    LCD_WRITE_DATA(0x01);
    LCD_WRITE_CMD(0xE0);/*SetGamma*/
    LCD_WRITE_DATA(0x0F);
    LCD_WRITE_DATA(0x2A);
    LCD_WRITE_DATA(0x28);
    LCD_WRITE_DATA(0x08);
    LCD_WRITE_DATA(0x0E);
    LCD_WRITE_DATA(0x08);
    LCD_WRITE_DATA(0x54);
    LCD_WRITE_DATA(0XA9);
    LCD_WRITE_DATA(0x43);
    LCD_WRITE_DATA(0x0A);
    LCD_WRITE_DATA(0x0F);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_CMD(0XE1);/*SetGamma*/
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x15);
    LCD_WRITE_DATA(0x17);
    LCD_WRITE_DATA(0x07);
    LCD_WRITE_DATA(0x11);
    LCD_WRITE_DATA(0x06);
    LCD_WRITE_DATA(0x2B);
    LCD_WRITE_DATA(0x56);
    LCD_WRITE_DATA(0x3C);
    LCD_WRITE_DATA(0x05);
    LCD_WRITE_DATA(0x10);
    LCD_WRITE_DATA(0x0F);
    LCD_WRITE_DATA(0x3F);
    LCD_WRITE_DATA(0x3F);
    LCD_WRITE_DATA(0x0F);
    LCD_WRITE_CMD(0x2B);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x01);
    LCD_WRITE_DATA(0x3f);
    LCD_WRITE_CMD(0x2A);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0xef);
    LCD_WRITE_CMD(0x11);/*ExitSleep*/
    delay_ms(120);
    LCD_WRITE_CMD(0x29);/*displayon*/
}

void LCD_RESET(void)
{
    LCD_WRITE_CMD(0x01);
}

uint32_t LCD_ReadStatus(void)
{
    LCD_WRITE_CMD(0x09); // 发送读ID命令
    uint32_t status = 0;
    LCD_READ_DATA();
    status |= (uint32_t)LCD_READ_DATA() << 24;
    status |= (uint32_t)LCD_READ_DATA() << 16;
    status |= (uint32_t)LCD_READ_DATA() << 8;
    status |= (uint32_t)LCD_READ_DATA();
    return status;
}

// 读取ID
uint32_t LCD_READ_ID(void)
{
    LCD_WRITE_CMD(0xD3); // 发送读ID命令
    uint32_t id = 0;
    LCD_READ_DATA();
    id = (uint32_t)LCD_READ_DATA() << 16;
    id |= (uint32_t)LCD_READ_DATA() << 8;
    id |= (uint32_t)LCD_READ_DATA();
    return id;
}

void LCD_Fill_Full_Screen(uint16_t color)
{
    // 列地址 0~239
    LCD_WRITE_CMD(0x2A);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0xEF); // 结束列 239

    // 行地址 0~319
    LCD_WRITE_CMD(0x2B);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x00);
    LCD_WRITE_DATA(0x01);
    LCD_WRITE_DATA(0x3F); // 结束行 319


    LCD_WRITE_CMD(0x2C); // 写入数据到GRAM

    // 填充颜色
    for (uint32_t i = 0; i < LCD_W * LCD_H; i++)
    {
        LCD_WRITE_DATA(color);
    }
}

uint16_t LCD_ReadPixel(uint16_t x, uint16_t y)
{
    // 设置坐标
    LCD_WRITE_CMD(0x2A);
    LCD_WRITE_DATA(x >> 8);
    LCD_WRITE_DATA(x & 0xFF);
    LCD_WRITE_DATA(x >> 8);
    LCD_WRITE_DATA(x & 0xFF);

    LCD_WRITE_CMD(0x2B);
    LCD_WRITE_DATA(y >> 8);
    LCD_WRITE_DATA(y & 0xFF);
    LCD_WRITE_DATA(y >> 8);
    LCD_WRITE_DATA(y & 0xFF);

    LCD_WRITE_CMD(0x2E);
    uint16_t r = LCD_READ_DATA();        // 强制Dummy读，丢弃无效值
    r = LCD_READ_DATA();
    uint16_t b = LCD_READ_DATA();
    uint16_t g = r & 0XFF;               /* 对于 9341/5310/5510/7789/9806, 第一次读取的是RG的值,R在前,G在后,各占8位 */
    g <<= 8;
    
    return (((r >> 11) << 11) | ((g >> 10) << 5) | (b >> 11));  /* 9341/5310/5510/7789/9806 需要公式转换一下 */
}

void LCD_SET_AREA(uint16_t x_start, uint16_t y_start, uint16_t w, uint16_t h)
{
    LCD_WRITE_CMD(0x2A);
    LCD_WRITE_DATA(x_start >> 8);
    LCD_WRITE_DATA(x_start & 0xFF);
    LCD_WRITE_DATA((x_start + w - 1) >> 8);
    LCD_WRITE_DATA((x_start + w - 1) & 0xFF);

    LCD_WRITE_CMD(0x2B);
    LCD_WRITE_DATA(y_start >> 8);
    LCD_WRITE_DATA(y_start & 0xFF);
    LCD_WRITE_DATA((y_start + h - 1) >> 8);
    LCD_WRITE_DATA((y_start + h - 1) & 0xFF);
}

void LCD_SHOW_ASCII(uint16_t x_start, uint16_t y_start, uint16_t char_size, uint8_t char_c, uint16_t color_c, uint16_t color_b)
{
    uint8_t row = char_c - ' ';        // 字库索引（从空格开始）
    uint8_t rows = 0, cols = 0;        // 字符高、宽（像素）
    uint8_t bytes_per_col = 0;         // 每列字节数
    const uint8_t *data = NULL;

    // 本字库为"列优先"存储: 每个字符 = cols 列, 每列 bytes_per_col 字节(大端,MSB在顶),
    // 名字前两位=高度, 后两位=宽度, 例如 2412 = 24 高 x 12 宽
    switch (char_size)
    {
        case 12: rows = 12; cols = 6;  bytes_per_col = 2; data = (const uint8_t *)asc2_1206[row]; break;
        case 16: rows = 16; cols = 8;  bytes_per_col = 2; data = (const uint8_t *)asc2_1608[row]; break;
        case 24: rows = 24; cols = 12; bytes_per_col = 3; data = (const uint8_t *)asc2_2412[row]; break;
        case 32: rows = 32; cols = 16; bytes_per_col = 4; data = (const uint8_t *)asc2_3216[row]; break;
        default: return;
    }

    LCD_SET_AREA(x_start, y_start, cols, rows);
    LCD_WRITE_CMD(0x2C); // 写入数据到GRAM

    // GRAM 写入顺序: 行内列递增, 再换行 (for row : for col)
    // 像素 (X=col, Y=row) = 第 col 列数据的第 row 位(该列最高位为顶部)
    for (uint8_t i = 0; i < rows; i++)          // i = 行 (Y)
    {
        for (uint8_t j = 0; j < cols; j++)      // j = 列 (X)
        {
            // 合成第 j 列的 bytes_per_col 个字节为大端整数
            uint32_t coldata = 0;
            for (uint8_t k = 0; k < bytes_per_col; k++)
            {
                coldata = (coldata << 8) | data[j * bytes_per_col + k];
            }
            uint32_t bit = 1UL << (bytes_per_col * 8 - 1 - i);
            LCD_WRITE_DATA((coldata & bit) ? color_c : color_b);
        }
    }
}

void LCD_SHOW_STRING(uint16_t x_start, uint16_t y_start, uint16_t str_size, uint8_t *str, uint8_t str_len, uint16_t color_c, uint16_t color_b)
{
    for (uint8_t i = 0; i < str_len; i++)
    {

        if (x_start + str_size / 2 < 240)
        {
            LCD_SHOW_ASCII(x_start, y_start, str_size, *str++, color_c, color_b);
            x_start += str_size / 2;
        }
        else
        {
            y_start += str_size;
            x_start = 0;
            LCD_SHOW_ASCII(0, y_start, str_size, *str++, color_c, color_b);
        } 
    }
}
