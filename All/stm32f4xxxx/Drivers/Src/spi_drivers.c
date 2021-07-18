/*
 * spi_drivers.c
 *
 *  Created on: Jul 18, 2021
 *      Author: keith
 */

#include "stm32f407xx.h"


void SPI_Init(SPI_RegDef_t *SPIx)
{
	/*
	 * SPI Config. 2 directional line. MSB first. 8 bit data format. Software slave managment disabled.
	 */


	SPIx->CR1 |= (SET << SPI_CR1_CPHA) | (SET << SPI_CR1_MSTR);

	SPIx->CR1 |= (5 << SPI_CR1_BR); //prescaler to 64

	SPIx->CR1 |= (SET << SPI_CR1_SPE);


}

