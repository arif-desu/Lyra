#include <vega/thejas32.h>
#include <vega/timer.h>
#include <stdint.h>
#include <stdlib.h>

int Timer_Init(Timer_Reg_t *TIMERx, uint16_t Mode, uint32_t Val)
{
    if (NULL == TIMERx) {
        return -1;
    }
    TIMERx->CTRL = 0;

    TIMERx->LOAD = Val;
    
    if (TIMER_MODE_PERIODIC == Mode) {
        TIMERx->CTRL |= TIMER_CTRL_MODE_1;
    }

    return 0;
}

/*---------------------------------------------------------------------------------------------------*/

void Timer_Start(Timer_Reg_t *TIMERx)
{
    if (NULL == TIMERx) {
        return;
    }
    TIMERx->CTRL |= TIMER_CTRL_EN;
}

/*---------------------------------------------------------------------------------------------------*/

void Timer_Stop(Timer_Reg_t *TIMERx)
{
    if (NULL == TIMERx) {
        return;
    }
    TIMERx->CTRL &= ~(TIMER_CTRL_EN);
}

/*---------------------------------------------------------------------------------------------------*/

int Timer_GetVal(Timer_Reg_t *TIMERx)
{
    if (NULL == TIMERx) {
        return -1;
    }
    else {
        return TIMERx->CURVAL;
    }
    
}

/*---------------------------------------------------------------------------------------------------*/

__attribute__((weak)) void delayus(uint32_t time)
{
    TIMER1->CTRL = 0;
    TIMER1->LOAD = time * 100;
    TIMER1->CTRL |= TIMER_CTRL_MODE_1;
    TIMER1->CTRL |= TIMER_CTRL_EN;
    while (TIMER1->ISR != 0x1);
    TIMER1->CTRL &= ~(TIMER_CTRL_EN);
}

/*---------------------------------------------------------------------------------------------------*/

__attribute__((weak)) void delayms(uint32_t time)
{
    TIMER1->CTRL = 0;
    TIMER1->LOAD = time * 100000;
    TIMER1->CTRL |= TIMER_CTRL_MODE_1;
    TIMER1->CTRL |= TIMER_CTRL_EN;
    while (TIMER1->ISR != 0x1);
    TIMER1->CTRL &= ~(TIMER_CTRL_EN);
}

/*---------------------------------------------------------------------------------------------------*/