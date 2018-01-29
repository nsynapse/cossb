################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../util/lwan/src/bin/tools/bin2hex.c \
../util/lwan/src/bin/tools/mimegen.c 

OBJS += \
./util/lwan/src/bin/tools/bin2hex.o \
./util/lwan/src/bin/tools/mimegen.o 

C_DEPS += \
./util/lwan/src/bin/tools/bin2hex.d \
./util/lwan/src/bin/tools/mimegen.d 


# Each subdirectory must supply rules for building sources it contributes
util/lwan/src/bin/tools/%.o: ../util/lwan/src/bin/tools/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


