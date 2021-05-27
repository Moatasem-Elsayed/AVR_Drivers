################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/05UART/subdir.mk
-include MCAL/03ADC/subdir.mk
-include MCAL/02Timer/subdir.mk
-include MCAL/01GPIO/subdir.mk
-include HAL/subdir.mk
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
AinShamsGP.lss \

FLASH_IMAGE += \
AinShamsGP.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: AinShamsGP.elf secondary-outputs

# Tool invocations
AinShamsGP.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,AinShamsGP.map -mmcu=atmega32 -o "AinShamsGP.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

AinShamsGP.lss: AinShamsGP.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S AinShamsGP.elf  >"AinShamsGP.lss"
	@echo 'Finished building: $@'
	@echo ' '

AinShamsGP.hex: AinShamsGP.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex AinShamsGP.elf  "AinShamsGP.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: AinShamsGP.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 AinShamsGP.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: AinShamsGP.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm32 -cusbasp -Uflash:w:AinShamsGP.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) AinShamsGP.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
