################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../include/base/broker.cpp \
../include/base/compmanager.cpp \
../include/base/driver.cpp \
../include/base/errorcode.cpp \
../include/base/instance.cpp \
../include/base/jsonprofile.cpp \
../include/base/log.cpp \
../include/base/manifest.cpp \
../include/base/message.cpp \
../include/base/message_any.cpp \
../include/base/message_json.cpp \
../include/base/search.cpp \
../include/base/sysmanager.cpp \
../include/base/xmlprofile.cpp 

OBJS += \
./include/base/broker.o \
./include/base/compmanager.o \
./include/base/driver.o \
./include/base/errorcode.o \
./include/base/instance.o \
./include/base/jsonprofile.o \
./include/base/log.o \
./include/base/manifest.o \
./include/base/message.o \
./include/base/message_any.o \
./include/base/message_json.o \
./include/base/search.o \
./include/base/sysmanager.o \
./include/base/xmlprofile.o 

CPP_DEPS += \
./include/base/broker.d \
./include/base/compmanager.d \
./include/base/driver.d \
./include/base/errorcode.d \
./include/base/instance.d \
./include/base/jsonprofile.d \
./include/base/log.d \
./include/base/manifest.d \
./include/base/message.d \
./include/base/message_any.d \
./include/base/message_json.d \
./include/base/search.d \
./include/base/sysmanager.d \
./include/base/xmlprofile.d 


# Each subdirectory must supply rules for building sources it contributes
include/base/%.o: ../include/base/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D__cplusplus=201103L -D-std=c++11 -I/usr/include -I/usr/local/include -I/usr/local/Cellar/boost/1.65.1/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


