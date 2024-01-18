#include <vega/gpio.h>
#include <vega/thejas32.h>
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

    Timer_Init(TIMER1, TIMER_MODE_PERIODIC, 50000*500);
    

    while (1) {
        GPIO_TogglePin(GPIOB, RED);
        Timer_Start(TIMER1);
        while (GLOBAL_TIMER_RAWINT_STATUS != TIMER1_RAWINT_STATUS);
        Timer_Stop(TIMER1);        
    }
    
    return 0;
}




/*
int main()
{

    for (int i = 6; i < 9; i++) {
        GPIO_Init(GPIOB, i, OUT);
        GPIO_SetPin(GPIOB, i);
    }

    Timer_Init_IT(TIMER1, TIMER_MODE_PERIODIC, 100000*500);
    
    Timer_Start(TIMER1);

    while (1) {
        GPIO_TogglePin(GPIOB, RED);
        
        while (TIMER1->ISR != 0x1);
        Timer_ClearInterrupt(TIMER1);
    }
    
    return 0;
}

*/