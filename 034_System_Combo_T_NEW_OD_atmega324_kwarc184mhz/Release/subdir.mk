################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BillAcceptor.c \
../CoinAcceptor.c \
../HD44780.c \
../Hopper.c \
../IO_Button.c \
../IO_Combo.c \
../LCD.c \
../main.c 

C_DEPS += \
./BillAcceptor.d \
./CoinAcceptor.d \
./HD44780.d \
./Hopper.d \
./IO_Button.d \
./IO_Combo.d \
./LCD.d \
./main.d 

OBJS += \
./BillAcceptor.o \
./CoinAcceptor.o \
./HD44780.o \
./Hopper.o \
./IO_Button.o \
./IO_Combo.o \
./LCD.o \
./main.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328 -DF_CPU=18432000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


