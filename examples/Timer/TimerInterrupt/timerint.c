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

#define MICROS(time)        (time * 100)
#define MILLIS(time)        (time * 100000)          


int main()
{
    
    for (int i = 6; i < 9; i++) {
        GPIO_Init(GPIOB, i, OUT);
        GPIO_SetPin(GPIOB, i);
    }
    
    //enable interrupts globally
    __enable_irq();

    Timer_Init(&htimer0, MILLIS(250));
    Timer_Init(&htimer1, MILLIS(500));
    Timer_Init(&htimer2, MILLIS(750));

    Timer_Start_IT(&htimer0);
    Timer_Start_IT(&htimer1);
    Timer_Start_IT(&htimer2); 

    while (1) {
        //infinite loop
    }
    
    return 0;
}

void TIMER0_IRQHandler()
{
    Timer_ClearInt(&htimer0);
    GPIO_TogglePin(GPIOB, RED);
}

void TIMER1_IRQHandler()
{
    Timer_ClearInt(&htimer1);
    GPIO_TogglePin(GPIOB, GREEN);
}

void TIMER2_IRQHandler()
{
    Timer_ClearInt(&htimer2);
    GPIO_TogglePin(GPIOB, BLUE);
}