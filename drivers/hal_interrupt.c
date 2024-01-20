/** @file hal_interrupt.c
 *  @brief Interrupt handler routines for THEJAS32
 *  @author Arif B <arif.dev@pm.me>
 */

#include <stdint.h>
#include <vega/csr.h>
#include <vega/interrupt.h>
#include <vega/thejas32.h>

extern unsigned long InterruptHandler;    

/* Platform-Level Interrupt Controller - Interrupt Service Routine table */

void (* PLIC_ISR[32])(void) = {
    UART0_IRQHandler,
    UART1_IRQHandler,
    UART2_IRQHandler,
    SPI0_IRQHandler,
    SPI1_IRQHandler,
    I2C0_IRQHandler,
    I2C1_IRQHandler,
    TIMER0_IRQHandler,
    TIMER1_IRQHandler,
    TIMER2_IRQHandler,
    GPIO0_IRQHandler,
    GPIO1_IRQHandler,
    GPIO2_IRQHandler,
    GPIO3_IRQHandler,
    GPIO4_IRQHandler,
    GPIO5_IRQHandler,
    GPIO6_IRQHandler,
    GPIO7_IRQHandler,
    GPIO8_IRQHandler,
    GPIO9_IRQHandler,
    GPIO10_IRQHandler,
    GPIO11_IRQHandler,
    I2C2_IRQHandler,
    SPI2_IRQHandler,
    PWMChannel1_IRQHandler,
    PWMChannel2_IRQHandler,
    PWMChannel3_IRQHandler,
    PWMChannel4_IRQHandler,
    PWMChannel5_IRQHandler,
    PWMChannel6_IRQHandler,
    PWMChannel7_IRQHandler,
    PWMChannel8_IRQHandler,
};

/*---------------------------------------------------------------------------------------------------*/

void __enable_irq(void)
{
    set_csr(mie, MIE_EIE);
    
    set_csr(mstatus, MSTATUS_MIE);

    write_csr(mtvec, (unsigned long)&InterruptHandler);

}

/*---------------------------------------------------------------------------------------------------*/

void __disable_irq(void)
{
    clear_csr(mie, MIE_EIE);
    clear_csr(mstatus, MSTATUS_MIE);
}

/*---------------------------------------------------------------------------------------------------*/

int PLIC_Enable(uint16_t IRQn)
{
    if (IRQn > 31) {
        return -1;
    }
    else {
        PLIC->INTEN |= 0x1UL << IRQn;
    }
    return 0;
}

/*---------------------------------------------------------------------------------------------------*/

int PLIC_Disable(uint16_t IRQn)
{
    if (IRQn > 31) {
        return -1;
    }
    else {
        PLIC->INTEN &= ~(0x1UL << IRQn);
    }
    return 0;
}

/*---------------------------------------------------------------------------------------------------*/

void ISR_Delegator(void)
{
    int cause = 0, type = 0;

    type = (read_csr(mcause) >> 31);

    if (type) {

        cause = ((read_csr(mcause) << 1) >> 1);

        if (MCAUSE_EXTI == cause) {
            uint32_t intstat = PLIC->INTSTATUS;

            for (uint32_t i = 0; i < 32; i++) {
                if ((intstat >> i) & 0x1UL) {
                    // Call ISR for each triggered interrupt, according to priority
                    PLIC_ISR[i]();
                }
            }
        }
    }
}

/*---------------------------------------------------------------------------------------------------*/

__attribute__((weak)) void UART0_IRQHandler(void)           { while (1); }
__attribute__((weak)) void UART1_IRQHandler(void)           { while (1); }
__attribute__((weak)) void UART2_IRQHandler(void)           { while (1); }
__attribute__((weak)) void SPI0_IRQHandler(void)            { while (1); }
__attribute__((weak)) void SPI1_IRQHandler(void)            { while (1); }
__attribute__((weak)) void I2C0_IRQHandler(void)            { while (1); }
__attribute__((weak)) void I2C1_IRQHandler(void)            { while (1); }
__attribute__((weak)) void TIMER0_IRQHandler(void)          { while (1); }
__attribute__((weak)) void TIMER1_IRQHandler(void)          { while (1); }
__attribute__((weak)) void TIMER2_IRQHandler(void)          { while (1); }
__attribute__((weak)) void GPIO0_IRQHandler(void)           { while (1); }
__attribute__((weak)) void GPIO1_IRQHandler(void)           { while (1); }
__attribute__((weak)) void GPIO2_IRQHandler(void)           { while (1); }
__attribute__((weak)) void GPIO3_IRQHandler(void)           { while (1); }
__attribute__((weak)) void GPIO4_IRQHandler(void)           { while (1); }
__attribute__((weak)) void GPIO5_IRQHandler(void)           { while (1); }
__attribute__((weak)) void GPIO6_IRQHandler(void)           { while (1); }
__attribute__((weak)) void GPIO7_IRQHandler(void)           { while (1); }
__attribute__((weak)) void GPIO8_IRQHandler(void)           { while (1); }
__attribute__((weak)) void GPIO9_IRQHandler(void)           { while (1); }
__attribute__((weak)) void GPIO10_IRQHandler(void)          { while (1); }
__attribute__((weak)) void GPIO11_IRQHandler(void)          { while (1); }
__attribute__((weak)) void GPIO12_IRQHandler(void)          { while (1); }
__attribute__((weak)) void I2C2_IRQHandler(void)            { while (1); }
__attribute__((weak)) void SPI2_IRQHandler(void)            { while (1); }
__attribute__((weak)) void PWMChannel1_IRQHandler(void)     { while (1); }
__attribute__((weak)) void PWMChannel2_IRQHandler(void)     { while (1); }
__attribute__((weak)) void PWMChannel3_IRQHandler(void)     { while (1); }
__attribute__((weak)) void PWMChannel4_IRQHandler(void)     { while (1); }
__attribute__((weak)) void PWMChannel5_IRQHandler(void)     { while (1); }
__attribute__((weak)) void PWMChannel6_IRQHandler(void)     { while (1); }
__attribute__((weak)) void PWMChannel7_IRQHandler(void)     { while (1); }
__attribute__((weak)) void PWMChannel8_IRQHandler(void)     { while (1); }

/*---------------------------------------------------------------------------------------------------*/