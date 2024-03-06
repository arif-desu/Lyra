#include <vega/gpio.h>
#include <vega/interrupt.h>
#include <vega/uart.h>
#include <vega/aries.h>

#include <stdio.h>
#include <string.h>

int _write(int file, char* ptr, int len) {
    (void)file;
    UART_Transmit(&huart0, ptr, len);
    return len;
}


char buf[80] = {0};

int main()
{
    __enable_irq();

    GPIO_Init(GPIOB, RGB_GREEN, OUT);
    RGB_GREEN_RST;

    UART_Init(&huart0);
    
    while (1) {
        UART_Receive_IT(&huart0, buf, 5);
    }
    
    return 0;
}

void UART_RxCpltCallback(UART_Handle_t *huart)
{
    GPIO_TogglePin(GPIOB, RGB_GREEN);
    printf("\r\nReceived : %s",buf);
    fflush(stdout);
    memset(buf, 0, 80);
}
