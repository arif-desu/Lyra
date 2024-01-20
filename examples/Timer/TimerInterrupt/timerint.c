#include <vega/gpio.h>
#include <vega/interrupt.h>
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



void TIMER0_IRQHandler()
{
    Timer_ClearInterrupt(TIMER0);
    GPIO_TogglePin(GPIOB, RED);
}
void TIMER1_IRQHandler()
{
    Timer_ClearInterrupt(TIMER1);
    GPIO_TogglePin(GPIOB, GREEN);

}

void TIMER2_IRQHandler()
{
    Timer_ClearInterrupt(TIMER2);
    GPIO_TogglePin(GPIOB, BLUE);
}

int main()
{
    
    for (int i = 6; i < 9; i++) {
        GPIO_Init(GPIOB, i, OUT);
        GPIO_SetPin(GPIOB, i);
    }

    

    Timer_Init_IT(TIMER0, TIMER_MODE_PERIODIC, 25000000);
    Timer_Init_IT(TIMER1, TIMER_MODE_PERIODIC, 50000000);
    Timer_Init_IT(TIMER2, TIMER_MODE_PERIODIC, 75000000);
    
    //enable interrupts globally
    __enable_irq();

    //Enable interrupts for timers in PLIC
    PLIC_Enable(TIMER0_IRQn);
    PLIC_Enable(TIMER1_IRQn);
    PLIC_Enable(TIMER2_IRQn);

    
    Timer_Start(TIMER0);
    Timer_Start(TIMER1);
    Timer_Start(TIMER2);


    while (1) {
        //infinite loop
        
    }
    
    return 0;
}

