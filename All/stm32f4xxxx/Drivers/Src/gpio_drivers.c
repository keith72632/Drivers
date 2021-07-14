/*
 * gpio_drivers.c
 *
 *  Created on: Jul 13, 2021
 *      Author: keith
 */

#include <stdint.h>
#include "stm32f407xx.h"
#include "gpio_drivers.h"

void GpioClockInit(uint8_t pinLetter)
{
	RCC_RegDef_t *rcc = (RCC_RegDef_t *)RCC_BASEADDR;
	rcc->AHB1ENR |= (ENABLE << pinLetter);
}

void GpioPinInit(GPIO_RegDef_t *baseAddr, uint8_t pin_no, uint8_t mode)
{
	GPIO_RegDef_t *gpio = (GPIO_RegDef_t *)baseAddr;
	gpio->MODER &= ~( (CLEAR) << (2 * pin_no) );
	gpio->MODER |= ( (mode) << (2 * pin_no) );
}

void GpioSpeedInit(GPIO_RegDef_t *baseAddr, uint8_t pin_no, uint8_t speed)
{
	GPIO_RegDef_t *gpio = (GPIO_RegDef_t *)baseAddr;
	gpio->OSPEEDR &= ~( (CLEAR) << (2 * pin_no) );
	gpio->OSPEEDR |= ( (speed) << (2 * pin_no) );
}

void GpioTogglePin(GPIO_RegDef_t *baseAddr, uint8_t pin_no)
{
	GPIO_RegDef_t *gpio = (GPIO_RegDef_t *)baseAddr;
	if(!(gpio->ODR & ( (SET) << pin_no) ) )
	{
		gpio->ODR |= ( (SET) << pin_no );
	}
	else
	{
		gpio->ODR &= ~( (SET) << pin_no );
	}

}

void GpioAltFunction(GPIO_RegDef_t *baseAddr, uint8_t pin_no, uint8_t mode)
{
	int n, pos;

	switch(pin_no)
	{
	case 8:
		n = AFRH8;
		break;
	case 9:
		n = AFRH9;
		break;
	case 10:
		n = AFRH10;
		break;
	case 11:
		n = AFRH11;
		break;
	case 12:
		n = AFRH12;
		break;
	case 13:
		n = AFRH13;
		break;
	case 14:
		n = AFRH14;
		break;
	case 15:
		n = AFRH15;
		break;
	}

	//pos == pin number * 4 UNLESS pin number is 0
	pos = pin_no == 0 ? 3 : (4 * pin_no);

	GPIO_RegDef_t *gpio = (GPIO_RegDef_t *)baseAddr;
	if(pin_no <= 7)
		gpio->AFR[0] |= ( (mode) << (pos) );
	else
		gpio->AFR[1] |= ( (mode) << (n) );
}
