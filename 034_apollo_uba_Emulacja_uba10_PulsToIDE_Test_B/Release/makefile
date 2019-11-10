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
034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.lss \

FLASH_IMAGE += \
034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.hex \

EEPROM_IMAGE += \
034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.elf secondary-outputs

# Tool invocations
034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.map -mmcu=atmega8 -o "034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.lss: 034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.elf  >"034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.lss"
	@echo 'Finished building: $@'
	@echo ' '

034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.hex: 034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.elf  "034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.hex"
	@echo 'Finished building: $@'
	@echo ' '

034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.eep: 034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.elf  "034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(M_DEPS)$(MI_DEPS)$(S_DEPS)$(LSS)$(C_DEPS)$(FLASH_IMAGE)$(ELFS)$(I_DEPS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(SIZEDUMMY)$(S_UPPER_DEPS) 034_apollo_uba_Emulacja_uba10_PulsToIDE_Test_B.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
