/*
 * spi_drivers.c
 *
 *  Created on: Jul 18, 2021
 *      Author: keith
 */
#include <stdint.h>
#include "stm32f407xx.h"
#include "gpio_drivers.h"

void SPI_PinInit(GPIO_RegDef_t *GPIOx)
{
	GPIOx->MODER |= ( (SET) << (2 * GPIO_PIN_4) );
	GPIOx->MODER |= ( (GPIO_ALT) << (2 * GPIO_PIN_5) ) | ( (GPIO_ALT) << (2 * GPIO_PIN_6) ) | ( (GPIO_ALT) << (2 * GPIO_PIN_7) );

	GPIOx->AFR[0] |= (5 << 20) | (5 << 24) | (5 << 28);

	//Set nss pin as high
//	GPIOx->ODR |= (SET << GPIO_PIN_4);
}


void SPI_Init(SPI_RegDef_t *SPIx)
{
	 SPI_PinInit(GPIOA);
	/*
	 * SPI Config. 2 directional line. MSB first. 8 bit data format. Software slave managment disabled.
	 */


	SPIx->CR1 |= (SET << SPI_CR1_CPHA) | (SET << SPI_CR1_MSTR);

	SPIx->CR1 |= (5 << SPI_CR1_BR); //prescaler to 64

	SPIx->CR1 |= (SET << SPI_CR1_SPE);


}

void SPI1_Receive(SPI_RegDef_t *SPIx, uint8_t *rxBuffer, uint32_t len)
{
	while(len > 0)
	{
		while(!(SPIx->SR & (1 << SPI_SR_RXNE))){};

		if(SPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			*(uint16_t *)rxBuffer = SPIx->DR;
			len--;
			len--;
			(uint16_t *)rxBuffer++;
		}
		else
		{
			*rxBuffer = SPIx->DR;
			len--;
			rxBuffer++;
		}
	}
}

