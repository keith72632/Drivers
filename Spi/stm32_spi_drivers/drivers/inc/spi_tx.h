/*
 * spi_tx.h
 *
 *  Created on: Jul 8, 2021
 *      Author: keith
 */

#ifndef INC_SPI_TX_H_
#define INC_SPI_TX_H_

void Gpio_Init_TX(void);
void TX_SPI_Activate(SPI_Handle_t *pSPIHandle);
void TX_Spi_Init(void);
void SPI_SSOE(SPI_RegDef_t *SPIx, uint8_t EnorDi);

#endif /* INC_SPI_TX_H_ */
