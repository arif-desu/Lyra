/** 
 @file timer.h
 @brief THEJAS32 Timer APIs
 @author Arif B (arif.dev@pm.me)
*/
#ifndef TIMER_H
#define TIMER_H

#include <vega/thejas32.h>

#define TIMER_MODE_FREERUN     (0U)
#define TIMER_MODE_PERIODIC   (1U)

/*---------------------------------------------------------------------------------------------------*/

/* Configures the Timer in Blocking Mode */
int Timer_Init(Timer_Reg_t *TIMERx, uint16_t Mode, uint32_t Val);

/*---------------------------------------------------------------------------------------------------*/

/* Starts the Timer counter */
void Timer_Start(Timer_Reg_t *TIMERx);

/*---------------------------------------------------------------------------------------------------*/

/* Stops the Timer counter */
void Timer_Stop(Timer_Reg_t *TIMERx);

/*---------------------------------------------------------------------------------------------------*/

/* Reads the current value of counter in Timer */
int Timer_GetVal(Timer_Reg_t *TIMERx);

/*---------------------------------------------------------------------------------------------------*/

/* Generate a blocking delay in micro-seconds */
void delayus(uint32_t time);

/*---------------------------------------------------------------------------------------------------*/

/* Generate a blocking in milliseconds */
void delayms(uint32_t time);

/*---------------------------------------------------------------------------------------------------*/
#endif