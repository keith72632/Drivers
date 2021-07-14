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
#include <string.h>
#include "stm32f407xx.h"
#include "stm32f407xx_spi.h"
#include "spi_tx.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
/*
 * pb14 -> SPI2 MISO
 * pb15 -> SPI2_MOSI
 * pb13 -> SPI2_SCLK
 * pb12 -> SPI2_NSS
 * Alt Function Mode: 5
 */
#define PIN12    12
#define PIN13    13
#define PIN14    14
#define PIN15    15

//For arduino send/receive
#define COMMAND_LED_CTRL       0x50
#define COMMAND_SENSOR_READ    0x51
#define COMMAND_LED_READ       0x52
#define COMMAND_PRINT          0x53
#define COMMAND_ID_READ        0x54

#define LED_ON                 1
#define LED_OFF                0

//arduino analog pins
#define ANALOG_PIN0            0
#define ANALOG_PIN1            1
#define ANALOG_PIN2            2
#define ANALOG_PIN3            3
#define ANALOG_PIN4            4

//arduino LED
#define LED_PIN                9



void SPI2_GPIOInits(void)
{
	GPIO_RegDef_t *pinB = (GPIO_RegDef_t *)GPIOB_BASEADDR;
	RCC_RegDef_t *rcc = (RCC_RegDef_t *)RCC_BASEADDR;

	rcc->AHB1ENR |= (1 << 1);

	pinB->MODER &= ~(0xffffffff);
	pinB->MODER |= (1 << (2 * PIN12)) | (2 << (2 * PIN13)) | ( 2 << (2 * PIN14)) | (2 << (2 * PIN15));

	pinB->AFR[1] |= (5 << 16) | (5 << 20) | (5 << 24) | (5 << 28);


	//output type == push pull
	pinB->OTYPER &= ~(1 << PIN13) & ~(1 << PIN15);

	pinB->OSPEEDR |= (3 << 24) | (3 << 26) | (3 << 28)| (3 <<  30);
}

void SPI2_Inits(void)
{
	RCC_RegDef_t *rcc = (RCC_RegDef_t *)RCC_BASEADDR;
	rcc->APB1ENR |= (1 << 14);
	SPI_Handle_t SPI2handle;
	SPI2handle.pSPIx                    = SPI2;
	SPI2handle.SPIConfig.SPI_BusConfig  = SPI_BUS_CONFIG_FD;
	SPI2handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2handle.SPIConfig.SPI_SclkSpeed  = SPI_SCLK_SPEED_DIV2; //8 MHz
	SPI2handle.SPIConfig.SPI_DFF        = SPI_DFF_8BITS;
	SPI2handle.SPIConfig.SPI_CPOL       = SPI_CPOL_HIGH;
	SPI2handle.SPIConfig.SPI_CPHA       = SPI_CPHA_LOW;
	SPI2handle.SPIConfig.SPI_SSM        = SPI_SSM_EN;


	SPI_Init(&SPI2handle);

}

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR1 |=  (1 << SPI_CR1_SPE);
	}else
	{
		pSPIx->CR1 &=  ~(1 << SPI_CR1_SPE);
	}


}

void  SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
	if(EnOrDi == ENABLE)
	{
		pSPIx->CR1 |=  (1 << SPI_CR1_SSI);
	}else
	{
		pSPIx->CR1 &=  ~(1 << SPI_CR1_SSI);
	}


}


int main(void)
{
	uint8_t dummy_byte = 0xff;

	//this function is used to initialize the GPIO pins to behave as SPI2 pins
	SPI2_GPIOInits();
//	Gpio_Init_TX();
	//This function is used to initialize the SPI2 peripheral parameters
	SPI2_Inits();
//	TX_Spi_Init();
	//this makes NSS signal internally high and avoids MODF error
	SPI_SSIConfig(SPI2,ENABLE);
	SPI_SSOE(SPI2, ENABLE);
	//enable the SPI2 peripheral
	SPI_PeripheralControl(SPI2,ENABLE);

	uint8_t command_code = COMMAND_LED_CTRL;
	SPI_SendData(SPI2,&command_code, 1);

	//to send data
	SPI_SendData(SPI2,&dummy_byte, 1);

	uint8_t ack_byte;
	SPI_ReceiveData(SPI2, &ack_byte, 1);

	SPI_VerifyResponse(ack_byte);

	//lets confirm SPI is not busy
	while(SPI2->SR & (1 << 7));

	//Disable the SPI2 peripheral
	SPI_PeripheralControl(SPI2,DISABLE);

	while(1);

	return 0;

}
