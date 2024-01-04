# Specify executable name
TARGET = vega_app

# C source files
# REMARK - To include all drivers: $(wildcard $(VEGA_SDK_PATH)/drivers/*.c)
C_SOURCES = \
main.c \
$(VEGA_SDK_PATH)/drivers/gpio.c

# C header include path(s)
C_INCLUDES = 

# Assembly (.s) source files
ASM_SOURCES = 

# AS Includes
AS_INCLUDES =

# Libraries
LIBS = 
LIBDIR =

# Optional parameters
#  DEBUG = 1 => include debug symbols in executable
DEBUG = 0

# OPT - Optimization ,default -O0 
# Read https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html
OPT = -Og

include $(VEGA_SDK_PATH)/build.mk
