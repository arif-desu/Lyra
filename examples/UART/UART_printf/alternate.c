#include <string.h>
#include <vega/interrupt.h>
#include <vega/uart.h>
#include <vega/timer.h>
#include <stdio.h>

#include <vega/thejas32.h>


extern UART_Handle_t huart0;


int _write(int file, char* ptr, int len) {
    (void)file;
    for (int idx = 0; idx < len; idx++) {
        UART_PutChar(&huart0, *ptr++);
    }
    return len;
}


int main()
{
    char buf[80] = {0};
    UART_Init(&huart0);
    
    //setbuf(stdout, NULL);

    while (1) {
        //UART_Transmit(&huart0, "\r\nEnter something : ", 20);
        printf("\r\nEnter something : ");
        fflush(stdout); 
        UART_Receive(&huart0, buf, 5);
        printf("\r\nReceived : %s",buf);
        fflush(stdout);

        memset(buf, 0, sizeof(buf));
        
    }
    
    return 0;
}



/* void UART0_IRQHandler(void)
{
    __attribute__((unused)) int status = UART0->IIR;
    char rxdata = UART0->RXBUF;
    //sprintf(buf, "UART Received : %c \r\n", rxdata);
    //UART_Transmit(&huart0, buf, strlen(buf));
    printf("UART RX Interrupt : %c\r\n",rxdata);
} */

/* void UART0_IRQHandler(void)
{
    static unsigned idx = 0;
    
    __attribute__((unused)) int status = UART0->IIR;
    char rxdata = UART0->RXBUF;
    if (idx == 0) {
        buf[idx++] = 'A';
        return;
    }
    buf[idx++] = rxdata;
    if (buf[idx] == '\r' || buf[idx] == '\n') {
        printf("Buffer : %s\r\n",buf);
        memset(buf, 0, 80);
        idx = 0;
    }
      
} */