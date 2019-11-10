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
034_Uba10_apollo_emulacja_banknociarki_new.lss \

FLASH_IMAGE += \
034_Uba10_apollo_emulacja_banknociarki_new.hex \

EEPROM_IMAGE += \
034_Uba10_apollo_emulacja_banknociarki_new.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 034_Uba10_apollo_emulacja_banknociarki_new.elf secondary-outputs

# Tool invocations
034_Uba10_apollo_emulacja_banknociarki_new.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,034_Uba10_apollo_emulacja_banknociarki_new.map -mmcu=atmega8 -o "034_Uba10_apollo_emulacja_banknociarki_new.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

034_Uba10_apollo_emulacja_banknociarki_new.lss: 034_Uba10_apollo_emulacja_banknociarki_new.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 034_Uba10_apollo_emulacja_banknociarki_new.elf  >"034_Uba10_apollo_emulacja_banknociarki_new.lss"
	@echo 'Finished building: $@'
	@echo ' '

034_Uba10_apollo_emulacja_banknociarki_new.hex: 034_Uba10_apollo_emulacja_banknociarki_new.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 034_Uba10_apollo_emulacja_banknociarki_new.elf  "034_Uba10_apollo_emulacja_banknociarki_new.hex"
	@echo 'Finished building: $@'
	@echo ' '

034_Uba10_apollo_emulacja_banknociarki_new.eep: 034_Uba10_apollo_emulacja_banknociarki_new.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 034_Uba10_apollo_emulacja_banknociarki_new.elf  "034_Uba10_apollo_emulacja_banknociarki_new.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 034_Uba10_apollo_emulacja_banknociarki_new.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 034_Uba10_apollo_emulacja_banknociarki_new.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(M_DEPS)$(MI_DEPS)$(S_DEPS)$(LSS)$(C_DEPS)$(FLASH_IMAGE)$(ELFS)$(I_DEPS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(SIZEDUMMY)$(S_UPPER_DEPS) 034_Uba10_apollo_emulacja_banknociarki_new.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
