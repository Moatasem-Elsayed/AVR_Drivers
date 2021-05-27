################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/05UART/subdir.mk
-include MCAL/02Timer/subdir.mk
-include MCAL/01GPIO/subdir.mk
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
RFIDGraduationProject.lss \

FLASH_IMAGE += \
RFIDGraduationProject.hex \

SIZEDUMMY += \
sizedummy \

AVRDUDEDUMMY += \
avrdudedummy \


# All Target
all: RFIDGraduationProject.elf secondary-outputs

# Tool invocations
RFIDGraduationProject.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,RFIDGraduationProject.map -mmcu=atmega32 -o "RFIDGraduationProject.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

RFIDGraduationProject.lss: RFIDGraduationProject.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S RFIDGraduationProject.elf  >"RFIDGraduationProject.lss"
	@echo 'Finished building: $@'
	@echo ' '

RFIDGraduationProject.hex: RFIDGraduationProject.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex RFIDGraduationProject.elf  "RFIDGraduationProject.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: RFIDGraduationProject.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 RFIDGraduationProject.elf
	@echo 'Finished building: $@'
	@echo ' '

avrdudedummy: RFIDGraduationProject.elf
	@echo 'Invoking: AVRDude'
	C:\WinAVR-20100110\bin\avrdude -pm32 -cusbasp -Uflash:w:RFIDGraduationProject.hex:a
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(AVRDUDEDUMMY)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) RFIDGraduationProject.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY) $(AVRDUDEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
