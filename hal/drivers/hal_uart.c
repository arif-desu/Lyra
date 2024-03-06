/**
 @file hal_uart.c
 @brief Contains routines for UART interface
 @author Arif B <arif.dev@pm.me>
 */

#include <vega/interrupt.h>
#include <vega/thejas32.h>
#include <vega/uart.h>

#include <stdlib.h>


/*---------------------------------------------------------------------------------------------------*/

UART_Handle_t huart0 = {
	.Instance = UART0,
	.BaudRate = 115200,
	.WordLength = 8,
	.Parity = 'N',
	.StopBits = 1,
	.gState = PERIPH_STATE_RDY,
	.RxBuffer = NULL,
	.TxBuffer = NULL,
	.RxXferCount = 0,
	.TxXferCount = 0,
	.TxState = PERIPH_STATE_RDY,
	.RxState = PERIPH_STATE_RDY
};

UART_Handle_t huart1 = {
	.Instance = UART1,
	.BaudRate = 115200,
	.WordLength = 8,
	.Parity = 'N',
	.StopBits = 1,
	.gState = PERIPH_STATE_RDY,
	.RxBuffer = NULL,
	.TxBuffer = NULL,
	.RxXferCount = 0,
	.TxXferCount = 0,
	.TxState = PERIPH_STATE_RDY,
	.RxState = PERIPH_STATE_RDY
};

UART_Handle_t huart2 = {
	.Instance = UART2,
	.BaudRate = 115200,
	.WordLength = 8,
	.Parity = 'N',
	.StopBits = 1,
	.gState = PERIPH_STATE_RDY,
	.RxBuffer = NULL,
	.TxBuffer = NULL,
	.RxXferCount = 0,
	.TxXferCount = 0,
	.TxState = PERIPH_STATE_RDY,
	.RxState = PERIPH_STATE_RDY
};

 
/*---------------------------------------------------------------------------------------------------*/

/* 
Initialises UART controller with attributes suggested by huart
*/

void UART_Init(UART_Handle_t *huart) 
{
	if (huart == NULL) {
		return;
	}

	if (huart->gState == PERIPH_STATE_BUSY) {
		return;
	}

	(huart->Instance)->LCR = 0x00000000UL;

	switch (huart->WordLength) {
		case 8:
			(huart->Instance)->LCR |= UART_LCR_WL8;
			break;
		case 7:
			(huart->Instance)->LCR |= UART_LCR_WL7;
			break;
		case 6:
			(huart->Instance)->LCR |= UART_LCR_WL6;
			break;
		case 5:
			(huart->Instance)->LCR |= UART_LCR_WL5;
			break;
		default:
			break;
	}
		
	switch (huart->Parity) {
		case 'n':
		case 'N':
		case 0:
			(huart->Instance)->LCR &= ~(0x1UL << UART_LCR_PE_Pos);
			break;
		case 'e':
		case 'E':
		case 2:
			(huart->Instance)->LCR |= UART_LCR_PE_EVEN;
			break;
		case 'o':
		case 'O':
		case 1:
			(huart->Instance)->LCR |= UART_LCR_PE_ODD;
			break;
		default:
			//TODO
			break;
	}

	switch (huart->StopBits) {
		case 1:
			(huart->Instance)->LCR |= UART_LCR_STOP_1;
			break;
		case 2:
			(huart->Instance)->LCR |= UART_LCR_STOP_2;
			break;
		default:
			break;
	}
	

	uint32_t divisor = (uint32_t) (SYSTEMCLK / ((huart->BaudRate) * 16));

	/* Enable Latch Access and load MSB and LSB into divisor latch register to set baud rate*/

	(huart->Instance)->LCR |= UART_LCR_DLAB;
	(huart->Instance)->DLL = divisor & 0xFFFFUL;
	(huart->Instance)->DLM = (divisor >> 8) & 0xFFFFUL;

	/* Disable Divisor Latch access */
	(huart->Instance)->LCR &= ~(UART_LCR_DLAB);

	/* Disable all UART interrupts */
	(huart->Instance)->IER = 0x00UL;
}

/*---------------------------------------------------------------------------------------------------*/

