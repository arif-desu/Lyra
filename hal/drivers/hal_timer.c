/** @file hal_timer.c
 *  @brief Timer routines for THEJAS32
 *  @author Arif B <arif.dev@pm.me>
 */

#include <vega/thejas32.h>
#include <vega/timer.h>
#include <vega/interrupt.h>
#include <stdint.h>
#include <stdlib.h>

Timer_Handle_t htimer0 = {
    .Instance = TIMER0,
    .LoadCount = 0,
    .Mode = TIMER_MODE_PERIODIC,
    .State = PERIPH_STATE_RDY
};

Timer_Handle_t htimer1 = {
    .Instance = TIMER1,
    .LoadCount = 0,
    .Mode = TIMER_MODE_PERIODIC,
    .State = PERIPH_STATE_RDY
};

Timer_Handle_t htimer2 = {
    .Instance = TIMER2,
    .LoadCount = 0,
    .Mode = TIMER_MODE_PERIODIC,
    .State = PERIPH_STATE_RDY
};

/*---------------------------------------------------------------------------------------------------*/

int Timer_Init(Timer_Handle_t *htimer, uint32_t val)
{
    if (htimer == NULL) {
        return -1;
    }

    if (htimer->State == PERIPH_STATE_BUSY) {
        return PERIPH_STATE_BUSY;
    }
    
    htimer->Instance->CTRL = 0;

    htimer->Instance->LOAD = val;
    
    switch (htimer->Mode) {
        case TIMER_MODE_FREERUN:
            htimer->Instance->CTRL &= ~(0x1UL << TIMER_CTRL_MODE_Pos);
            break;
        case TIMER_MODE_PERIODIC:
            htimer->Instance->CTRL |= (0x1UL << TIMER_CTRL_MODE_Pos);
            break;
        default:
            return -1;
    }

    return 0;
}

/*---------------------------------------------------------------------------------------------------*/

void Timer_Start(Timer_Handle_t *htimer)
{
    if (htimer == NULL) {
        return;
    }

    if (htimer->State == PERIPH_STATE_BUSY) {
        return;
    }

    htimer->Instance->CTRL |= TIMER_CTRL_EN;
    htimer->State = PERIPH_STATE_BUSY;
}

/*---------------------------------------------------------------------------------------------------*/


void Timer_Start_IT(Timer_Handle_t *htimer)
{
    if (htimer == NULL) {
        return;
    }

    if (htimer->State == PERIPH_STATE_BUSY) {
        return;
    }

    int irqn;
    if (htimer->Instance == TIMER0) {
       irqn = TIMER0_IRQn; 
    }
    else if (htimer->Instance == TIMER1) {
        irqn = TIMER1_IRQn;
    }
    else if (htimer->Instance == TIMER2) {
        irqn = TIMER2_IRQn;
    }
    else {
        return;
    }

    PLIC->EN |= 0x1UL << irqn;

    htimer->Instance->CTRL |= TIMER_CTRL_EN;
    htimer->State = PERIPH_STATE_BUSY;
}

/*---------------------------------------------------------------------------------------------------*/

void Timer_Stop(Timer_Handle_t *htimer)
{
    if (htimer->Instance == NULL) {
        return;
    }
    else {
        htimer->Instance->CTRL &= ~(TIMER_CTRL_EN);
        htimer->State = PERIPH_STATE_RDY;
    } 
}

/*---------------------------------------------------------------------------------------------------*/

int Timer_GetCount(Timer_Handle_t *htimer)
{
    if (htimer->Instance == NULL) {
        return -1;
    }
    else {
        return htimer->Instance->CURVAL;
    }
}

/*---------------------------------------------------------------------------------------------------*/

int Timer_ClearInt(Timer_Handle_t *htimer)
{
    if (htimer->Instance == NULL) {
        return -1;
    }
    else {
        // Perform read on Interrupt Clear register to clear interrupt bit
        return htimer->Instance->INTCLR;
    }
}

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