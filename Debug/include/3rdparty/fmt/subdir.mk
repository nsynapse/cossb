################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../include/3rdparty/fmt/format.cc \
../include/3rdparty/fmt/ostream.cc \
../include/3rdparty/fmt/posix.cc \
../include/3rdparty/fmt/printf.cc 

CC_DEPS += \
./include/3rdparty/fmt/format.d \
./include/3rdparty/fmt/ostream.d \
./include/3rdparty/fmt/posix.d \
./include/3rdparty/fmt/printf.d 

OBJS += \
./include/3rdparty/fmt/format.o \
./include/3rdparty/fmt/ostream.o \
./include/3rdparty/fmt/posix.o \
./include/3rdparty/fmt/printf.o 


# Each subdirectory must supply rules for building sources it contributes
include/3rdparty/fmt/%.o: ../include/3rdparty/fmt/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D__cplusplus=201103L -D-std=c++11 -I/usr/include -I/usr/local/include -I/usr/local/Cellar/boost/1.65.1/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


