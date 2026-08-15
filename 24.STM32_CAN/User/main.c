#include "USART.h"
#include "CAN.h"
#include "LCD.h"

int main(void)
{
    USART_Init_(115200);
    CAN_INIT_();
    CAN_Filter_Init_();
    LCD_Init_();

    CAN_TXMsg_(0x0010, 5, "12345");
    CAN_TXMsg_(0x0011, 6, "abcdef");
    CAN_TXMsg_(0x0022, 7, "woshini");

    Msg_ MSG_RX[3];
    uint8_t data_num = 0;              // normal variable, not pointer
    CAN_RXMsg_(MSG_RX, &data_num);     // pass its address
    printf("Message count: %d\r\n", data_num);
    for (uint8_t n = 0; n < data_num; n++)
    {
        printf("MessageID[%d]: ", n);
        printf("%#x", MSG_RX[n].ID);
        printf("\r\n");
        printf("Message[%d]: ", n);
        for (uint8_t i = 0; i < MSG_RX[n].data_len; i++)
            printf("%c", MSG_RX[n].data[i]);
        printf("\r\n");
        LCD_SHOW_STRING(0, 32 * n, 32, MSG_RX[n].data, BLACK, WHITE);
    }
}
