/** @file gpio.c
 *  @brief APIs related to GPIO for THEJAS32
 *  @author Arif B <arif.dev@pm.me>
 */

#include <vega/thejas32.h>
#include <vega/gpio.h>

#include <stdint.h>

void GPIO_Init(uint32_t GPIOx, uint32_t Pin, uint32_t Direction)
{
    if (0 == GPIOx) {
        switch (Direction) {
            case 0:
                *GPIOA_DIR &= ~ (1 << Pin);
                break;
            case 1:
                *GPIOB_DIR |= 1 << Pin;
                break;
            default:
                break;
        }
    }
    else if (1 == GPIOx) {
        switch (Direction) {
            case 0:
                *GPIOA_DIR &= ~ (1 << Pin);
                break;
            case 1:
                *GPIOB_DIR |= 1 << Pin;
                break;
            default:
                break;
        }
    }
    
}

void GPIO_SetPin(uint32_t GPIOx, const uint32_t Pin)
{
    unsigned long PADDR = (1 << Pin) << 2;
    __IO unsigned long *GPIO_DATA;

    if (0 == GPIOx) {
        GPIO_DATA = (unsigned long *) (GPIOA_DATA | PADDR) ;
    }
    else if (1 == GPIOx) {
        GPIO_DATA = (unsigned long *) (GPIOB_DATA | PADDR) ;
    }  

    *GPIO_DATA = 1 << Pin; 
}

void GPIO_ResetPin(uint32_t GPIOx, const uint32_t Pin)
{
    unsigned long PADDR = (1 << Pin) << 2;
    __IO unsigned long *GPIO_DATA;

    if (0 == GPIOx) {
        GPIO_DATA = (unsigned long *) (GPIOA_DATA | PADDR) ;
    }
    else if (1 == GPIOx) {
        GPIO_DATA = (unsigned long *) (GPIOB_DATA | PADDR) ;
    }    

    *GPIO_DATA = 0 << Pin;

}

void GPIO_TogglePin(uint32_t GPIOx, const uint32_t Pin)
{
    if (0 != GPIOx && Pin >= 0 && Pin <= 15)
    {
        unsigned long PADDR = (1 << Pin) << 2;
        __IO unsigned long *GPIO_DATA;

        if (0 == GPIOx) {
            GPIO_DATA = (unsigned long *) (GPIOA_DATA | PADDR) ;       
        }
        else if (1 == GPIOx) {
            GPIO_DATA = (unsigned long *) (GPIOB_DATA | PADDR) ;
        }
        *GPIO_DATA ^= 1 << Pin; 
    }

}

int GPIO_ReadPin(uint32_t GPIOx, const uint32_t Pin) 
{
    unsigned long PADDR = (1 << Pin) << 2;
    __IO unsigned long *GPIO_DATA;
    uint32_t data;
    
    if (0 == GPIOx) {
            GPIO_DATA = (unsigned long *) (GPIOA_DATA | PADDR) ;       
    }
    else if (1 == GPIOx) {
            GPIO_DATA = (unsigned long *) (GPIOB_DATA | PADDR) ;
    }

    data = *GPIO_DATA;

    if (data) {
        return 1;
    }
    else {
        return 0;
    }
    

    
}



