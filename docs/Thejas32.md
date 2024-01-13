# THEJAS32


## Memory Map





## Boot-up

On PoR, the boot-loader starts executing and the BOOTSEL jumper selects where to execute the code from

| Jumper Position | BOOTSEL | Boot Mode                     |
| --------------- | ------- | ----------------------------- |
| Open            | 0       | UART XMODEM                   |
| Closed          | 1       | Boot from external SPI flash  |

THEJAS32 does **not** have RAM+FLASH segregation to execute code. All code is executed from the 250 KB SRAM.

- When **BOOTSEL=0**, the bootloader waits for the user to upload the executable code (.bin format) over UART and copies the code to SRAM. 

```
+-----------------------------------------------------------------------------+
 |           VEGA Series of Microprocessors Developed By C-DAC, INDIA          |
 |     Microprocessor Development Programme, Funded by MeitY, Govt. of India   |
 +-----------------------------------------------------------------------------+
 | Bootloader, ver 1.0.0 [  (hdg@cdac_tvm) Tue Dec  15 16:50:32 IST 2020 #135] |
 |                                                                             |
 |  ___    _________________________          ISA  : RISC-V [RV32IM]           |
 |  __ |  / /__  ____/_  ____/__    |                                          |
 |  __ | / /__  __/  _  / __ __  /| |         CPU  : VEGA ET1031               |
 |  __ |/ / _  /___  / /_/ / _  ___ |                                          |
 |  _____/  /_____/  \____/  /_/  |_|         SoC  : THEJAS32                  |
 +---------------------------------------+-------------------------------------+
 |         www.vegaprocessors.in         |             vega@cdac.in            |
 +---------------------------------------+-------------------------------------+

 Transfer mode  : UART XMODEM
 
 IRAM           : [0x200000 - 0x23E7FF] [250 KB]
 
 Please send file using XMODEM and then press ENTER key.
 CCCCCCCCCCCCC

+-[Upload]--+
| zmodem    |
| ymodem    |
|>xmodem<   |
| kermit    |
| ascii     |
+-----------+

```

- When **BOOTSEL=1**, the bootloader copies the code from external SPI flash memory to the SRAM. Flashing to this external flash memory is achieved using `xmodemflasher` tool provided by CDAC.

---

## GPIO

ET1031 has two GPIO modules - GPIOA, GPIOB - each of them 16 bit wide.

GPIO is accessible with two registers :

- DIR (Direction Register)
- DATA (Data Register)

`GPIOA_DIR` - 0x100C0000

`GPIOB_DIR` - 0x101C0000

The DATA register for each GPIO appears at 16 locations in memory, according to the Pin number selected.

The PADDR register needs to be set/reset at appropriate location and bit for writing to GPIO.

`GPIOA_BASE` = 0x10080000

`GPIOB_BASE` = 0x10180000

Suppose you wish to write logical LOW to GPIOA Pin 5 :

We define address `PADDR` as `( (1 << pin) << 2 )`. `PADDR` acts as a mask for `GPIO_DATA`

`PADDR = (1 << 5) << 2`

Then the GPIO DATA registers occurs at address :

`GPIO_DATA = GPIOA_BASE + PADDR`

Now write to address appropriate bit as per pin:

`*GPIO_DATA = 0 << 5;`

Here's a figure explaining the operation on a similar 8-bit implementation (ET1031 is a 16-bit implementation) :

![Image.png](https://res.craft.do/user/full/3372ef50-799d-12ab-837f-d73801b8cbf5/doc/061B987D-3FA8-42F2-BFA2-2ECEB04F74BE/3209E924-C79F-48BE-B26B-9E9BD74227A7_2/hH8PsSCTw7rwsinyryjaLHft2fTTxshhD2ATXJSxLyIz/Image.png)

Data `0xFB` is written to **DATA** register. Only the bits masked with 1 in **PADDR** get changed in GPIO_DATA (bits 5 and 2).


Similar GPIO IP : [ARM PrimeCell GPIO](https://developer.arm.com/documentation/ddi0142/b/functional-overview/arm-primecell-general-purpose-input-output--pl060--overview?lang=en)

REMARK : There is no pin multiplexing, each of THEJAS32's 128 pins correspond to one single function.

---

# Interrupts

Interrupts can only be enabled/ disabled on a global basis and not individually. There is an event/interrupt controller outside of the core that performs masking and buffering of the interrupt lines. The global interrupt enable is done via the CSR register `MSTATUS`.

ET1031 **does support nested interrupt/exception handling**. Exceptions inside interrupt/exception handlers cause another exception, thus exceptions during the critical part of the exception handlers, i.e. before having saved the `MEPC` and `MSTATUS` register, will cause those register to be overwritten. Interrupts during interrupt/exception handlers are disabled by default, but can be explicitly enabled if desired.

---

