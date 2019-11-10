################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cct_coin.c \
../cctalk.c \
../config.c \
../eeprom.c \
../hopper.c \
../lcd_menu.c \
../lcd_new.c \
../main.c \
../timers.c \
../uart.c 

C_DEPS += \
./cct_coin.d \
./cctalk.d \
./config.d \
./eeprom.d \
./hopper.d \
./lcd_menu.d \
./lcd_new.d \
./main.d \
./timers.d \
./uart.d 

OBJS += \
./cct_coin.o \
./cctalk.o \
./config.o \
./eeprom.o \
./hopper.o \
./lcd_menu.o \
./lcd_new.o \
./main.o \
./timers.o \
./uart.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega88 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


