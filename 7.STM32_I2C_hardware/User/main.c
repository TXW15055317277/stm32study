#include "USART.h"
#include "m24c02_h.h"
#include <string.h>


uint8_t buffer[100] = {0};
uint8_t size = 0;

int main(void)
{
	uint8_t byte1;
	uint8_t byte2;
	uint8_t byte3;
	USART_Init_(115200);
	EEPROM_Init();
	printf("开始测试I2C...\n");

	//写入EEPROM
	EEPROM_WriteByte(0x00, 'a');
	EEPROM_WriteByte(0x01, 'b');
	EEPROM_WriteByte(0x02, 'c');
	//读取EEPROM
	byte1 = EEPROM_ReadByte(0x00);
	byte2 = EEPROM_ReadByte(0x01);
	byte3 = EEPROM_ReadByte(0x02);

	printf("a = %c\t b = %c\t c = %c\n", byte1, byte2, byte3);

	//字符串写入
	EEPROM_WriteBytes(0x00, "123456", 6);
	//字符串读取
	EEPROM_ReadBytes(0x00, buffer, 6);
	printf("str = %s\n", buffer);
	memset(buffer, 0, sizeof(buffer));
	EEPROM_WriteBytes(0x00, "1234567890abcdefghijk", 21);
	EEPROM_WriteByte(0x10, '\0');
	EEPROM_ReadBytes(0x00, buffer, 21);
	uint8_t test = EEPROM_ReadByte(0x10);
	printf("str = %s\n", buffer);
	printf("test = %c\n", test);
}
