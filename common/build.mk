######################################
# target
######################################
ifndef TARGET
TARGET = app
endif

######################################
# building variables
######################################
# debug build?
ifndef DEBUG
DEBUG = 0
endif
# optimization
ifndef OPT
OPT = -O0
endif

#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES += 

# ASM sources
ASM_SOURCES +=  \
$(VEGA_SDK_PATH)/startup.s

#######################################
# binaries
#######################################
PREFIX = riscv-none-elf-
# The gcc compiler bin path can be either defined in make command via CC_PATH variable (> make CC_PATH=xxx)
# or it can be added to the PATH environment variable.
ifdef CC_PATH
CC = $(CC_PATH)/$(PREFIX)gcc
AS = $(CC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(CC_PATH)/$(PREFIX)objcopy
SZ = $(CC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# Memory model
CODEMODEL = -mcmodel=medany

#ISA Arch
ARCH = -march=rv32im_zicsr_zifencei

# ABI
ABI = -mabi=ilp32

# mcu
MCU = $(CODEMODEL) $(ARCH) $(ABI)

# macros for gcc
# AS defines
AS_DEFS += 

# C defines
C_DEFS +=  

# AS includes
AS_INCLUDES += 

# C includes
C_INCLUDES += \
-I/usr/local/include


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
ifndef LDSCRIPT
LDSCRIPT = $(VEGA_SDK_PATH)/thejas32mem.ld
endif

# libraries
LIBS += -lc -lm -lnosys 
LIBDIR += 
LDFLAGS = $(MCU) -specs=nano.specs -nostartfiles -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	@-$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	@-$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	@-$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	@-$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@-$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	@-$(BIN) $< $@	
	
$(BUILD_DIR):
	@-mkdir $@		

#######################################
# Phony targets
#######################################
.PHONY:	clean

#######################################
# clean up
#######################################
clean:
	@echo Cleaning up build artifacts...
	@-rm -rf $(BUILD_DIR)

#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***