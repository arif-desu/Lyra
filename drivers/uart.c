/**
 @file uart.c
 @brief Contains routines for UART interface
 @author Arif B <arif.dev@pm.me>
 */

#include <vega/thejas32.h>
#include <vega/uart.h>

#include <stdio.h>
#include <string.h>


/* 
Initialises UART controller in blocking mode 
@param UARTx - UART instance
@param Baud  - Baud Rate in bits per second
@param Frame - Frame format <WordLength><Parity><StopBits>

Default - If Frame is passed as NULL, defaults to 8N1
@return : void
*/

void UART_Init(UART_Reg_t *UARTx, uint32_t baud, const UART_Frame_t *frame) 
{
	if (NULL == UARTx) {
		return;
	}

	UARTx->LCR = 0x00000000UL;

	if (NULL == frame) {
		UARTx->LCR = (UART_LCR_WL8 | UART_LCR_PE_NONE | UART_LCR_STOP_1);
	}
	else {
		switch (frame->WordLength) {
			case 8:
				UARTx->LCR |= UART_LCR_WL8;
				break;
			case 7:
				UARTx->LCR |= UART_LCR_WL7;
				break;
			case 6:
				UARTx->LCR |= UART_LCR_WL6;
				break;
			case 5:
				UARTx->LCR |= UART_LCR_WL5;
				break;
			default:
				break;
		}
			
		switch (frame->Parity) {
			case 'n':
			case 'N':
				UARTx->LCR |= UART_LCR_PE_NONE;
				break;
			case 'e':
			case 'E':
				UARTx->LCR |= UART_LCR_PE_EVEN;
				break;
			case 'o':
			case 'O':
				UARTx->LCR |= UART_LCR_PE_ODD;
				break;
			default:
				//TODO
				break;
		}

		switch (frame->StopBits) {
			case 1:
				UARTx->LCR |= UART_LCR_STOP_1;
				break;
			case 2:
				UARTx->LCR |= UART_LCR_STOP_2;
				break;
			default:
				break;
		}
	}

	/* Enable Latch Access and load MSB and LSB into divisor latch register to set baud rate*/
	uint32_t divisor = (uint32_t) (UARTCLK / (baud * 16));

	UARTx->LCR |= UART_LCR_DLAB;
	UARTx->DLL = divisor & 0xFFFFUL;
	UARTx->DLM = (divisor >> 8) & 0xFFFFUL;

	/* Disable Divisor Latch access */
	UARTx->LCR &= ~(UART_LCR_DLAB);

	/* Disable all UART interrupts */
	UARTx->IER = 0x00UL;
}

void UART_TxChar(UART_Reg_t *UARTx, const char data)
{
	if (NULL == UARTx) {
		return;
	}

	/* Wait till Transmit FIFOs are empty from any previous transactions */
	while (! (UARTx->LSR & (UART_LSR_TXE_Msk | UART_LSR_TEMPT_Msk)));

	UARTx->TXBUF = data;

	while (! (UARTx->LSR & UART_LSR_TXE_Msk));
}


void UART_Transmit(UART_Reg_t *UARTx, const char *buffer, uint32_t len)
{
	if (NULL == UARTx || NULL == buffer || 0 == len) {
		return;
	}

	while (*buffer && len) {
		UART_TxChar(UARTx, *buffer++);
	}
}




