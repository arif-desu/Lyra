# THEJAS32 Memory Map

| Peripheral/Register                   | Start       | End         | Interrupt Number  |
| ------------------------------------- | ----------- | ----------- | ----------------- | 
| RAM                                   | 0x00200000  | 0x00237FFF | -                 |
| UART0                                 | 0x1000_0100 | 0x1000_01FF | 0                 |
| UART1                                 | 0x1000_0200 | 0x1000_02FF | 1                 |
| UART2                                 | 0x1000_0300 | 0x1000_03FF | 2                 |
| SPI0                                  | 0x1000_0600 | 0x1000_06FF | 3                 |
| SPI1                                  | 0x1000_0700 | 0x1000_07FF | 4                 |
| I2C0                                  | 0x1000_0800 | 0x1000_08FF | 5                 |
| I2C1                                  | 0x1000_0900 | 0x1000_09FF | 6                 |
| TIMER0                                | 0x1000_0A00 | 0x1000_0A10 | 7                 |
| TIMER1                                | 0x1000_0A14 | 0x1000_0A24 | 8                 |
| TIMER2                                | 0x1000_0A28 | 0x1000_0A38 | 9                 |
| TIMERS MASKED INTERRUPT STATUS        | 0x1000_0AA0 |             |                   |
| TIMERS INTERRUPT CLEAR                | 0x1000_0AA4 |             |                   |
| TIMERS RAW INTERRUPT STATUS           | 0x1000_0AA8 |             |                   |
| I2C2                                  | 0x1000_1000 | 0x1000_1FFF | 22                |
| GPIOA                                 | 0x1008_0000 |             | 10 - 21           |
| GPIOB                                 | 0x1018_0000 |             |                   |
| SPI2                                  | 0x1020_0100 | 0x1020_01FF | 23                |
| SPI3                                  | 0x1020_0200 | 0x1020_02FF |                   |
| PWM                                   | 0x1040_0000 | 0x1040_00FF | 24 - 31           |
| PLIC                                  | 0x2001_0000 | 0x2001_FFFF |                   |