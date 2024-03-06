#include <vega/uart.h>

#include <stdio.h>
#include <string.h>

extern UART_Handle_t huart0;

int main()
{
    char buf[80];
    char rxdata;

    UART_Init(&huart0);

    while (1) {
        rxdata = UART_GetChar(&huart0);
        
        sprintf(buf, "Received : %c \r\n", rxdata);

        UART_Transmit(&huart0, buf, strlen(buf));
        
    }
    
    return 0;
}

