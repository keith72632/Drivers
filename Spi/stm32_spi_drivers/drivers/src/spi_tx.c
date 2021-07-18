/*
 * spi_tx.c
 *
 *  Created on: Jul 8, 2021
 *      Author: keith
 */

#include "stm32f407xx_spi.h"
#include "stm32f407xx.h"

#define MOSI_PIN 15
#define SCLK_PIN 13

void Gpio_Init_TX()
{
	RCC_RegDef_t *rcc   = (RCC_RegDef_t *)0x40023800;
	GPIO_RegDef_t *pinB = (GPIO_RegDef_t*)GPIOB_BASEADDR;

	rcc->AHB1ENR &= ~(1 << 1);
	rcc->AHB1ENR |= (1 << 1);

	pinB->MODER |= (2 << (2 * SCLK_PIN)) | (2 << (2 * MOSI_PIN));
	pinB->AFR[1] |= (5 << 20) | (5 << 28);

	pinB->OSPEEDR |= (3 << (2 * SCLK_PIN)) | (3 << (2 * MOSI_PIN));
}

void TX_SPI_Activate(SPI_Handle_t *pSPIHandle)
{
	RCC_RegDef_t *rcc   = (RCC_RegDef_t *)0x40023800;
	rcc->APB1ENR |= (1 << 14);
	//Events shown by SR(status register)
	//Master produces clock
	//SCLK is only configured when master is transmitting data
	uint32_t tempreg = 0;

	//1.Configure device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR; //bit 2

	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		//bidi mode should be cleared
		tempreg &= ~(1 << SPI_CR1_BIDIMODE); //bit 15
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		//bidi mode should be set
		tempreg |= (1 << SPI_CR1_BIDIMODE); //bit 15
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_RX)
	{
		//BIDI mode should be cleared
		//RXONLY bit must be set
		tempreg &= ~(1 << SPI_CR1_BIDIMODE); //bit 15
		tempreg |= (1 << SPI_CR1_RXONLY); //bit 10
	}

	//3. Configure the spi serial clock speed (baud rate)
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR; //bit 3

	//4. Configure the DFF
	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF; //bit 11

	//5. Configure the CPOL
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL; //bit 1

	//6. Configure the CPHA
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA; //bit 0

	tempreg |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;

	pSPIHandle->pSPIx->CR1 = tempreg;
};


void TX_Spi_Init()
{
	SPI_Handle_t SPI2handle;
	SPI2handle.pSPIx = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8;
	SPI2handle.SPIConfig.SPI_DFF = SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM = SPI_SSM_DI; //DI == Hardware. SSM == 0. When SPE == 1, NSS pulled to low automatically. SPE == 1, nss pulled high automatically
	//when ssoe enabled, nss output enabled. SSOE = slave select output enabled

	TX_SPI_Activate(&SPI2handle);

}

void SPI_SSOE(SPI_RegDef_t *SPIx, uint8_t EnorDi)
{
	if(EnorDi == DISABLE)
	{
		SPIx->CR2 |= (1 << SPI_CR2_SSOE);
	}
	else
	{
		SPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
	}
}
