#include <vega/gpio.h>
#include <vega/interrupt.h>
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
    GPIO_Init(GPIOB, RED, OUT);
    RED_RST;

    GPIO_Init(GPIOA, 3, IN);

    __enable_irq();
    PLIC_Enable(GPIO3_IRQn);

    while (1) {
    
    }

    return 0;
}


void GPIO3_IRQHandler()
{
    delayms(150);
    // or choose your preferred method of debouncing
    GPIO_TogglePin(GPIOB, RED);

}