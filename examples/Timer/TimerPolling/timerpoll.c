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

    GPIO_Init(GPIOB, 12, OUT);

    Timer_Init(TIMER1, TIMER_MODE_PERIODIC, 25*1000*500);
    
    Timer_Start(TIMER1);

    while (1) {
        GPIO_TogglePin(GPIOB, RED);
        //wait till timer counter decrements to 0
        while (Timer_GetCount(TIMER1) != 0);  
    }
    
    return 0;
}






/*

// This would be a hybrid approach - polling the interrupt status of the timer
// Note this is the local Interrupt the timer produces in it's own domain, without registering in PLIC

int main()
{

    for (int i = 6; i < 9; i++) {
        GPIO_Init(GPIOB, i, OUT);
        GPIO_SetPin(GPIOB, i);
    }

    // Factor=100 for 1us when using timer with interrupt enabled
    // *1000 for 1ms, *500 for 500ms
    Timer_Init_IT(TIMER1, TIMER_MODE_PERIODIC, 100*1000*500);
    
    Timer_Start(TIMER1);

    while (1) {
        GPIO_TogglePin(GPIOB, RED);
        
        while (TIMER1->ISR != 0x1);

        // Clear interrupt 
        Timer_ClearInterrupt(TIMER1);
    }
    
    return 0;
}

*/


