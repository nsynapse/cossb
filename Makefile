# Makefile for all component project

# compiler flags
#	-g	--Enable debugging
#	-Wall	--Turn on all warnings
#	-D_USE_FIXED_PROTOTYPES_
#	--Force the compiler to use the correct headers
#	-ansi	--Don't use GNU ext; do use ansi standard.

CC = gcc
CXX = g++
CXXFLAGS = -O3 -fPIC -Wall -std=c++11 -D__cplusplus=201103L -D__boostthread__
CCFLAGS = $(CXXFLAGS)
LDFLAGS = -Wl,--export-dynamic
LDLIBS = -lpopt -lboost_system -lboost_thread -lboost_filesystem -ltinyxml2 -ldl -luuid -lmraa
LDLIBS_TEST = -lpopt -lboost_system -lboost_thread -ltinyxml2 -ldl -lgtest -lpthread
INCLUDE = -I./include -I/usr/include -I/usr/local/include
RM	= rm -rf

OUTDIR		= ./bin/
INCLUDE_FILES = ./include/
EXAMPLE_FILES = ./examples/
COMPONENT_FILES = ./components/
LIB_FILES = ./lib/
UTIL_FILES = ./utils/
TEST_FILES = ./test/
SOURCE_FILES = ./src/
UTIL_FILES = ./util/
BASE_FILES = ./base/

#ossb version
CXXFLAGS += -D__MAJOR__=0 -D__MINOR__=0 -D__REV__=1


# Make COSSB Application
cossb:	$(OUTDIR)cossb.o \
		$(OUTDIR)instance.o	\
		$(OUTDIR)manifest.o \
		$(OUTDIR)sysmanager.o \
		$(OUTDIR)compmanager.o \
		$(OUTDIR)driver.o \
		$(OUTDIR)broker.o \
		$(OUTDIR)xmlprofile.o \
		$(OUTDIR)server.o \
		$(OUTDIR)client.o \
		$(OUTDIR)message.o \
		$(OUTDIR)log.o
		$(CXX) $(LDFLAGS) -o $(OUTDIR)$@ $^ $(LDLIBS)
		
cossb_test:	$(OUTDIR)cossb_test.o \
		$(OUTDIR)sysmanager_test.o \
		$(OUTDIR)instance.o	\
		$(OUTDIR)manifest.o \
		$(OUTDIR)sysmanager.o \
		$(OUTDIR)compmanager.o \
		$(OUTDIR)driver.o \
		$(OUTDIR)broker.o \
		$(OUTDIR)xmlprofile.o \
		$(OUTDIR)server.o \
		$(OUTDIR)client.o \
		$(OUTDIR)message.o \
		$(OUTDIR)log.o
		$(CXX) $(LDFLAGS) -o $(OUTDIR)$@ $^ $(LDLIBS_TEST)

# Util
wsbroadcaster: $(OUTDIR)broadcaster.o
	$(CXX) $(LDFLAGS) -o $(OUTDIR)$@ $^ -lpthread -lboost_system -lboost_regex -lssl -lcrypto
$(OUTDIR)broadcaster.o: $(UTIL_FILES)websocket/broadcaster.cpp 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
		
#examples
helloworld.comp: $(OUTDIR)helloworld.o 
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)helloworld.o: $(EXAMPLE_FILES)01_Helloworld/helloworld.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
example_tcpserver.comp: $(OUTDIR)example_tcpserver.o 
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)example_tcpserver.o: $(EXAMPLE_FILES)02_tcpserver/example_tcpserver.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
example_uart.comp: $(OUTDIR)example_uart.o 
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)example_uart.o: $(EXAMPLE_FILES)03_uart/example_uart.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
example_messageout.comp: $(OUTDIR)example_messageout.o 
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)example_messageout.o: $(EXAMPLE_FILES)04_messageout/example_messageout.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
example_messageprint.comp: $(OUTDIR)example_messageprint.o 
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)example_messageprint.o: $(EXAMPLE_FILES)05_messageprint/example_messageprint.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@	
	
