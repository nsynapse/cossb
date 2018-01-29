################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../examples/11_example_cat_db_log/example_cat_db_log.cpp 

OBJS += \
./examples/11_example_cat_db_log/example_cat_db_log.o 

CPP_DEPS += \
./examples/11_example_cat_db_log/example_cat_db_log.d 


# Each subdirectory must supply rules for building sources it contributes
examples/11_example_cat_db_log/%.o: ../examples/11_example_cat_db_log/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D__cplusplus=201103L -D-std=c++11 -I/usr/include -I/usr/local/include -I/usr/local/Cellar/boost/1.65.1/include -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