void UART_SetBaud(UART_Handle_t *huart, uint32_t baud)
{
	if (huart == NULL) {
		return;
	}

	while (huart->TxState == PERIPH_STATE_BUSY && huart->RxState == PERIPH_STATE_BUSY);

	huart->gState = PERIPH_STATE_BUSY;

	huart->BaudRate = baud;

	uint32_t divisor = (uint32_t) (SYSTEMCLK / ((huart->BaudRate) * 16));

	/* Enable Latch Access and load MSB and LSB into divisor latch register to set baud rate*/

	(huart->Instance)->LCR |= UART_LCR_DLAB;
	(huart->Instance)->DLL = divisor & 0xFFFFUL;
	(huart->Instance)->DLM = (divisor >> 8) & 0xFFFFUL;
	(huart->Instance)->LCR &= ~(UART_LCR_DLAB);

	huart->gState = PERIPH_STATE_RDY;

}

/*---------------------------------------------------------------------------------------------------*/

void UART_SetFrame(UART_Handle_t *huart, uint8_t wlen, char parity, uint8_t stopbit)
{
	if (huart == NULL) {
		return;
	}

	while (huart->TxState == PERIPH_STATE_BUSY && huart->RxState == PERIPH_STATE_BUSY);

	huart->gState = PERIPH_STATE_BUSY;

	huart->WordLength = wlen;
	huart->Parity = parity;
	huart->StopBits = stopbit;

	switch (huart->WordLength) {
		case 8:
			(huart->Instance)->LCR |= UART_LCR_WL8;
			break;
		case 7:
			(huart->Instance)->LCR |= UART_LCR_WL7;
			break;
		case 6:
			(huart->Instance)->LCR |= UART_LCR_WL6;
			break;
		case 5:
			(huart->Instance)->LCR |= UART_LCR_WL5;
			break;
		default:
			break;
	}
		
	switch (huart->Parity) {
		case 'n':
		case 'N':
		case 0:
			(huart->Instance)->LCR &= ~(0x1UL << UART_LCR_PE_Pos);
			break;
		case 'e':
		case 'E':
		case 2:
			(huart->Instance)->LCR |= UART_LCR_PE_EVEN;
			break;
		case 'o':
		case 'O':
		case 1:
			(huart->Instance)->LCR |= UART_LCR_PE_ODD;
			break;
		default:
			//TODO
			break;
	}

	switch (huart->StopBits) {
		case 1:
			(huart->Instance)->LCR |= UART_LCR_STOP_1;
			break;
		case 2:
			(huart->Instance)->LCR |= UART_LCR_STOP_2;
			break;
		default:
			break;
	}

	huart->gState = PERIPH_STATE_RDY;

}

/*---------------------------------------------------------------------------------------------------*/

void UART_PutChar(UART_Handle_t *huart, const char data)
{
	if (huart == NULL) {
		return;
	}

	/* Wait till Transmit FIFO and shift registers are empty from any previous transactions */
	while (! ((huart->Instance)->LSR & UART_LSR_TXE));

	(huart->Instance)->TXFIFO = data;
}

/*---------------------------------------------------------------------------------------------------*/

void UART_Transmit(UART_Handle_t *huart, const char *buffer, uint32_t len)
{
	if (NULL == (huart->Instance) || NULL == buffer || 0 == len) {
		return;
	}

	if (huart->TxState == PERIPH_STATE_BUSY) {
		return;
	}

	huart->TxState = PERIPH_STATE_BUSY;
	// Transmit till specified length or till buffer is empty
	while (*buffer && len--) {
		UART_PutChar(huart, *buffer++);
	}
	huart->TxState = PERIPH_STATE_RDY;
}

/*---------------------------------------------------------------------------------------------------*/

void UART_Transmit_IT(UART_Handle_t *huart, const char *buffer, uint32_t len)
{
	if (huart == NULL) {
		return;
	}

	if(huart->TxState == PERIPH_STATE_BUSY || huart->gState == PERIPH_STATE_BUSY)
	{
		return;
	}

	int irqn;
	if (huart->Instance == UART0) {
		irqn = UART0_IRQn;
	}
	else if (huart->Instance == UART1) {
		irqn = UART1_IRQn;
	}
	else if (huart->Instance == UART2) {
		irqn = UART2_IRQn;
	}
	else {
		return;
	}

	// Generate interrupts when Tx Buffer is Empty
	huart->TxBuffer = (char *)buffer;
	huart->Instance->IER |= UART_IER_TXE;
	PLIC->EN |= 0x1 << irqn;

	huart->TxState = PERIPH_STATE_BUSY;

	return;
}

