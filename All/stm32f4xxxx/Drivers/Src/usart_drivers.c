/*
 * uart_drivers.c
 *
 *  Created on: Jul 13, 2021
 *      Author: keith
 */
#include <stdio.h>
#include <usart_drivers.h>
#include "stm32f407xx.h"


void UsartTwoInit(uint32_t baud_rate)
{
	//BaudRate 9600. Mantissa = 104(0x68). Fraction = .166(0x3);
	USART2->BRR = baud_rate;
	USART2->CR1 |= (SET << USART_CR1_TE) | (SET << USART_CR1_RE);

	//Enable USART
	USART2->CR1 |= (SET << USART_CR1_UE);
}

/***Usart Write Functions***/

void usart_putc(char c)
{
	while(!(USART2->SR & (1 << 7))){};
	USART2->DR = c;
}

void usart_puts(char *s, uint32_t len, uint8_t new_line)
{
	while(len--)
	{
		usart_putc(*s++);
	}

	if(new_line)
	{
		usart_putc('\n');
		usart_putc('\r');
	}
}

/***Usart Read Functions***/

uint8_t usart_getc()
{
	uint8_t c;
	while(!(USART2->SR & (1 << 5))){};

	c = USART2->DR;

	return c;
}
