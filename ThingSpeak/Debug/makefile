################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Service/subdir.mk
-include MCAL/05UART/subdir.mk
-include MCAL/02Timer/subdir.mk
-include MCAL/01GPIO/subdir.mk
-include HAL/0AGPRS/subdir.mk
-include HAL/03\ LCD/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
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
ThingSpeak.lss \

FLASH_IMAGE += \
ThingSpeak.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: ThingSpeak.elf secondary-outputs

# Tool invocations
ThingSpeak.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,ThingSpeak.map -mmcu=atmega32 -o "ThingSpeak.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

ThingSpeak.lss: ThingSpeak.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S ThingSpeak.elf  >"ThingSpeak.lss"
	@echo 'Finished building: $@'
	@echo ' '

ThingSpeak.hex: ThingSpeak.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex ThingSpeak.elf  "ThingSpeak.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: ThingSpeak.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 ThingSpeak.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: ThingSpeak.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm32 -cusbasp -Uflash:w:ThingSpeak.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) ThingSpeak.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
