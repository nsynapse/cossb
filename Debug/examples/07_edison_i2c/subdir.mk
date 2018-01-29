################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../examples/07_edison_i2c/example_edison_i2c.cpp 

OBJS += \
./examples/07_edison_i2c/example_edison_i2c.o 

CPP_DEPS += \
./examples/07_edison_i2c/example_edison_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
examples/07_edison_i2c/%.o: ../examples/07_edison_i2c/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D__cplusplus=201103L -D-std=c++11 -I/usr/include -I/usr/local/include -I/usr/local/Cellar/boost/1.65.1/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


