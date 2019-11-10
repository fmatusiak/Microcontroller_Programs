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
043_Tetris_v_test_final.lss \

FLASH_IMAGE += \
043_Tetris_v_test_final.hex \

EEPROM_IMAGE += \
043_Tetris_v_test_final.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 043_Tetris_v_test_final.elf secondary-outputs

# Tool invocations
043_Tetris_v_test_final.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,043_Tetris_v_test_final.map -mmcu=atmega16 -o "043_Tetris_v_test_final.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

043_Tetris_v_test_final.lss: 043_Tetris_v_test_final.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 043_Tetris_v_test_final.elf  >"043_Tetris_v_test_final.lss"
	@echo 'Finished building: $@'
	@echo ' '

043_Tetris_v_test_final.hex: 043_Tetris_v_test_final.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 043_Tetris_v_test_final.elf  "043_Tetris_v_test_final.hex"
	@echo 'Finished building: $@'
	@echo ' '

043_Tetris_v_test_final.eep: 043_Tetris_v_test_final.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 043_Tetris_v_test_final.elf  "043_Tetris_v_test_final.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 043_Tetris_v_test_final.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 043_Tetris_v_test_final.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(M_DEPS)$(MI_DEPS)$(S_DEPS)$(LSS)$(C_DEPS)$(FLASH_IMAGE)$(ELFS)$(I_DEPS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(SIZEDUMMY)$(S_UPPER_DEPS) 043_Tetris_v_test_final.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
