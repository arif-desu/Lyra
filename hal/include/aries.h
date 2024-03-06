#ifndef ARIES_H
#define ARIES_H

#include <vega/thejas32.h>
#include <vega/gpio.h>

#define RGB_RED             (8)
#define RGB_GREEN           (6)
#define RGB_BLUE            (7)

#define RGB_RED_SET         (GPIO_ResetPin(GPIOB, RGB_RED))
#define RGB_RED_RST         (GPIO_SetPin(GPIOB, RGB_RED))

#define RGB_GREEN_SET       (GPIO_ResetPin(GPIOB, RGB_GREEN))
#define RGB_GREEN_RST       (GPIO_SetPin(GPIOB, RGB_GREEN))

#define RGB_BLUE_SET        (GPIO_ResetPin(GPIOB, RGB_BLUE))
#define RGB_BLUE_RST        (GPIO_SetPin(GPIOB, RGB_BLUE))

#ifdef ARIESV2

#define BTN0                (3)
#define BTN1                (2)

#define IS_BTN0_ON             (GPIO_ReadPin(GPIOB, BTN0) == 0)  
#define IS_BTN1_ON             (GPIO_ReadPin(GPIOB, BTN1) == 0)  
#define IS_BTN0_OFF            (GPIO_ReadPin(GPIOB, BTN0) == 1)  
#define IS_BTN1_OFF            (GPIO_ReadPin(GPIOB, BTN1) == 1)  

#endif

#endif