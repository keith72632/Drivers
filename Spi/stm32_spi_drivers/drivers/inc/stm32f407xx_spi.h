/*
 * stm32f407xx_spi.h
 *
 *  Created on: Jul 6, 2021
 *      Author: keith
 */
#include <stdint.h>
#include "stm32f407xx.h"
#ifndef INC_STM32F407XX_SPI_H_
#define INC_STM32F407XX_SPI_H_

/*
 * Clock Enable Macros for SPIx peripheralsbu
 */
#define SPI1_PCLK_EN() (RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN() (RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN() (RCC->APB1ENR |= (1 << 15))
#define SPI4_PCLK_EN() (RCC->APB2ENR |= (1 << 13))

/*
 * Clock Disable Macros for SPIx
 */
#define SPI1_PCLK_DIS() (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DIS() (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DIS() (RCC->APB1ENR &= ~(1 << 15))
#define SPI4_PCLK_DIS() (RCC->APB2ENR &= ~(1 << 13))


/*
 * peripheral register definition structure for SPI
 */
typedef struct
{
	__vo uint32_t CR1;        /*!< TODO,     										Address offset: 0x00 */
	__vo uint32_t CR2;        /*!< TODO,     										Address offset: 0x04 */
	__vo uint32_t SR;         /*!< TODO,     										Address offset: 0x08 */
	__vo uint32_t DR;         /*!< TODO,     										Address offset: 0x0C */
	__vo uint32_t CRCPR;      /*!< TODO,     										Address offset: 0x10 */
	__vo uint32_t RXCRCR;     /*!< TODO,     										Address offset: 0x14 */
	__vo uint32_t TXCRCR;     /*!< TODO,     										Address offset: 0x18 */
	__vo uint32_t I2SCFGR;    /*!< TODO,     										Address offset: 0x1C */
	__vo uint32_t I2SPR;      /*!< TODO,     										Address offset: 0x20 */
} SPI_RegDef_t;

typedef struct
{
    uint8_t SPI_DeviceMode;
    uint8_t SPI_BusConfig;
    uint8_t SPI_SclkSpeed;
    uint8_t SPI_DFF;
    uint8_t SPI_CPOL;
    uint8_t SPI_CPHA;
    uint8_t SPI_SSM;
}SPI_Config_t;

typedef struct
{
    SPI_RegDef_t    *pSPIx; //Base address of the SPIx(0, 1, 2) peripheral
    SPI_Config_t    SPIConfig;
}SPI_Handle_t;

#define SPI_DEVICE_MODE_MASTER 1
#define SPI_DEVICE_MODE_SLAVE  0

//Spi Bus Conifg. Full-duplex, Half-duplex and Simplex
#define SPI_BUS_CONFIG_FD      1
#define SPI_BUS_CONFIG_HD      2
#define SPI_BUS_CONFIG_RX      3

//SPI Clock Speed. In CR1. Prescaler
#define SPI_SCLK_SPEED_DIV2    0
#define SPI_SCLK_SPEED_DIV4    1
#define SPI_SCLK_SPEED_DIV8    2
#define SPI_SCLK_SPEED_DIV16   3
#define SPI_SCLK_SPEED_DIV32   4
#define SPI_SCLK_SPEED_DIV64   5

//DFF
#define SPI_DFF_8BITS          0
#define SPI_DFF_16BITS         1

//CPOL
#define SPI_CPOL_HIGH          1
#define SPI_CPOL_LOW           0

//CPHA
#define SPI_CPHA_HIGH          1
#define SPI_CPHA_LOW           0

//SSM
#define SPI_SSM_EN             1
#define SPI_SSM_DI             0
/**************************************************************************************************
 *                                      API Prototypes                                            *
 *************************************************************************************************/

void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

//Data transmission(Non-interrupt based)
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len);
int SPI_VerifyResponse(uint8_t ack_byte);
//IRQ configuration  and ISR handling
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);
#endif /* INC_STM32F407XX_SPI_H_ */
