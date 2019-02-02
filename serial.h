
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __serial_H
#define __serial_H

#include "usart.h"

void Debug_Print_String(UART_HandleTypeDef *huart, char _out[]);
void Debug_Print_String_ln(UART_HandleTypeDef *huart, char _out[]);
void Debug_Print_Integer_ln(UART_HandleTypeDef *huart, int _out);

void Uart_Send_Demo_Strings(UART_HandleTypeDef *huart);
void Uart_Receive_Demo_Strings(UART_HandleTypeDef *huart);
void Uart_Send_Demo_ASCII_Art(UART_HandleTypeDef *huart);

#endif /*__serial_H */
