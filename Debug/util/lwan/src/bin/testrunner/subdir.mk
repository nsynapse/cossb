################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../util/lwan/src/bin/testrunner/main.c 

OBJS += \
./util/lwan/src/bin/testrunner/main.o 

C_DEPS += \
./util/lwan/src/bin/testrunner/main.d 


# Each subdirectory must supply rules for building sources it contributes
util/lwan/src/bin/testrunner/%.o: ../util/lwan/src/bin/testrunner/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


