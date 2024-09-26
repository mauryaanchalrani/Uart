/*
 * uart.h
 *
 *  Created on: 06-Sep-2024
 *      Author: ANCHAL MAURYA
 */

#ifndef SOURCE_UART_H_
#define SOURCE_UART_H_



//void Uart_Init();


void UART5_Init(void);
void UART5_SendChar(char c);
void UART5_SendString(const char* str);
#endif /* SOURCE_UART_H_ */
