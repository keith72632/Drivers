/*
 * gpio_drivers.h
 *
 *  Created on: Jul 13, 2021
 *      Author: keith
 */
#include <stdint.h>
#include "stm32f407xx.h"
#ifndef INCLUDES_GPIO_DRIVERS_H_
#define INCLUDES_GPIO_DRIVERS_H_

#define LOW                     0
#define HIGH                    1
#define CLEAR                   3

#define GPIO_A_CLK              0
#define GPIO_B_CLK              1
#define GPIO_C_CLK              2
#define GPIO_D_CLK              3
#define GPIO_E_CLK              4

#define GPIO_PIN_0              0
#define GPIO_PIN_1              1
#define GPIO_PIN_2              2
#define GPIO_PIN_3              3
#define GPIO_PIN_4              4
#define GPIO_PIN_5              5
#define GPIO_PIN_6              6
#define GPIO_PIN_7              7
#define GPIO_PIN_8              8
#define GPIO_PIN_9              9
#define GPIO_PIN_10             10
#define GPIO_PIN_11             11
#define GPIO_PIN_12             12
#define GPIO_PIN_13             13
#define GPIO_PIN_14             14
#define GPIO_PIN_15             15

#define GPIO_INPUT              0
#define GPIO_OUTPUT             1
#define GPIO_ALT                2
#define GPIO_ANAL               3

#define GPIO_ALT_FUNCTION_5     5

#define AFRH8                   0
#define AFRH9                   4
#define AFRH10                  8
#define AFRH11                  12
#define AFRH12                  16
#define AFRH13                  20
#define AFRH14                  24
#define AFRH15                  28

/***Prototypes***/
void GpioClockInit(uint8_t pinLetter);
void GpioPinInit(GPIO_RegDef_t *baseAddr, uint8_t pin_no, uint8_t mode);
void GpioTogglePin(GPIO_RegDef_t *baseAddr, uint8_t pin_no);
void GpioAltFunction(GPIO_RegDef_t *baseAddr, uint8_t pin_no, uint8_t mode);
void GpioSpeedInit(GPIO_RegDef_t *baseAddr, uint8_t pin_no, uint8_t speed);

#endif /* INCLUDES_GPIO_DRIVERS_H_ */
