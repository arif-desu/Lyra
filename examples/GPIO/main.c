#include <vega/gpio.h>
#include <vega/thejas32.h>

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

    for (int i = 0; i < 9; i++) {
        GPIO_Init(GPIOB, i, OUT);
        GPIO_SetPin(GPIOB, i);
    }

    GPIO_Init(GPIOB, 3, IN);
    GPIO_Init(GPIOB, 2, IN);
    
    while (1) {
        if (GPIO_ReadPin(GPIOB, 3) == 0) {
            RED_RST;
            BLUE_RST;
            GREEN_SET;
        }
        else if (GPIO_ReadPin(GPIOB, 2) == 0) {
            RED_RST;
            GREEN_RST;
            BLUE_SET;
        }
        else {
            GREEN_RST;
            BLUE_RST;
            RED_SET;
        }
    
    }

    
    return 0;
}