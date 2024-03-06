# Specify executable name
TARGET = uart_interrupt

# C source files
C_SOURCES = \
main.c \
syscalls.c \
sysmem.c \
$(VEGA_SDK_PATH)/drivers/hal_gpio.c \
$(VEGA_SDK_PATH)/drivers/hal_timer.c \
$(VEGA_SDK_PATH)/drivers/hal_interrupt.c \
$(VEGA_SDK_PATH)/drivers/hal_uart.c \

FLASHMODE = 1

include $(VEGA_SDK_PATH)/build.mk
