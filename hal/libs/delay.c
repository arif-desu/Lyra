#include <vega/delay.h>
#include <vega/thejas32.h>

/*---------------------------------------------------------------------------------------------------*/

__attribute__((weak)) void delayus(uint32_t time)
{
    TIMER0->CTRL = 0;
    TIMER0->LOAD = time * 100;
    TIMER0->CTRL |= TIMER_CTRL_MODE_1 | TIMER_CTRL_EN;
    while (! (TIMER0->ISR & 0x1UL));
}

/*---------------------------------------------------------------------------------------------------*/

__attribute__((weak)) void delayms(uint32_t time)
{
    TIMER0->CTRL = 0;
    TIMER0->LOAD = time * 100000;
    TIMER0->CTRL |= TIMER_CTRL_MODE_1 | TIMER_CTRL_EN;
    while (! (TIMER0->ISR & 0x1UL));
}

/*---------------------------------------------------------------------------------------------------*/