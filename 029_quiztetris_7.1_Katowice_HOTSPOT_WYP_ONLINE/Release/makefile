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
029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.lss \

FLASH_IMAGE += \
029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.hex \

EEPROM_IMAGE += \
029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.elf secondary-outputs

# Tool invocations
029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.map -mmcu=atmega16 -o "029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.lss: 029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.elf  >"029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.lss"
	@echo 'Finished building: $@'
	@echo ' '

029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.hex: 029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.elf  "029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.hex"
	@echo 'Finished building: $@'
	@echo ' '

029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.eep: 029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.elf  "029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(M_DEPS)$(MI_DEPS)$(S_DEPS)$(LSS)$(C_DEPS)$(FLASH_IMAGE)$(ELFS)$(I_DEPS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(SIZEDUMMY)$(S_UPPER_DEPS) 029_quiztetris_7.1_Katowice_HOTSPOT_WYP_ONLINE.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
