#include <vega/gpio.h>
#include <vega/thejas32.h>

#define RED             8
#define GREEN           6
#define BLUE            7

int main()
{

   
    GPIO_Init(GPIOB, 8, OUT);
    GPIO_Init(GPIOB, 7, OUT);
    GPIO_Init(GPIOB, 6, OUT);



    while (1) {
        GPIO_SetPin(GPIOB, 8);
        for (int i=0; i < 0x800000; i++);
        GPIO_ResetPin(GPIOB, 8);
        for (int i=0; i < 0x800000; i++);
        
        GPIO_SetPin(GPIOB, 7);
        for (int i=0; i < 0x800000; i++);
        GPIO_ResetPin(GPIOB, 7);
        for (int i=0; i < 0x800000; i++);


        GPIO_SetPin(GPIOB, 6);
        for (int i=0; i < 0x800000; i++);
        GPIO_ResetPin(GPIOB, 6);
        for (int i=0; i < 0x800000; i++);
        
    }
    

    
}