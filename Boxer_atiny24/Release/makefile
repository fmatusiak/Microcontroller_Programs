################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(I_DEPS)),)
-include $(I_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(M_DEPS)),)
-include $(M_DEPS)
endif
ifneq ($(strip $(MI_DEPS)),)
-include $(MI_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Boxer_atiny24.lss \

FLASH_IMAGE += \
Boxer_atiny24.hex \

EEPROM_IMAGE += \
Boxer_atiny24.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Boxer_atiny24.elf secondary-outputs

# Tool invocations
Boxer_atiny24.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Boxer_atiny24.map -mmcu=attiny24a -o "Boxer_atiny24.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Boxer_atiny24.lss: Boxer_atiny24.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Boxer_atiny24.elf  >"Boxer_atiny24.lss"
	@echo 'Finished building: $@'
	@echo ' '

Boxer_atiny24.hex: Boxer_atiny24.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Boxer_atiny24.elf  "Boxer_atiny24.hex"
	@echo 'Finished building: $@'
	@echo ' '

Boxer_atiny24.eep: Boxer_atiny24.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Boxer_atiny24.elf  "Boxer_atiny24.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Boxer_atiny24.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=attiny24a Boxer_atiny24.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(M_DEPS)$(MI_DEPS)$(S_DEPS)$(LSS)$(C_DEPS)$(FLASH_IMAGE)$(ELFS)$(I_DEPS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(SIZEDUMMY)$(S_UPPER_DEPS) Boxer_atiny24.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