example_edison_gpio.comp: $(OUTDIR)example_edison_gpio.o 
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)example_edison_gpio.o: $(EXAMPLE_FILES)06_edison_gpio/example_edison_gpio.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@	
	
example_edison_i2c.comp: $(OUTDIR)example_edison_i2c.o 
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)example_edison_i2c.o: $(EXAMPLE_FILES)07_edison_i2c/example_edison_i2c.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@	
	
example_edison_uart.comp: $(OUTDIR)example_edison_uart.o 
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)example_edison_uart.o: $(EXAMPLE_FILES)08_edison_uart/example_edison_uart.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
example_websocket_client.comp: $(OUTDIR)example_websocket_client.o 
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)example_websocket_client.o: $(EXAMPLE_FILES)09_websocket_client/example_websocket_client.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
edison_gpio.comp: $(OUTDIR)edison_gpio.o 
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)edison_gpio.o: $(COMPONENT_FILES)edison_gpio/edison_gpio.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
edison_uart.comp: $(OUTDIR)edison_uart.o 
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)edison_uart.o: $(COMPONENT_FILES)edison_uart/edison_uart.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
edison_i2c.comp: $(OUTDIR)edison_i2c.o 
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)edison_i2c.o: $(COMPONENT_FILES)edison_i2c/edison_i2c.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
tcpserver.comp: $(OUTDIR)tcpserver.o 
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)tcpserver.o: $(COMPONENT_FILES)tcpserver/tcpserver.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
serial.comp: $(OUTDIR)serial.o $(OUTDIR)libserial.o
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)serial.o: $(COMPONENT_FILES)serial/serial.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
$(OUTDIR)libserial.o: $(COMPONENT_FILES)serial/libserial.cpp 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
wsclient.comp: $(OUTDIR)wsclient.o
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)wsclient.o: $(COMPONENT_FILES)websocket/wsclient.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
uart_protocol.comp: $(OUTDIR)uart_protocol.o
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)uart_protocol.o: $(COMPONENT_FILES)uart_protocol/uart_protocol.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
		
		
$(OUTDIR)cossb.o: $(SOURCE_FILES)cossb.cpp 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)instance.o: $(INCLUDE_FILES)base/instance.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)manifest.o: $(INCLUDE_FILES)base/manifest.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)sysmanager.o: $(INCLUDE_FILES)base/sysmanager.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)compmanager.o: $(INCLUDE_FILES)base/compmanager.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)driver.o: $(INCLUDE_FILES)base/driver.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)broker.o: $(INCLUDE_FILES)base/broker.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)xmlprofile.o: $(INCLUDE_FILES)base/xmlprofile.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)log.o: $(INCLUDE_FILES)base/log.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)server.o: $(INCLUDE_FILES)net/server.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)client.o: $(INCLUDE_FILES)net/client.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)message.o: $(INCLUDE_FILES)base/message.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
#for test code	
$(OUTDIR)cossb_test.o: $(TEST_FILES)cossb_test.cpp 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)sysmanager_test.o: $(TEST_FILES)sysmanager_test.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@





# make cossb
all: cossb serial.comp tcpserver.comp example_tcpserver.comp example_uart.comp example_messageout.comp example_messageprint.comp
base: cossb
components: serial.comp tcpserver.comp uart_protocol.comp wsclient.comp
edison: edison_i2c.comp edison_uart.comp edison_gpio.comp
test: cossb_test
examples: helloworld.comp example_tcpserver.comp example_uart.comp example_messageout.comp example_messageprint.comp example_edison_gpio.comp example_edison_i2c.comp example_edison_uart.comp example_websocket_client.comp
tutorial1 : example_messageout.comp example_messageprint.comp
util: wsbroadcaster

# Clean
clean: 
	$(RM) $(OUTDIR)*.o $(OUTDIR)cossb $(OUTDIR)cossb_test $(OUTDIR)*.so $(OUTDIR)*.comp
