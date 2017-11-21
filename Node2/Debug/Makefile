################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../ADC.c \
../CAN.c \
../DAC.c \
../IR.c \
../main.c \
../MCP2515.c \
../motor.c \
../PID.c \
../pong.c \
../PWM.c \
../servo.c \
../solenoid.c \
../SPI.c \
../TWI_Master.c \
../USART.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
ADC.o \
CAN.o \
DAC.o \
IR.o \
main.o \
MCP2515.o \
motor.o \
PID.o \
pong.o \
PWM.o \
servo.o \
solenoid.o \
SPI.o \
TWI_Master.o \
USART.o

OBJS_AS_ARGS +=  \
ADC.o \
CAN.o \
DAC.o \
IR.o \
main.o \
MCP2515.o \
motor.o \
PID.o \
pong.o \
PWM.o \
servo.o \
solenoid.o \
SPI.o \
TWI_Master.o \
USART.o

C_DEPS +=  \
ADC.d \
CAN.d \
DAC.d \
IR.d \
main.d \
MCP2515.d \
motor.d \
PID.d \
pong.d \
PWM.d \
servo.d \
solenoid.d \
SPI.d \
TWI_Master.d \
USART.d

C_DEPS_AS_ARGS +=  \
ADC.d \
CAN.d \
DAC.d \
IR.d \
main.d \
MCP2515.d \
motor.d \
PID.d \
pong.d \
PWM.d \
servo.d \
solenoid.d \
SPI.d \
TWI_Master.d \
USART.d

OUTPUT_FILE_PATH +=Node2.elf

OUTPUT_FILE_PATH_AS_ARGS +=Node2.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler































./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 5.4.0
	$(QUOTE)D:\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"D:\7.0\Packs\atmel\ATmega_DFP\1.2.150\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -mrelax -g2 -Wall -mmcu=atmega2560 -B "D:\7.0\Packs\atmel\ATmega_DFP\1.2.150\gcc\dev\atmega2560" -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 5.4.0
	$(QUOTE)D:\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Node2.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mrelax -mmcu=atmega2560 -B "D:\7.0\Packs\atmel\ATmega_DFP\1.2.150\gcc\dev\atmega2560"  
	@echo Finished building target: $@
	"D:\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "Node2.elf" "Node2.hex"
	"D:\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Node2.elf" "Node2.eep" || exit 0
	"D:\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "Node2.elf" > "Node2.lss"
	"D:\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "Node2.elf" "Node2.srec"
	"D:\7.0\toolchain\avr8\avr8-gnu-toolchain\bin\avr-size.exe" "Node2.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Node2.elf" "Node2.a" "Node2.hex" "Node2.lss" "Node2.eep" "Node2.map" "Node2.srec" "Node2.usersignatures"
	