#ifndef __CAN_H
#define __CAN_H

#include "stm32f4xx.h"

typedef struct
{
    uint16_t ID;
    uint8_t data_len;
    uint8_t data[8];
} Msg_;

void CAN_INIT_(void);
void CAN_TXMsg_(uint16_t ID, uint8_t data_len, uint8_t *data);
void CAN_RXMsg_(Msg_ *Msg_RX, uint8_t *data_num);
void CAN_Filter_Init_(void);


#endif
