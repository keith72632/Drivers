/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "mem.h"
#include "usart_drivers.h"
#include "gpio_drivers.h"
#include "spi_drivers.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

/***Prototyes***/
void GpioInit(void);
void UsartInit(uint32_t baud_rate);
void SPI1_ClockInit(void);

int main(void)
{

	GpioInit();

	SPI1_ClockInit();

	SPI_Init(SPI1);

	UsartInit(BAUD_RATE_9600);

    /* Loop forever */
	while(1)
	{
		uint8_t c;
		char string[] = "hello";
		char message[] = "If c, it worked!";
		uint8_t len = strlen(string);
		usart_puts(string, len, NEW_LINE);

		GpioTogglePin(GPIOD, 15);

		for(int i = 0; i < 1000000; i++){};

		GpioTogglePin(GPIOD, 15);
		c = usart_getc();
		usart_puts(message, strlen(message), NEW_LINE);

		usart_putc(c | 32);


		for(int i = 0; i < 1000000; i++){};
	}
}

void GpioInit()
{
	GPIOD_PCLK_EN();

	GpioPinInit(GPIOD, 15, (uint8_t)GPIO_OUTPUT);

}

void UsartInit(uint32_t baud_rate)
{
	//PA2 USART_TX. PA3 USART_RX. Alternate Function F7(0x07)
	GPIOA_PCLK_EN();

	GpioPinInit(GPIOA, 2, (uint8_t)GPIO_ALT);
	GpioPinInit(GPIOA, 3, (uint8_t)GPIO_ALT);

	GpioAltFunction(GPIOA, 2, 7);
	GpioAltFunction(GPIOA, 3, 7);

	GpioSpeedInit(GPIOA, 2, 3);
	GpioSpeedInit(GPIOA, 3, 3);

	USART2_PCCK_EN();

	UsartTwoInit(baud_rate);

}

void SPI1_ClockInit()
{
	GPIOA_PCLK_EN();

	SPI1_PCLK_EN();
}
