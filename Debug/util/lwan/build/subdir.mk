################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../util/lwan/build/empty.c 

OBJS += \
./util/lwan/build/empty.o 

C_DEPS += \
./util/lwan/build/empty.d 


# Each subdirectory must supply rules for building sources it contributes
util/lwan/build/%.o: ../util/lwan/build/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


