/** @file gpio.h
 *  @brief Header file for APIs to use GPIO Ports.
 *
 *  @author Arif B <arif.dev@pm.me>
 */
#ifndef GPIO_H
#define GPIO_H

#include <vega/thejas32.h>
#include <stdint.h>

#define OUT             1
#define IN              0

/*---------------------------------------------------------------------------------------------------*/

/* Initializes GPIO pin to be used in digital input or output according to Direction */
void GPIO_Init(uint32_t GPIOx, uint32_t Pin, uint32_t Direction);

/*---------------------------------------------------------------------------------------------------*/

/* Sets GPIO pin logical High */
void GPIO_SetPin(uint32_t GPIOx, uint32_t Pin);

/*---------------------------------------------------------------------------------------------------*/

/* Reads data at GPIO pin

Returns -1 if invalid GPIO or Pin is passed 
*/
int GPIO_ReadPin(uint32_t GPIOx, uint32_t Pin);

/*---------------------------------------------------------------------------------------------------*/

/* Sets GPIO pin logical Low */
void GPIO_ResetPin(uint32_t GPIOx, uint32_t Pin);

/*---------------------------------------------------------------------------------------------------*/

/* Toggles GPIO pin from last state */
void GPIO_TogglePin(uint32_t GPIOx, uint32_t Pin);

/*---------------------------------------------------------------------------------------------------*/


#endif /* GPIO_H */
