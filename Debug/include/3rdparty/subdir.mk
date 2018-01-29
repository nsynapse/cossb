################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../include/3rdparty/bcm2835.c 

OBJS += \
./include/3rdparty/bcm2835.o 

C_DEPS += \
./include/3rdparty/bcm2835.d 


# Each subdirectory must supply rules for building sources it contributes
include/3rdparty/%.o: ../include/3rdparty/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


