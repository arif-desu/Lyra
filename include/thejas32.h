/** 
 @file thejas32.h
 @brief THEJAS32 hardware registers
 @author Arif B (arif.dev@pm.me)
*/


#ifndef _THEJAS32_H_
#define _THEJAS32_H_

#ifdef __cplusplus
    extern "C" {
#endif /* __cpluscplus */

#include <stdint.h>

#define __IO    volatile

#define SYSTEMCLK		(100000000UL)		/* 100 MHz core clock */
#define UARTCLK			(40000000UL)		/* 40 MHz UART Bus Clock ? */
/*
* @brief Memory Map
*/

#define UART_BASE						(0x10000100UL)
#define SPI_BASE                        (0x10000600UL)
#define I2C_BASE                        (0x10000800UL)
#define TIMER_BASE                      (0x10000A00UL)
#define ADC_BASE                        (0x10001000UL)                   
#define PWM_BASE                        (0x10400000UL)
#define PLIC_BASE                       (0x20010000UL)

#define PLIC_SWINTR_EN					(0x20010400UL)



/*
* @brief GPIO Registers
*/

#define GPIOA_DATA                  (0x10080000UL)   
#define GPIOB_DATA                  (0x10180000UL)  

#define GPIOA_DIR					((__IO uint32_t *)(0x100C0000UL))
#define GPIOB_DIR					((__IO uint32_t *)(0x101C0000UL))




/*------------------------------------------------------------------------------*/

/* TIMER 
32-bit down counter supporting free-running and periodic modes
*/

typedef struct {
	__IO uint32_t LOAD;						/* Load Count Register */
	const __IO uint32_t CURVAL;				/* Current Value Register */
	__IO uint32_t CTRL;						/* Control Register */
	__IO uint32_t INTCLR;					/* Interrupt Clear Register */
	const __IO uint32_t ISR;				/* Interrupt Status Register */
} Timer_Reg_t;


#define TIMER1						((Timer_Reg_t *)(TIMER_BASE + 0x00UL))
#define TIMER2						((Timer_Reg_t *)(TIMER_BASE + 0x14UL))
#define TIMER3						((Timer_Reg_t *)(TIMER_BASE + 0x28UL))

/* Timer Control Register bits */
#define TIMER_CTRL_EN_Pos			(0UL)
#define TIMER_CTRL_EN				(0x1U << TIMER_CTRL_EN_Pos)					/* Timer Enable */
#define TIMER_CTRL_MODE_Pos			(1UL)
#define TIMER_CTRL_MODE_0			(0x0U << TIMER_CTRL_MODE_Pos)				/* Free-running Counter */
#define TIMER_CTRL_MODE_1			(0x1U << TIMER_CTRL_MODE_Pos)				/* Periodic Mode */
#define TIMER_CTRL_INT_Pos			(2UL)
#define TIMER_CTRL_INT  			(1U << TIMER_CTRL_INT_Pos)					/* Timer Interrupt Enable */

/*------------------------------------------------------------------------------*/

/*
* UART Controller
Based on UART16550/16450
*/

typedef struct {
	union {
		const __IO uint32_t RXBUF;				/* UART Receiever Buffer Register */
		__IO uint32_t TXBUF;					/* UART Transmitter Holding Register */
		__IO uint32_t DLL;						/* UART Divisor Latch LSB */
	};
	union {
		__IO uint32_t IER;						/* UART Interrupt Enable Register */
		__IO uint32_t DLM;						/* UART Divisor Latch MSB */
	};
	union {
		const __IO uint32_t IIR;				/* UART Interrupt Identification Register */
		__IO uint32_t FCR;						/* UART FIFO Control Register */
	};
	__IO uint32_t LCR;                          /* UART Line Control Register */
	__IO uint32_t MCR;							/* UART Modem Control Register */
	__IO uint32_t LSR;							/* UART Line Status Register */	
	__IO uint32_t MSR;							/* UART Modem Status Register */
	__IO uint32_t SCRATCH;						/* UART Scratch Register */
} UART_Reg_t;



#define UART0 							((UART_Reg_t *)(UART_BASE + 0x0000UL))    /* 0x1000 0100 */
#define UART1 							((UART_Reg_t *)(UART_BASE + 0x0100UL))    /* 0x1000 0200 */
#define UART2 							((UART_Reg_t *)(UART_BASE + 0x0200UL))    /* 0x1000 0300 */

/* UART Interrupt Enable Register (IER) bits */

#define UART_IER_RXBUFINT_Pos			(0U)			/* Received Data Available Interrupt */
#define UART_IER_RXBUFINT				(0x1U << UART_IER_RXBUFINT_Pos)			
#define UART_IER_TXBUFINT_Pos			(1U)			/* Transmitter Holding Register Empty Interrupt */
#define UART_IER_TXBUFINT				(0x1U << 1)			/* Transmitter Holding Register Empty Interrupt */
#define UART_IER_RXLSR					(2U)	/* Receiver Line Status Register */
#define UART_IER_MSI 					(3U)	/* Modem Status Interrupt */

/* UART Interrupt Identification Register (IIR) bits */

#define UART_IIR_INTPEND				(0U)	/* Interrupt Pending */
#define UART_IIR_INTID					(1U)	/* Interrupt ID [2:0] */
#define UART_IIR_FIFOEN					(6U)	/* IIR FIFOs Enable [7:6] */

/* UART FIFO Control Register (FCR) bits */

#define UART_FCR_FIFOEN					(0U)	/* FIFO Enable */
#define UART_FCR_RXFIFORST              (1U)    /* Receiver FIFO Reset */
#define UART_FCR_TXFIFORST              (2U)    /* Transmitter FIFO Reset */
#define UART_FCR_DMAMODE                (3U)    /* DMA Mode Select ??? THEJAS32 has no DMA controller*/
#define UART_FCR_RXFIFOTRIG             (6U)    /* Receiver FIFO Trigger Level [7:6] */

/* UART Line Control Register */

/* | DLAB | SB | SP | PS | PE | STOP | WL [1:0] |  */

#define UART_LCR_WL                     (0U)    /* Word Length [1:0] */
#define UART_LCR_STOP                   (2U)    /* Stop Bits */
#define UART_LCR_PE                		(3U)    /* Parity Enable */
#define UART_LCR_PS                     (4U)    /* Parity Selection */
#define UART_LCR_SP                     (5U)    /* Stick Parity */
#define UART_LCR_SB                     (6U)    /* Set Break */
#define UART_LCR_DLAB_Pos               (7U)    /* Divisor Latch Access Bit */
#define UART_LCR_DLAB 					(0x1U << UART_LCR_DLAB_Pos)

#define UART_LCR_WL8					(0x3U << UART_LCR_WL)
#define UART_LCR_WL7					(0x2U << UART_LCR_WL)
#define UART_LCR_WL6					(0x1U << UART_LCR_WL)
#define UART_LCR_WL5					(0x0U << UART_LCR_WL)

#define UART_LCR_PE_NONE				(0x0U << UART_LCR_PE)
#define UART_LCR_PE_EVEN				(0x1U << UART_LCR_PE | 0x0U << UART_LCR_PS)
#define UART_LCR_PE_ODD					(0x1U << UART_LCR_PE | 0x0U << UART_LCR_PS)

#define UART_LCR_STOP_1					(0x0U << UART_LCR_STOP)
#define UART_LCR_STOP_2					(0x1U << UART_LCR_STOP)


/* UART Line Status Register */

#define UART_LSR_DATARDY_Pos				(0U)	/* Data Ready bit */
#define UART_LSR_DATARDY				(1U << 0U)
#define UART_LSR_OE						(1U)	/* Overrun Error bit */
#define UART_LSR_PERR					(2U)	/* Parity Error bit */
#define UART_LSR_FERR					(3U)	/* Framing Error bit */
#define UART_LSR_BRKINT					(4U)	/* Break Interrupt bit */
#define UART_LSR_TXE					(5U)	/* Transmitter (FIFO) Buffer Empty */
#define UART_LSR_TXE_Msk				(1UL << UART_LSR_TXE)
#define UART_LSR_TEMPT					(6U)	/* Transmitter Empty */
#define UART_LSR_TEMPT_Msk				(1UL << UART_LSR_TEMPT)
#define UART_LSR_RXERR					(7U)	/* Receiver FIFO Error */




/* SPI */





#ifdef __cplusplus
    }
#endif /* __cplusplus */
#endif /* _THEJAS32_H_ */