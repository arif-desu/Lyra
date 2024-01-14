#include <vega/gpio.h>
#include <vega/timer.h>

#define RED             8
#define GREEN           6
#define BLUE            7

#define RED_SET         GPIO_ResetPin(GPIOB, RED)
#define RED_RST         GPIO_SetPin(GPIOB,RED)

#define GREEN_SET       GPIO_ResetPin(GPIOB, GREEN)
#define GREEN_RST       GPIO_SetPin(GPIOB, GREEN)

#define BLUE_SET        GPIO_ResetPin(GPIOB, BLUE)
#define BLUE_RST        GPIO_SetPin(GPIOB, BLUE)


int main()
{

    for (int i = 6; i < 9; i++) {
        GPIO_Init(GPIOB, i, OUT);
        GPIO_SetPin(GPIOB, i);
    }


    while (1) {
        RED_SET;
        delayms(1000);
        RED_RST;
        delayms(1000);

        GREEN_SET;
        delayms(1000);
        GREEN_RST;
        delayms(1000);

        BLUE_SET;
        delayms(1000);
        BLUE_RST;
        delayms(1000); 
    }
    
    return 0;
}