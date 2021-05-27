################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/03\ LCD/LCD.c 

OBJS += \
./HAL/03\ LCD/LCD.o 

C_DEPS += \
./HAL/03\ LCD/LCD.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/03\ LCD/LCD.o: ../HAL/03\ LCD/LCD.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"HAL/03 LCD/LCD.d" -MT"HAL/03\ LCD/LCD.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


