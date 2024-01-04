/** @file gpio.h
 *  @brief Header file for APIs to use GPIO Ports.
 *
 *  @author Arif B <arif.dev@pm.me>
 */

#include <vega/thejas32.h>
#include <stdint.h>


#ifndef GPIO_H
#define GPIO_H


#define GPIO_OUT             1
#define GPIO_IN              0

/*---------------------------------------------------------------------------------------------------*/

/* Initializes GPIO pin to be used in digital input or output according to Direction */
void GPIO_Init(uint8_t GPIOx, uint8_t Pin, uint8_t Direction);

/*---------------------------------------------------------------------------------------------------*/

/* Sets GPIO pin logical High */
void GPIO_SetPin(uint8_t GPIOx, uint8_t Pin);

/*---------------------------------------------------------------------------------------------------*/

/* Reads data at GPIO pin

Returns -1 if invalid GPIO or Pin is passed 
*/
int GPIO_ReadPin(uint8_t GPIOx, uint8_t Pin);

/*---------------------------------------------------------------------------------------------------*/

/* Sets GPIO pin logical Low */
void GPIO_ResetPin(uint8_t GPIOx, uint8_t Pin);

/*---------------------------------------------------------------------------------------------------*/

/* Toggles GPIO pin from last state */
void GPIO_TogglePin(uint8_t GPIOx, uint8_t Pin);

/*---------------------------------------------------------------------------------------------------*/


#endif /* GPIO_H */
