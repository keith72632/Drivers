/*
 * uart_drivers.h
 *
 *  Created on: Jul 13, 2021
 *      Author: keith
 */

#ifndef INCLUDES_USART_DRIVERS_H_
#define INCLUDES_USART_DRIVERS_H_

#define NO_NEW_LINE         0
#define NEW_LINE            1

enum {
	BAUD_RATE_9600 = 0x0683
};

void UsartTwoInit(uint32_t baud_rate);
void usart_putc(char c);
void usart_puts(char *s, uint8_t new_line);

#endif /* INCLUDES_USART_DRIVERS_H_ */
