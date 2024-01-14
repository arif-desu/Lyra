/** @file gpio.h
 *  @brief Header file for APIs to use GPIO Ports.
 *  @author Arif B <arif.dev@pm.me>
 */
#ifndef GPIO_H
#define GPIO_H

#include <vega/thejas32.h>
#include <stdint.h>

#define GPIOA 			(0U)
#define GPIOB		    (1U)

#define OUT             (1U)
#define IN              (1U)

/*---------------------------------------------------------------------------------------------------*/

/* Initializes GPIO pin to be used in digital input or output according to Direction */
int GPIO_Init(uint16_t GPIOx, uint16_t Pin, uint16_t Direction);

/*---------------------------------------------------------------------------------------------------*/

/* Sets GPIO pin logical High */
int GPIO_SetPin(uint16_t GPIOx, uint16_t Pin);

/*---------------------------------------------------------------------------------------------------*/

/* Sets GPIO pin logical Low */
int GPIO_ResetPin(uint16_t GPIOx, uint16_t Pin);

/*---------------------------------------------------------------------------------------------------*/

/* Toggles GPIO pin from last state */
int GPIO_TogglePin(uint16_t GPIOx, uint16_t Pin);

/*---------------------------------------------------------------------------------------------------*/

/* Reads data at GPIO pin */
int GPIO_ReadPin(uint16_t GPIOx, uint16_t Pin);

/*---------------------------------------------------------------------------------------------------*/

#endif /* GPIO_H */
