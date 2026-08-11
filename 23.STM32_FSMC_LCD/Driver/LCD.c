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
    LCD_WRITE_DATA(0x48);
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
    LCD_WRITE_DATA((x_start + h - 1) & 0xFF);
}

void LCD_SHOW_ASCII(uint16_t x_start, uint16_t y_start, uint16_t char_size, uint8_t char_c, uint16_t color_c, uint16_t color_b)
{
    uint8_t row = char_c - ' ';
    LCD_SET_AREA(x_start, y_start, char_size / 2, char_size);
    LCD_WRITE_CMD(0x2C); // 写入数据到GRAM
    if (char_size == 12 || char_size == 16)
    {
        for (uint16_t i = 0; i < char_size; i++)
        {
            uint8_t rowdata = (char_size == 16) ? asc2_1608[row][i] : asc2_1206[row][i];
            for (uint16_t j = 0; j < char_size / 2; j++)
            {
                if (rowdata & 0x01)
                {
                    LCD_WRITE_DATA(color_c);
                }
                else
                {
                    LCD_WRITE_DATA(color_b);
                }
                rowdata >>= 1;
            }
        }
    }
    else if (char_size == 24 || char_size == 32)
    {
        const uint8_t *data = (char_size == 32) ? asc2_3216[row] : asc2_2412[row];
        if (char_size == 24)
        {
            for (uint8_t i = 0; i < char_size; i++)
            {
                for (uint8_t j = 0; j < char_size / 2; j++)
                {
                    int bit_idx = i * 12 + j;

                    uint8_t arr_idx = bit_idx / 8;   // 数组下标 0~35
                    uint8_t bit_pos = bit_idx % 8;   // 字节内第几位 0~7

                    // 读取该位
                    uint8_t bit_val = (data[arr_idx] >> bit_pos) & 0x01;
                    if (bit_val)
                    {
                        LCD_WRITE_DATA(color_c);
                    }
                    else
                    {
                        LCD_WRITE_DATA(color_b);
                    }
                }
            }
        }
        else
        {
            for (uint8_t i = 0; i < char_size; i++)
            {
                for (uint8_t j = 0; j < char_size / 2; j++)
                {
                    int bit_idx = i * 16 + j;

                    uint8_t arr_idx = bit_idx / 8;   // 数组下标 0~64
                    uint8_t bit_pos = bit_idx % 8;   // 字节内第几位 0~7

                    // 读取该位
                    uint8_t bit_val = (data[arr_idx] >> bit_pos) & 0x01;
                    if (bit_val)
                    {
                        LCD_WRITE_DATA(color_c);
                    }
                    else
                    {
                        LCD_WRITE_DATA(color_b);
                    }
                }
            }
        }
    }
}