/*---------------------------------------------------------------------------------------------------*/

char UART_GetChar(UART_Handle_t *huart)
{
	if (huart == NULL) {
		return -1;
	}

	//wait till RX FIFO is full
	while (! (huart->Instance->LSR & UART_LSR_RXFNE));

	return huart->Instance->RXFIFO;
}

/*---------------------------------------------------------------------------------------------------*/

void UART_Receive(UART_Handle_t *huart, char *buffer, uint32_t len)
{
	if (huart == NULL) {
		return;
	}

	if (huart->RxState == PERIPH_STATE_BUSY) {
		return;
	}

	huart->RxState = PERIPH_STATE_BUSY;
	// Receive till specified length
	for (int i = 0; i < len && buffer[i] != '\r'; i++) {
		*buffer++ = UART_GetChar(huart);
	}
	huart->RxState = PERIPH_STATE_RDY;
}

/*---------------------------------------------------------------------------------------------------*/

void UART_Receive_IT(UART_Handle_t *huart, char *buffer, uint32_t len)
{
	if (huart == NULL) {
		return;
	}

	if (huart->RxState == PERIPH_STATE_BUSY) {
		return;
	}

	int irqn;
	if (huart->Instance == UART0) {
		irqn = UART0_IRQn;
	}
	else if (huart->Instance == UART1) {
		irqn = UART1_IRQn;
	}
	else if (huart->Instance == UART2) {
		irqn = UART2_IRQn;
	}
	else {
		return;
	}

	huart->RxBuffer = buffer;
	huart->RxXferCount = len;
	huart->Instance->IER |= UART_IER_RXNE;
	PLIC->EN |= 0x1 << irqn;

	huart->RxState = PERIPH_STATE_BUSY;

	return;
	
}

/*---------------------------------------------------------------------------------------------------*/

void __UART_RxISR(UART_Handle_t *huart)
{
	*(huart->RxBuffer) = (huart->Instance->RXFIFO & 0xFFUL);
	huart->RxBuffer++;
	huart->RxXferCount--;

	if (huart->RxXferCount == 0UL) {
		huart->Instance->IER &= ~(UART_IER_RXNE);
		UART_RxCpltCallback(huart);
		huart->gState = PERIPH_STATE_RDY;
		return;
	}
}

void __UART_TxISR(UART_Handle_t *huart)
{
	huart->Instance->TXFIFO = (*(uint32_t *)huart->TxBuffer) & 0xFFUL;
	huart->TxBuffer++;
	huart->TxXferCount--;

	if (huart->TxXferCount == 0UL) {
		huart->Instance->IER &= ~(UART_IER_TXE);
		UART_TxCpltCallback(huart);
		huart->RxState = PERIPH_STATE_RDY;
		return;
	}
}

/*---------------------------------------------------------------------------------------------------*/

void UART0_IRQHandler(void)
{
	uint32_t id = UART0->IIR & 0xE;

	switch (id) {
		case UART_IIR_ID_RXNE:
			__UART_RxISR(&huart0);
			break;

		case UART_IIR_ID_TXE:
			__UART_TxISR(&huart0);
			break;

		default:
			break;
	}
}

void UART1_IRQHandler(void)
{
	uint32_t id = UART1->IIR & 0xE;

	switch (id) {
		case UART_IIR_ID_RXNE:
			__UART_RxISR(&huart1);
			break;

		case UART_IIR_ID_TXE:
			__UART_TxISR(&huart1);
			break;

		default:
			break;
	}
}

void UART2_IRQHandler(void)
{
	uint32_t id = UART2->IIR & 0xE;

	switch (id) {
		case UART_IIR_ID_RXNE:
			__UART_RxISR(&huart2);
			break;

		case UART_IIR_ID_TXE:
			__UART_TxISR(&huart2);
			break;

		default:
			break;
	}
}


__attribute__((weak)) void UART_RxCpltCallback(UART_Handle_t *huart)
{
	return;
}

__attribute__((weak)) void UART_TxCpltCallback(UART_Handle_t *huart)
{
	return;
}

/*---------------------------------------------------------------------------------------------------*/