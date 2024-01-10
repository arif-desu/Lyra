/**
 @file uart.h
 @brief header file for UART driver
 @detail 
 */

#ifndef __UART_H
#define __UART_H

#include <vega/thejas32.h>

#include <stdint.h>


typedef enum {
	UART_TRXN_SUCCESS = 0,
	UART_PARITY_ERROR,
	UART_OVERRUN_ERROR,
	UART_FRAMING_ERROR
} UART_ReturnStatus;

typedef struct {
	uint16_t WordLength;
	char Parity;
	uint16_t StopBits;
} UART_Frame_t;


/* 
Initialises UART controller in blocking mode 
@param UARTx - UART controller
@param Baud  - Baud Rate 
@param Frame - Frame format <WordLength><Parity><StopBits>

Default - If Frame is passed as NULL, defaults to 8N1
@return : void
*/

void UART_Init(UART_Reg_t *UARTx, uint32_t baud, const UART_Frame_t *frame);



void UART_Init_IT(UART_Reg_t *UARTx, uint32_t baud, const UART_Frame_t *frame, uint8_t int_flags);

void UART_TxChar(UART_Reg_t *UARTx, const char data);

void UART_Transmit(UART_Reg_t *UARTx, const char *buffer, uint32_t len);

void UART_Transmit_IT(UART_Reg_t *UARTx, const char *buffer);

void UART_Receive(UART_Reg_t *UARTx, char *buffer);

void UART_Receive_IT(UART_Reg_t *UARTx, char *buffer);

#endif /*__UART_H*/