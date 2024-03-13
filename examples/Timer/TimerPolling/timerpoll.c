#include <vega/hal.h>
#include <vega/aries.h>

int main()
{

    for (int i = 6; i < 9; i++) {
        GPIO_Init(GPIOB, i, GPIO_OUT);
        GPIO_SetPin(GPIOB, i);
    }

    GPIO_Init(GPIOB, RGB_RED , GPIO_OUT);

    TIMER_Init(&htimer0);
    
    TIMER_Start(&htimer0);

    while (1) {
        GPIO_TogglePin(GPIOB, RGB_RED);
        //wait till timer counter decrements to 0
        while (TIMER_GetCount(&htimer0) != 0);  
    }
    
    return 0;
}


