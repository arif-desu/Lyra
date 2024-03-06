/** 
 @file timer.h
 @brief THEJAS32 Timer APIs
 @author Arif B (arif.dev@pm.me)
*/
#ifndef TIMER_H
#define TIMER_H

#include <vega/thejas32.h>
#include <stdint.h>

#define TIMER_MODE_FREERUN      (0)
#define TIMER_MODE_PERIODIC     (1)


typedef struct {
    Timer_Reg_t *Instance;
    uint32_t LoadCount;
    uint8_t Mode;
    uint8_t State;
} Timer_Handle_t;


extern Timer_Handle_t htimer0;
extern Timer_Handle_t htimer1;
extern Timer_Handle_t htimer2;


/*---------------------------------------------------------------------------------------------------*/

/* Configures the Timer in Blocking mode */
int Timer_Init(Timer_Handle_t *htimer, uint32_t val);

/*---------------------------------------------------------------------------------------------------*/

void Timer_SetMode(Timer_Handle_t *htimer, uint8_t mode);

/*---------------------------------------------------------------------------------------------------*/

/* Starts the Timer counter */
void Timer_Start(Timer_Handle_t *htimer);

/*---------------------------------------------------------------------------------------------------*/

/* Starts the Timer counter */
void Timer_Start_IT(Timer_Handle_t *htimer);

/*---------------------------------------------------------------------------------------------------*/

/* Stops the Timer counter */
void Timer_Stop(Timer_Handle_t *htimer);

/*---------------------------------------------------------------------------------------------------*/

/* Clears the timer interrupt */
int Timer_ClearInt(Timer_Handle_t *htimer);

/*---------------------------------------------------------------------------------------------------*/

/* Reads the current value of counter in Timer */
int Timer_GetCount(Timer_Handle_t *htimer);

/*---------------------------------------------------------------------------------------------------*/

/* Generate a blocking delay in micro-seconds */
void delayus(uint32_t time);

/*---------------------------------------------------------------------------------------------------*/

/* Generate a blocking delay in milliseconds */
void delayms(uint32_t time);

/*---------------------------------------------------------------------------------------------------*/
#endif