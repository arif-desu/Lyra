# Lyra API Documentation


## GPIO

GPIO is controlled with the following API calls:

#### GPIO_Init()

```c 
int GPIO_Init( uint16_t GPIOx, 
               uint16_t pin, 
               uint16_t dir)
```

- **Description** : Initializes a GPIO port pin to general purpose Output or Input.

- **Parameters** : 

    - `GPIOx` - GPIO controller to be initialized. Accepts 0, 1 or GPIOA, GPIOB
    - `pin` - Pin to be configured
    - `dir` - GPIO_OUT GPIO_IN

- **Return** : 

    - Returns `0` on successful configuration. 
    - Returns `-1` on invalid argument input 

---

#### GPIO_SetPin()

```c 
int GPIO_SetPin( uint16_t GPIOx, 
                 uint16_t Pin)
```

- **Description** : Writes a digital HIGH to GPIO Pin configured as Output.

- **Parameters** : 

    - `GPIOx` - GPIO controller. Accepts 0, 1 or GPIOA, GPIOB
    - `pin` - Pin to be written

- **Return** : 

    - Returns `0` on successful configuration. 
    - Returns `-1` on invalid argument input 

---

```c 
int GPIO_ResetPin( uint16_t GPIOx, 
                   uint16_t Pin)
```

- **Description** : Writes a digital LOW to GPIO Pin configured as Output.

- **Parameters** : 

    - `GPIOx` - GPIO controller. Accepts 0, 1 or GPIOA, GPIOB
    - `pin` - Pin to be written

- **Return** : 

    - Returns `0` on successful configuration. 
    - Returns `-1` on invalid argument input 
---

#### GPIO_TogglePin()
```c 
int GPIO_TogglePin( uint16_t GPIOx, 
                    uint16_t Pin)
```

- **Description** : Toggles the specified Pin (configured as Output) from last configured output state.

- **Parameters** : 

    - `GPIOx` - GPIO controller to be initialized. Accepts 0, 1 or GPIOA, GPIOB
    - `pin` - Pin to be toggled

- **Return** : 

    - Returns `0` on successful configuration. 
    - Returns `-1` on invalid argument input 

---

#### GPIO_ReadPin()
```c 
int GPIO_ReadPin( uint16_t GPIOx, 
                  uint16_t Pin)
```

- **Description** : Reads the data for pin configured as digital Input.

- **Parameters** : 

    - `GPIOx` - GPIO controller. Accepts 0, 1 or GPIOA, GPIOB
    - `pin` - Pin to be toggled

- **Return** : 

    - Returns `1` for a a logical HIGH.
     - Returns `0` for a logical LOW.
    - Returns `-1` on invalid argument input 

---

## Timer

#### Timer_Init()
```c
int Timer_Init( Timer_Reg_t *TIMERx, 
                uint16_t Mode, 
                uint32_t Val )
```

- **Description** : Initialises Timer module with interrupt masked.

- **Parameters** : 

    - `TIMERx` - Timer Module to be initialized. Accepts TIMER0, TIMER1, TIMER2
    - `Mode` - Timer mode. Free-running (`TIMER_MODE_FREERUN`) or Periodic (`TIMER_MODE_PERIODIC`)
    - `Val` - Value to be loaded into timer counter

- **Return** : 

    - Returns `0` for configuration
    - Returns `-1` if TIMERx is passed as NULL

---

#### Timer_Init_IT()
```c
int Timer_Init( Timer_Reg_t *TIMERx, 
                uint16_t Mode, 
                uint32_t Val )
```

The same as `Timer_Init()`, only initialises timer with interrupt un-masked.

---

#### Timer_Start()
```c
void Timer_Start(Timer_Reg_t *TIMERx)
```
- **Description** : Starts the timer counter for specified Timer.

- **Parameters** : 

    - `TIMERx` - Timer module to start.

- **Return** : void return type

---

#### Timer_Stop()
```c
void Timer_Stop(Timer_Reg_t *TIMERx)
```
- **Description** : Stops the timer counter for specified Timer.

- **Parameters** : 

    - `TIMERx` - Timer module to stop.

- **Return** : void return type

---

#### Timer_GetCount()

```c
int Timer_GetCount(Timer_Reg_t *TIMERx)
```

- **Description** : Reads the timer counter value for specified Timer.

- **Parameters** : 

    - `TIMERx` - Timer module to stop.

- **Return** : 
    - Returns counter value
    - Returns `-1` for invalid argument input

---

#### Timer_ClearInterrupt()
```c
int Timer_ClearInterrupt(Timer_Reg_t *TIMERx)
```
- **Description** : Reads the interrupt status bit for specified Timer to mark End-Of-Interrupt. This should be called everytime the interrupt occurs - either through polling the `TIMERx->ISR` or in ISR Routine.

- **Parameters** : 

    - `TIMERx` - Timer module.

- **Return** : 
    - Returns counter value
    - Returns `-1` for invalid argument input

---

## Interrupts

#### __enable_irq()
```c
void __enable_irq(void)
```
- **Description** : Enables interrupts globally.

- **Parameters** : None

- **Return** : void

---

#### __disable_irq()
```c
void __disable_irq(void)
```
- **Description** : Disables interrupts globally.

- **Parameters** : None

- **Return** : void

---

#### PLIC_Enable()
```c
int PLIC_Enable(uint16_t IRQn)
```
- **Description** : Registers an interrupt in the PLIC (Platform-level Interrupt Controller) specified by the interrupt number

- **Parameters** : 
    - `IRQn` : Interrupt Request Number. See memory map or interrupt.h. These are also defined by macros in interrupt.h

- **Return** : 

    - Returns `0` on success
    - Returns `-1` for invalid argument.

---

#### PLIC_Enable()
```c
int PLIC_Enable(uint16_t IRQn)
```
- **Description** : De-registers an interrupt in the PLIC (Platform-level Interrupt Controller) specified by the interrupt number.

- **Parameters** : 
    - `IRQn` : Interrupt Request Number. See memory map or interrupt.h. These are also defined by macros in interrupt.h

- **Return** : 

    - Returns `0` on success
    - Returns `-1` for invalid argument.

---
