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
011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.lss \

FLASH_IMAGE += \
011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.hex \

EEPROM_IMAGE += \
011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: 011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.elf secondary-outputs

# Tool invocations
011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.map -mmcu=atmega8 -o "011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.lss: 011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S 011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.elf  >"011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.lss"
	@echo 'Finished building: $@'
	@echo ' '

011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.hex: 011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex 011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.elf  "011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.hex"
	@echo 'Finished building: $@'
	@echo ' '

011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.eep: 011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex 011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.elf  "011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: 011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega8 011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(M_DEPS)$(MI_DEPS)$(S_DEPS)$(LSS)$(C_DEPS)$(FLASH_IMAGE)$(ELFS)$(I_DEPS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(SIZEDUMMY)$(S_UPPER_DEPS) 011_rozmieniarka_hr1_paraller_zezwolenie_binarny_5zl_bez_zab.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
