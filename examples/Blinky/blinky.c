#include <vega/hal.h>
#include <vega/aries.h>

int main()
{

    for (int i = 6; i < 9; i++) {
        GPIO_Init(GPIOB, i, GPIO_OUT);
        GPIO_SetPin(GPIOB, i);
    }

    while (1) {
        RGB_RED_SET;
        delayms(500);
        RGB_RED_RST;
        delayms(500);

        RGB_GREEN_SET;
        delayms(500);
        RGB_GREEN_RST;
        delayms(500);

        RGB_BLUE_SET;
        delayms(500);
        RGB_BLUE_RST;
        delayms(500); 
    }
    
    return 0;
}