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
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(M_DEPS)),)
-include $(M_DEPS)
endif
ifneq ($(strip $(CP_DEPS)),)
-include $(CP_DEPS)
endif
ifneq ($(strip $(MI_DEPS)),)
-include $(MI_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(M_UPPER_DEPS)),)
-include $(M_UPPER_DEPS)
endif
ifneq ($(strip $(I_DEPS)),)
-include $(I_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(MII_DEPS)),)
-include $(MII_DEPS)
endif
ifneq ($(strip $(MM_DEPS)),)
-include $(MM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
m88_exchange_20180314.lss \

FLASH_IMAGE += \
m88_exchange_20180314.hex \

EEPROM_IMAGE += \
m88_exchange_20180314.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: m88_exchange_20180314.elf secondary-outputs

# Tool invocations
m88_exchange_20180314.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-g++ -Wl,-Map,m88_exchange_20180314.map,--cref -mrelax -Wl,--gc-sections -mmcu=atmega88 -o "m88_exchange_20180314.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

m88_exchange_20180314.lss: m88_exchange_20180314.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S m88_exchange_20180314.elf  >"m88_exchange_20180314.lss"
	@echo 'Finished building: $@'
	@echo ' '

m88_exchange_20180314.hex: m88_exchange_20180314.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex m88_exchange_20180314.elf  "m88_exchange_20180314.hex"
	@echo 'Finished building: $@'
	@echo ' '

m88_exchange_20180314.eep: m88_exchange_20180314.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex m88_exchange_20180314.elf  "m88_exchange_20180314.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: m88_exchange_20180314.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega88 m88_exchange_20180314.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(M_DEPS)$(CP_DEPS)$(MI_DEPS)$(S_DEPS)$(LSS)$(C_DEPS)$(FLASH_IMAGE)$(CC_DEPS)$(ELFS)$(C++_DEPS)$(M_UPPER_DEPS)$(I_DEPS)$(OBJS)$(CXX_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(MII_DEPS)$(MM_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(CPP_DEPS) m88_exchange_20180314.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
