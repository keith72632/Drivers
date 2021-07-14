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

void usart_putc(char c)
{
	while(!(USART2->SR & (1 << 7))){};
	USART2->DR = c;
}

void usart_puts(char *s, uint8_t new_line)
{
	uint32_t len = sizeof(s) + 1;
	while(len--)
	{
		usart_putc(*s);
		s++;
	}
	if(new_line)
	{
		usart_putc('\n');
		usart_putc('\r');
	}

    while(!(USART2->SR & 0x0040)){};
}
