################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../util/lwan/build/CMakeFiles/3.9.4/CompilerIdC/CMakeCCompilerId.c 

OBJS += \
./util/lwan/build/CMakeFiles/3.9.4/CompilerIdC/CMakeCCompilerId.o 

C_DEPS += \
./util/lwan/build/CMakeFiles/3.9.4/CompilerIdC/CMakeCCompilerId.d 


# Each subdirectory must supply rules for building sources it contributes
util/lwan/build/CMakeFiles/3.9.4/CompilerIdC/%.o: ../util/lwan/build/CMakeFiles/3.9.4/CompilerIdC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


