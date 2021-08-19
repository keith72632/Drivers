/*
 * spi_drivers.h
 *
 *  Created on: Jul 18, 2021
 *      Author: keith
 */
#include <stdint.h>
#include "stm32f407xx.h"

#ifndef INCLUDES_SPI_DRIVERS_H_
#define INCLUDES_SPI_DRIVERS_H_

#define SPI_NSS_LOW() (GPIOA->ODR &= ~(1 << 4))
#define SPI_NSS_HIGH() (GPIOA->ODR |= (1 << 4))

void SPI_Init(SPI_RegDef_t *SPIx);
void SPI1_Receive(SPI_RegDef_t *SPIx, uint8_t *rxBuffer, uint8_t len);

#endif /* INCLUDES_SPI_DRIVERS_H_ */
