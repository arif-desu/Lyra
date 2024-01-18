/** @file hal_timer.c
 *  @brief Timer routines for THEJAS32
 *  @author Arif B <arif.dev@pm.me>
 */

#include <vega/thejas32.h>
#include <vega/timer.h>
#include <stdint.h>
#include <stdlib.h>

/*---------------------------------------------------------------------------------------------------*/

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
    TIMERx->CTRL |= TIMER_CTRL_INT_Msk;

    return 0;
}

/*---------------------------------------------------------------------------------------------------*/

int Timer_Init_IT(Timer_Reg_t *TIMERx, uint16_t Mode, uint32_t Val)
{
    if (NULL == TIMERx) {
        return -1;
    }
    TIMERx->CTRL = 0;

    TIMERx->LOAD = Val;
    
    if (TIMER_MODE_PERIODIC == Mode) {
        TIMERx->CTRL |= TIMER_CTRL_MODE_1;
    }
    TIMERx->CTRL &= ~(TIMER_CTRL_INT_Msk);
    
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

int Timer_GetCount(Timer_Reg_t *TIMERx)
{
    if (NULL == TIMERx) {
        return -1;
    }
    else {
        return TIMERx->CURVAL;
    }
    
}

/*---------------------------------------------------------------------------------------------------*/

int Timer_ClearInterrupt(Timer_Reg_t *TIMERx)
{
    if (NULL == TIMERx) {
        return -1;
    }
    else {
        return TIMERx->INTCLR;
    }
    
}

/*---------------------------------------------------------------------------------------------------*/

__attribute__((weak)) void delayus(uint32_t time)
{
    TIMER0->CTRL = 0;
    TIMER0->LOAD = time * 50;
    TIMER0->CTRL |= TIMER_CTRL_MODE_1 | TIMER_CTRL_INT_Msk | TIMER_CTRL_EN;
    while (GLOBAL_TIMER_RAWINT_STATUS != TIMER0_RAWINT_STATUS);
}

/*---------------------------------------------------------------------------------------------------*/

__attribute__((weak)) void delayms(uint32_t time)
{
    TIMER0->CTRL = 0;
    TIMER0->LOAD = time * 50000;
    TIMER0->CTRL |= TIMER_CTRL_MODE_1 | TIMER_CTRL_INT_Msk | TIMER_CTRL_EN;
    while (GLOBAL_TIMER_RAWINT_STATUS != TIMER0_RAWINT_STATUS);
}

/*---------------------------------------------------------------------------------------------------*/