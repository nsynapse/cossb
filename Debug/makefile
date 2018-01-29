################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include util/websocket/subdir.mk
-include util/lwan/src/samples/techempower/subdir.mk
-include util/lwan/src/samples/freegeoip/subdir.mk
-include util/lwan/src/lib/subdir.mk
-include util/lwan/src/bin/tools/subdir.mk
-include util/lwan/src/bin/testrunner/subdir.mk
-include util/lwan/src/bin/lwan/subdir.mk
-include util/lwan/build/src/lib/CMakeFiles/lwan-static.dir/subdir.mk
-include util/lwan/build/src/lib/CMakeFiles/lwan-shared.dir/__/__/subdir.mk
-include util/lwan/build/src/bin/tools/CMakeFiles/mimegen.dir/__/__/lib/subdir.mk
-include util/lwan/build/src/bin/tools/CMakeFiles/mimegen.dir/subdir.mk
-include util/lwan/build/src/bin/tools/CMakeFiles/bin2hex.dir/subdir.mk
-include util/lwan/build/src/bin/testrunner/CMakeFiles/testrunner.dir/subdir.mk
-include util/lwan/build/src/bin/lwan/CMakeFiles/lwan.dir/subdir.mk
-include util/lwan/build/CMakeFiles/3.9.4/CompilerIdC/subdir.mk
-include util/lwan/build/CMakeFiles/subdir.mk
-include util/lwan/build/subdir.mk
-include test/subdir.mk
-include src/subdir.mk
-include include/util/subdir.mk
-include include/net/subdir.mk
-include include/file/subdir.mk
-include include/ext/subdir.mk
-include include/base/subdir.mk
-include include/3rdparty/fmt/subdir.mk
-include include/3rdparty/subdir.mk
-include examples/12_filelog/subdir.mk
-include examples/11_example_cat_db_log/subdir.mk
-include examples/10_cat_monitoring/subdir.mk
-include examples/09_websocket_client/subdir.mk
-include examples/08_edison_uart/subdir.mk
-include examples/07_edison_i2c/subdir.mk
-include examples/06_edison_gpio/subdir.mk
-include examples/05_messageprint/subdir.mk
-include examples/04_messageout/subdir.mk
-include examples/03_uart/subdir.mk
-include examples/02_tcpserver/subdir.mk
-include examples/01_Helloworld/subdir.mk
-include components/websocket/subdir.mk
-include components/uart_protocol/subdir.mk
-include components/uart/subdir.mk
-include components/timboprotocol/subdir.mk
-include components/tcpserver/subdir.mk
-include components/sqlitedb/subdir.mk
-include components/serial/subdir.mk
-include components/rpi_uart/subdir.mk
-include components/rpi_spi/subdir.mk
-include components/rpi_i2c/subdir.mk
-include components/rpi_gpio/subdir.mk
-include components/nanopi_timbo/subdir.mk
-include components/nanopi/subdir.mk
-include components/msapi_face/subdir.mk
-include components/imageviewer/subdir.mk
-include components/filelog/subdir.mk
-include components/emotion_adapter/subdir.mk
-include components/edison_uart/subdir.mk
-include components/edison_i2c/subdir.mk
-include components/edison_gpio/subdir.mk
-include components/compcontroller/subdir.mk
-include components/cat_protocol/subdir.mk
-include components/camcapture/subdir.mk
-include components/app_timbo/subdir.mk
-include components/app_picat/subdir.mk
-include bin/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: cossb

# Tool invocations
cossb: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L/usr/local/Cellar/boost/1.65.1/lib -o "cossb" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) cossb
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
