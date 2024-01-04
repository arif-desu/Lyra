#include <vega/gpio.h>
#include <vega/thejas32.h>

int main()
{
    GPIO_Init(GPIOB, 8, GPIO_OUT);
    GPIO_Init(GPIOB, 7, GPIO_OUT);
    GPIO_Init(GPIOB, 6, GPIO_OUT);

    while (1) {
        GPIO_ResetPin(GPIOB, 8);
        for (int i=0; i < 0x800000; i++);
        GPIO_SetPin(GPIOB, 8);
        for (int i=0; i < 0x800000; i++);
        
        GPIO_ResetPin(GPIOB, 7);
        for (int i=0; i < 0x800000; i++);
        GPIO_SetPin(GPIOB, 7);
        for (int i=0; i < 0x800000; i++);


        GPIO_ResetPin(GPIOB, 6);
        for (int i=0; i < 0x800000; i++);
        GPIO_SetPin(GPIOB, 6);
        for (int i=0; i < 0x800000; i++);
        
    }

    return 0;
}