/** @file gpio.c
 *  @brief APIs related to GPIO for THEJAS32
 *  @author Arif B <arif.dev@pm.me>
 */


#include <vega/thejas32.h>
#include <vega/gpio.h>

#include <stdint.h>

void GPIO_Init(uint8_t GPIOx, uint8_t pin, uint8_t direction)
{
    if (0 == GPIOx) {
        switch (direction) {
            case 0:
                GPIOA_DIR &= ~ (1 << pin);
                break;
            case 1:
                GPIOB_DIR |= 1 << pin;
                break;
            default:
                break;
        }
    }
    else if (1 == GPIOx) {
        switch (direction) {
            case 0:
                GPIOA_DIR &= ~ (1 << pin);
                break;
            case 1:
                GPIOB_DIR |= 1 << pin;
                break;
            default:
                break;
        }
    }
    
}

void GPIO_SetPin(uint8_t GPIOx, const uint8_t pin)
{
    unsigned long PADDR = (1 << pin) << 2;
    __IO unsigned long *GPIO_DATA_R;

    if (0 == GPIOx) {
        GPIO_DATA_R = (unsigned long *) (GPIO_PORTA | PADDR) ;
        *GPIO_DATA_R = 1 << pin;
    }
    else if (1 == GPIOx) {
        GPIO_DATA_R = (unsigned long *) (GPIO_PORTB | PADDR) ;
        *GPIO_DATA_R = 1 << pin;
    }    
}

void GPIO_ResetPin(uint8_t GPIOx, const uint8_t pin)
{
    unsigned long PADDR = (1 << pin) << 2;
    __IO unsigned long *GPIO_DATA_R;

    if (0 == GPIOx) {
        GPIO_DATA_R = (unsigned long *) (GPIO_PORTA | PADDR) ;
        *GPIO_DATA_R = 0 << pin;
    }
    else if (1 == GPIOx) {
        GPIO_DATA_R = (unsigned long *) (GPIO_PORTB | PADDR) ;
        *GPIO_DATA_R = 0 << pin;
    }    
}

void GPIO_TogglePin(uint8_t GPIOx, const uint8_t Pin)
{
    if (0 != GPIOx && Pin >= 0 && Pin <= 15)
    {
        unsigned long PADDR = (1 << Pin) << 2;
        __IO unsigned long *GPIO_DATA_R;

        if (0 == GPIOx) {
            GPIO_DATA_R = (unsigned long *) (GPIO_PORTA | PADDR) ;
            *GPIO_DATA_R ^= Pin;
        }
        else if (1 == GPIOx) {
            GPIO_DATA_R = (unsigned long *) (GPIO_PORTB | PADDR) ;
            *GPIO_DATA_R ^= Pin;
        }    
    }
}

//TODO
int GPIO_ReadPin(uint8_t GPIOx, const uint8_t Pin) 
{
    return -1;
}



