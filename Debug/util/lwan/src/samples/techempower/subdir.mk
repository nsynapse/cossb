################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../util/lwan/src/samples/techempower/database.c \
../util/lwan/src/samples/techempower/json.c \
../util/lwan/src/samples/techempower/techempower.c 

OBJS += \
./util/lwan/src/samples/techempower/database.o \
./util/lwan/src/samples/techempower/json.o \
./util/lwan/src/samples/techempower/techempower.o 

C_DEPS += \
./util/lwan/src/samples/techempower/database.d \
./util/lwan/src/samples/techempower/json.d \
./util/lwan/src/samples/techempower/techempower.d 


# Each subdirectory must supply rules for building sources it contributes
util/lwan/src/samples/techempower/%.o: ../util/lwan/src/samples/techempower/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


