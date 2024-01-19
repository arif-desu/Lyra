# Lyra API Documentation


## GPIO

GPIO is controlled with the following API calls:

#### GPIO_Init()

```c 
int GPIO_Init( uint16_t GPIOx, 
               uint16_t Pin, 
               uint16_t Direction)
```

- **Description** : Initializes a GPIO port pin to be general purpose Output or Input.

- **Parameters** : 

    - `GPIOx` - GPIO controller to be initialized. Accepts 0, 1 or GPIOA, GPIOB
    - `Pin` - Pin to be configured
    - `Direction` - OUT / IN

- **Return** : 

    - Returns `0` on successfull configuration. 
    - Returns `-1` on invalid input 

---

#### GPIO_SetPin()

```c 
int GPIO_SetPin( uint16_t GPIOx, 
                 uint16_t Pin)
```

- **Description** : Writes a digital HIGH to GPIO Pin configured as Output.

- **Parameters** : 

    - `GPIOx` - GPIO controller. Accepts 0, 1 or GPIOA, GPIOB
    - `Pin` - Pin to be written

- **Return** : 

    - Returns `0` on successfull configuration. 
    - Returns `-1` on invalid input 

---

```c 
int GPIO_ResetPin( uint16_t GPIOx, 
                   uint16_t Pin)
```

- **Description** : Writes a digital LOW to GPIO Pin configured as Output.

- **Parameters** : 

    - `GPIOx` - GPIO controller. Accepts 0, 1 or GPIOA, GPIOB
    - `Pin` - Pin to be written

- **Return** : 

    - Returns `0` on successfull configuration. 
    - Returns `-1` on invalid input 

---

#### GPIO_TogglePin()
```c 
int GPIO_TogglePin( uint16_t GPIOx, 
                    uint16_t Pin)
```

- **Description** : Toggles the specified Pin (configured as Output) from last configured output state.

- **Parameters** : 

    - `GPIOx` - GPIO controller to be initialized. Accepts 0, 1 or GPIOA, GPIOB
    - `Pin` - Pin to be toggled

- **Return** : 

    - Returns `0` on successfull configuration. 
    - Returns `-1` on invalid input 

---

#### GPIO_ReadPin()
```c 
int GPIO_ReadPin( uint16_t GPIOx, 
                  uint16_t Pin)
```

- **Description** : Reads the data for pin configured as digital Input.

- **Parameters** : 

    - `GPIOx` - GPIO controller. Accepts 0, 1 or GPIOA, GPIOB
    - `Pin` - Pin to be toggled

- **Return** : 

    - Returns `1` for a a logical HIGH.
     - Returns `0` for a logical LOW.
    - Returns `-1` on invalid input 