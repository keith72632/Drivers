/*
 * spi.c
 *
 *  Created on: Jul 6, 2021
 *      Author: keith
 */


#include "stm32f407xx_spi.h"

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pSPIx == SPI1)
            SPI1_PCLK_EN();
        else if(pSPIx == SPI2)
            SPI2_PCLK_EN();
        else if(pSPIx == SPI3)
            SPI3_PCLK_EN();
        else if(pSPIx == SPI4)
            SPI4_PCLK_EN();
    }
    else
    {
        if(pSPIx == SPI1)
            SPI1_PCLK_DIS();
        else if(pSPIx == SPI2)
            SPI2_PCLK_DIS();
        else if(pSPIx == SPI3)
            SPI3_PCLK_DIS();
        else if(pSPIx == SPI4)
            SPI4_PCLK_DIS();
    }
};

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
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

void SPI_DeInit(SPI_RegDef_t *pSPIx)
{

};

//Data transmission(Non-interrupt based)
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len)
{
	while(len > 0)
	{
		//Wait until txe is 1 (empty)
		while(!(pSPIx->SR & (1 << SPI_SR_TXE))){};

		//Check the DFF bit
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			//16 bit
			pSPIx->DR = *(uint16_t *)pTxBuffer;
			len--;
			len--;
			(uint16_t*)pTxBuffer++;
		}
		else
		{
			//8 bit
			pSPIx->DR = *pTxBuffer;
			len--;
			pTxBuffer++;
		}
	}
};

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t len)
{
	while(len > 0)
	{
		//Wait until txe is 1 (empty)
		while(!(pSPIx->SR & (1 << SPI_SR_RXNE))){};

		//Check the DFF bit
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF))
		{
			//16 bit
			*(uint16_t *)pRxBuffer = pSPIx->DR;
			len--;
			len--;
			(uint16_t*)pRxBuffer++;
		}
		else
		{
			//8 bit
			*pRxBuffer = pSPIx->DR;
			len--;
			pRxBuffer++;
		}
	}
};

int SPI_VerifyResponse(uint8_t ack_byte)
{
	if(ack_byte == 0xf5)
	{
		return 1;
	}
	else
	{
		return 0;
	}
};


//IRQ configuration  and ISR handling
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{

};

void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{

};

void SPI_IRQHandling(SPI_Handle_t *pHandle)
{

};
