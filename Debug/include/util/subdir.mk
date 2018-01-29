################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../include/util/format.cc \
../include/util/ostream.cc 

CPP_SRCS += \
../include/util/filesystem.cpp \
../include/util/localtime.cpp \
../include/util/pid.cpp \
../include/util/sha1.cpp \
../include/util/utilloader.cpp 

CC_DEPS += \
./include/util/format.d \
./include/util/ostream.d 

OBJS += \
./include/util/filesystem.o \
./include/util/format.o \
./include/util/localtime.o \
./include/util/ostream.o \
./include/util/pid.o \
./include/util/sha1.o \
./include/util/utilloader.o 

CPP_DEPS += \
./include/util/filesystem.d \
./include/util/localtime.d \
./include/util/pid.d \
./include/util/sha1.d \
./include/util/utilloader.d 


# Each subdirectory must supply rules for building sources it contributes
include/util/%.o: ../include/util/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D__cplusplus=201103L -D-std=c++11 -I/usr/include -I/usr/local/include -I/usr/local/Cellar/boost/1.65.1/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/util/%.o: ../include/util/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D__cplusplus=201103L -D-std=c++11 -I/usr/include -I/usr/local/include -I/usr/local/Cellar/boost/1.65.1/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


