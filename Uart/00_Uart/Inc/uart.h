/*
 * uart.h
 *
 *  Created on: Jun 29, 2021
 *      Author: keith
 */
#include <stdint.h>
#ifndef UART_H_
#define UART_H_

typedef struct
{
	uint8_t USART_Mode;
	uint32_t USART_Baud;
	uint8_t USART_NoOfBitStops;
	uint8_t USART_WordLength;
	uint8_t USART_ParityControl;
	uint8_t USART_HWControl;
}USART_CONFIG_t;

typedef struct
{
	uint32_t USART_SR;
	uint32_t USART_DR;
	uint32_t USART_BRR;
	uint32_t USART_CR1;
	uint32_t USART_CR2;
	uint32_t USART_CR3;
	uint32_t USART_GTPR;
}__attribute__((packed))USART_RegDef_t;

typedef struct
{
	USART_RegDef_t *pUSARTx;
	USART_CONFIG_t USART_Config;
}USART_Handle_t;

#endif /* UART_H_ */
