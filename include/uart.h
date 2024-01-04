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
	uint8_t WordLength;
	uint8_t Parity;
	uint8_t StopBits;
} UART_Frame_t;



void UART_Init(UART_Reg_Type *UARTx, uint32_t baud, const UART_Frame_t *frame);

void UART_Init_IT(UART_Reg_Type *UARTx, uint32_t baud, const UART_Frame_t *frame, uint8_t int_flags);

void UART_Transmit(UART_Reg_Type *UARTx, const char *buffer, unsigned int len);

void UART_Transmit_IT(UART_Reg_Type *UARTx, const char *buffer);

void UART_Receive(UART_Reg_Type *UARTx, char *buffer);

void UART_Receive_IT(UART_Reg_Type *UARTx, char *buffer);

#endif /*__UART_H*/