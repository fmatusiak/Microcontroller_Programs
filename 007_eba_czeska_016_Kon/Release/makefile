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
007_eba_czeska_016_Kon.lss \

FLASH_IMAGE += \
007_eba_czeska_016_Kon.hex \

EEPROM_IMAGE += \
007_eba_czeska_016_Kon.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 007_eba_czeska_016_Kon.elf secondary-outputs

# Tool invocations
007_eba_czeska_016_Kon.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,007_eba_czeska_016_Kon.map -mmcu=atmega8 -o "007_eba_czeska_016_Kon.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

007_eba_czeska_016_Kon.lss: 007_eba_czeska_016_Kon.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 007_eba_czeska_016_Kon.elf  >"007_eba_czeska_016_Kon.lss"
	@echo 'Finished building: $@'
	@echo ' '

007_eba_czeska_016_Kon.hex: 007_eba_czeska_016_Kon.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 007_eba_czeska_016_Kon.elf  "007_eba_czeska_016_Kon.hex"
	@echo 'Finished building: $@'
	@echo ' '

007_eba_czeska_016_Kon.eep: 007_eba_czeska_016_Kon.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 007_eba_czeska_016_Kon.elf  "007_eba_czeska_016_Kon.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 007_eba_czeska_016_Kon.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 007_eba_czeska_016_Kon.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(M_DEPS)$(MI_DEPS)$(S_DEPS)$(LSS)$(C_DEPS)$(FLASH_IMAGE)$(ELFS)$(I_DEPS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(SIZEDUMMY)$(S_UPPER_DEPS) 007_eba_czeska_016_Kon.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
