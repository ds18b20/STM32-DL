/* Ref:
 * https://simonmartin.ch/resources/stm32/dl/STM32%20Tutorial%2003%20-%20UART%20Communication%20using%20HAL%20(and%20FreeRTOS).pdf
 * */
#include "usart.h"
#include "serial.h"
#include <string.h>

//extern UART_HandleTypeDef huart1;
  char buffer[16];

/* print a string */
void Debug_Print_String(UART_HandleTypeDef *huart, char _out[])
{
  uint32_t time_out = 1000 * strlen(_out) * (8 + 1) / huart->Init.BaudRate;  // round to N Ms
  HAL_UART_Transmit(huart, (uint8_t *) _out, strlen(_out), time_out + 1);
}

/* print a string followed by a 0x0A 0x0D */
void Debug_Print_String_ln(UART_HandleTypeDef *huart, char _out[])
{
  Debug_Print_String(huart, _out);
  Debug_Print_String(huart, "\r\n");
}

/* print a integer */
void Debug_Print_Integer_ln(UART_HandleTypeDef *huart, int _out)
{
  HAL_UART_Transmit(huart, (uint8_t*)buffer, sprintf(buffer, "%d", _out), 100);
  Debug_Print_String(huart, "\r\n");
}

/* send strings Demo */
void Uart_Send_Demo_Strings(UART_HandleTypeDef *huart)
{
  Debug_Print_String_ln(huart, "Hello world!");
  Debug_Print_String_ln(huart, "This is a UART test.");
}

/* send SCII Art Demo */
void Uart_Send_Demo_ASCII_Art(UART_HandleTypeDef *huart)
{
  Debug_Print_String_ln(huart, "                     _|_");
  Debug_Print_String_ln(huart, "                 --o-(_)-o--");
  Debug_Print_String(huart, "\r\n");
  Debug_Print_String_ln(huart, "       --|--");
  Debug_Print_String_ln(huart, "*--o--o-(_)-o--o--*");
}

/* receive strings Demo */
void Uart_Receive_Demo_Strings(UART_HandleTypeDef *huart)
{
  Debug_Print_String_ln(huart, "Type something:");
  char in[8];
  HAL_UART_Receive(huart, (uint8_t *)in, 8, 1000);  // time_out is set to 1000 Ms
  Debug_Print_String(huart, "\n");
  HAL_UART_Transmit(huart, (uint8_t *)in, 8, 1);
  Debug_Print_String(huart, "\n");
}
