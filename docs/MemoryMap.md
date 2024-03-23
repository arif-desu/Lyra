# THEJAS32 Memory Map

| Peripheral Register         | Start      | End        | Interrupt Number |
|-----------------------------|------------|------------|------------------|
| RAM                         | 0x00200000 | 0x00237FFF | -                |
| UART0                       | 0x10000100 | 0x100001FF | 0                |
| UART1                       | 0x10000200 | 0x100002FF | 1                |
| UART2                       | 0x10000300 | 0x100003FF | 2                |
| SPI0                        | 0x10000600 | 0x100006FF | 3                |
| SPI1                        | 0x10000700 | 0x100007FF | 4                |
| I2C0                        | 0x10000800 | 0x100008FF | 5                |
| I2C1                        | 0x10000900 | 0x100009FF | 6                |
| TIMER0                      | 0x10000A00 | 0x10000A10 | 7                |
| TIMER1                      | 0x10000A14 | 0x10000A24 | 8                |
| TIMER2                      | 0x10000A28 | 0x10000A38 | 9                |
| TIMERS INTERRUPT STATUS     | 0x10000AA0 |            |                  |
| TIMERS INTERRUPT CLEAR      | 0x10000AA4 |            |                  |
| TIMERS RAW INTERRUPT STATUS | 0x10000AA8 |            |                  |
| I2C2                        | 0x10001000 | 0x10001FFF | 22               |
| GPIOA                       | 0x10080000 |            | 10 - 21          |
| GPIOB                       | 0x10180000 |            |                  |
| SPI2                        | 0x10200100 | 0x102001FF | 23               |
| SPI3                        | 0x10200200 | 0x102002FF |                  |
| PWM                         | 0x10400000 | 0x104000FF | 24 - 31          |
| PLIC                        | 0x20010000 | 0x2001FFFF |                  |