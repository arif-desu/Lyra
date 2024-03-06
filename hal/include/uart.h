/**
 @file uart.h
 @brief header file for UART driver
 @author Arif B (arif.dev@pm.me)
 */

#ifndef _UART_H_
#define _UART_H_


#include <vega/thejas32.h>

#include <stdint.h>



#define UART_PARITY_NONE		('N')
#define UART_PARITY_ODD			('O')
#define UART_PARITY_EVEN		('E')


typedef enum {
	UART_TRXN_SUCCESS = 0,
	UART_PARITY_ERROR,
	UART_OVERRUN_ERROR,
	UART_FRAMING_ERROR
} UART_Status_t;


typedef struct {
	UART_Reg_t *Instance;
	uint32_t BaudRate;
	uint32_t WordLength;
	uint32_t Parity;
	uint32_t StopBits;
	uint32_t gState;
	char *TxBuffer;
	uint32_t TxXferCount;
	uint32_t TxState;
	char *RxBuffer;
	uint32_t RxXferCount;
	uint32_t RxState;
} UART_Handle_t;

extern UART_Handle_t huart0;
extern UART_Handle_t huart1;
extern UART_Handle_t huart2;

/* Initialise the UART controller  */
void UART_Init(UART_Handle_t *huart);

/* Set UART Baud rate */
void UART_SetBaud(UART_Handle_t *huart, uint32_t baud);

/* Set UART frame format */
void UART_SetFrame(UART_Handle_t *huart, uint8_t wlen, char parity, uint8_t stopbit);

/* Blocking call to transmit a string buffer via UART */
void UART_Transmit(UART_Handle_t *huart, const char *buffer, uint32_t len);

/* Asynchronous call to transmit a string via UART */
void UART_Transmit_IT(UART_Handle_t *huart, const char *buffer, uint32_t len);

/* UART IRQ callback for TX transaction completion */
void UART_TxCpltCallback(UART_Handle_t *huart);

void UART_Receive(UART_Handle_t *huart, char *buffer, uint32_t len);

void UART_Receive_IT(UART_Handle_t *huart, char *buffer, uint32_t len);

void UART_RxCpltCallback(UART_Handle_t *huart);



#endif /*_UART_H_*/