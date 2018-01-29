################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../components/rpi_uart/libserial.cpp \
../components/rpi_uart/rpi_uart.cpp 

OBJS += \
./components/rpi_uart/libserial.o \
./components/rpi_uart/rpi_uart.o 

CPP_DEPS += \
./components/rpi_uart/libserial.d \
./components/rpi_uart/rpi_uart.d 


# Each subdirectory must supply rules for building sources it contributes
components/rpi_uart/%.o: ../components/rpi_uart/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D__cplusplus=201103L -D-std=c++11 -I/usr/include -I/usr/local/include -I/usr/local/Cellar/boost/1.65.1/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


