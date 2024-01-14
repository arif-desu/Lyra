/** @file gpio.c
 *  @brief APIs related to GPIO for THEJAS32
 *  @author Arif B <arif.dev@pm.me>
 */

#include <vega/thejas32.h>
#include <vega/gpio.h>

#include <stdint.h>
#include <stdlib.h>

/*---------------------------------------------------------------------------------------------------*/

int GPIO_Init(uint16_t GPIOx, uint16_t Pin, uint16_t Direction)
{
    if (Pin < 0 || Pin > 15) {
        return -1;
    }

    if (GPIOA == GPIOx) {
        switch (Direction) {
            case 0:
                *GPIOA_DIR &= ~ (1 << Pin);
                break;
            case 1:
                *GPIOB_DIR |= 1 << Pin;
                break;
            default:
                return -1;
                break;
        }
    }
    else if (GPIOB == GPIOx) {
        switch (Direction) {
            case 0:
                *GPIOA_DIR &= ~ (1 << Pin);
                break;
            case 1:
                *GPIOB_DIR |= 1 << Pin;
                break;
            default:
                return -1;
                break;
        }
    }
    else {
        return -1;
    }

    return 0;   
}

/*---------------------------------------------------------------------------------------------------*/

int GPIO_SetPin(uint16_t GPIOx, const uint16_t Pin)
{
    if (Pin < 0 || Pin > 15) {
        return -1;
    }

    unsigned long PADDR = (1 << Pin) << 2;
    volatile unsigned long *GPIO_DATA = NULL;
    
    switch (GPIOx) {
        case GPIOA:
            GPIO_DATA = (unsigned long *) (GPIOA_DATA | PADDR) ;
            break;
        case GPIOB:
            GPIO_DATA = (unsigned long *) (GPIOB_DATA | PADDR) ;
            break;
        default:
            return -1;
    }

    *GPIO_DATA = 1 << Pin;

    return 0;
}

/*---------------------------------------------------------------------------------------------------*/

int GPIO_ResetPin(uint16_t GPIOx, const uint16_t Pin)
{
    if (Pin < 0 || Pin > 15) {
        return -1;
    }

    unsigned long PADDR = (1 << Pin) << 2;
    volatile unsigned long *GPIO_DATA = NULL;

    switch (GPIOx) {
        case GPIOA:
            GPIO_DATA = (unsigned long *) (GPIOA_DATA | PADDR) ;
            break;
        case GPIOB:
            GPIO_DATA = (unsigned long *) (GPIOB_DATA | PADDR) ;
            break;
        default:
            return -1;
    }    

    *GPIO_DATA = 0 << Pin;

    return 0;
}

/*---------------------------------------------------------------------------------------------------*/

int GPIO_TogglePin(uint16_t GPIOx, const uint16_t Pin)
{
    if (Pin < 0 || Pin > 15) {
        return -1;
    }

    unsigned long PADDR = (1 << Pin) << 2;
    volatile unsigned long *GPIO_DATA = NULL;

    switch (GPIOx) {
        case GPIOA:
            GPIO_DATA = (unsigned long *) (GPIOA_DATA | PADDR) ;
            break;
        case GPIOB:
            GPIO_DATA = (unsigned long *) (GPIOB_DATA | PADDR) ;
            break;
        default:
            return -1;
    }    
    
    *GPIO_DATA ^= 1 << Pin; 
    
    return 0;
}

/*---------------------------------------------------------------------------------------------------*/

int GPIO_ReadPin(uint16_t GPIOx, const uint16_t Pin) 
{
    if (Pin < 0 || Pin > 15) {
        return -1;
    }
    
    unsigned long PADDR = (1 << Pin) << 2;
    volatile unsigned long *GPIO_DATA = NULL;
    uint16_t data;
    
    switch (GPIOx) {
        case GPIOA:
            GPIO_DATA = (unsigned long *) (GPIOA_DATA | PADDR) ;
            break;
        case GPIOB:
            GPIO_DATA = (unsigned long *) (GPIOB_DATA | PADDR) ;
            break;
        default:
            return -1;
    } 

    data = *GPIO_DATA;

    if (data) {
        return 1;
    }
    else {
        return 0;
    }
}

/*---------------------------------------------------------------------------------------------------*/



