# COSSB Makefile

OS := $(shell uname)

ifeq ($(OS),Darwin) #Mac OS
	LDFLAGS = -dynamiclib
	INCLUDE += -I/usr/local/Cellar/boost/1.66.0/include
	LD_LIBRARY_PATH += -L/usr/local/Cellar/boost/1.66.0/lib/ -L/usr/local/opt/openssl/lib/
	LDLIBS = -lboost_system-mt -lboost_thread-mt -lboost_filesystem-mt
endif

ifeq ($(OS),Linux) #Linux
	LDFLAGS = -Wl,--export-dynamic
	LDLIBS = -lboost_system -lboost_thread -lboost_filesystem -ldl -luuid 
endif

CXX = g++
CXXFLAGS = -O3 -fPIC -Wall -std=c++11 -D__cplusplus=201103L -D__boostthread__

EDISON_LDLIBS = -lmraa
INCLUDE += -I./include -I/usr/include -I/usr/local/include -I/usr/local/opt/openssl/include/
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

#cossb version
CXXFLAGS += -D__MAJOR__=0 -D__MINOR__=0 -D__REV__=2


# Make COSSB Application
cossb:	$(OUTDIR)cossb.o \
		$(OUTDIR)instance.o	\
		$(OUTDIR)manifest.o \
		$(OUTDIR)sysmanager.o \
		$(OUTDIR)compmanager.o \
		$(OUTDIR)driver.o \
		$(OUTDIR)broker.o \
		$(OUTDIR)xmlprofile.o \
		$(OUTDIR)message_any.o \
		$(OUTDIR)log.o\
		$(OUTDIR)localtime.o \
		$(OUTDIR)ostream.o \
		$(OUTDIR)format.o \
		$(OUTDIR)tinyxml2.o
		$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -o $(OUTDIR)$@ $^ $(LDLIBS)

# Util
wsbroadcaster: $(OUTDIR)broadcaster.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -o $(OUTDIR)$@ $^ -lpthread -lboost_system -lboost_regex -lssl -lcrypto
$(OUTDIR)broadcaster.o: $(UTIL_FILES)websocket/broadcaster.cpp 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

		
#examples
	
helloworld.comp: $(OUTDIR)helloworld.o \
					$(OUTDIR)message_any.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)helloworld.o: $(EXAMPLE_FILES)01_Helloworld/helloworld.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
example_tcpserver.comp: $(OUTDIR)example_tcpserver.o 
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)example_tcpserver.o: $(EXAMPLE_FILES)02_tcpserver/example_tcpserver.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
example_uart.comp: $(OUTDIR)example_uart.o 
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)example_uart.o: $(EXAMPLE_FILES)03_uart/example_uart.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
example_messageout.comp: $(OUTDIR)example_messageout.o 
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)example_messageout.o: $(EXAMPLE_FILES)04_messageout/example_messageout.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
example_messageprint.comp: $(OUTDIR)example_messageprint.o 
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)example_messageprint.o: $(EXAMPLE_FILES)05_messageprint/example_messageprint.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@	
	
example_edison_gpio.comp: $(OUTDIR)example_edison_gpio.o 
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS) $(EDISON_LDLIBS)
$(OUTDIR)example_edison_gpio.o: $(EXAMPLE_FILES)06_edison_gpio/example_edison_gpio.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@	
	
example_edison_i2c.comp: $(OUTDIR)example_edison_i2c.o 
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS) $(EDISON_LDLIBS)
$(OUTDIR)example_edison_i2c.o: $(EXAMPLE_FILES)07_edison_i2c/example_edison_i2c.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@	
	
example_edison_uart.comp: $(OUTDIR)example_edison_uart.o 
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS) $(EDISON_LDLIBS)
$(OUTDIR)example_edison_uart.o: $(EXAMPLE_FILES)08_edison_uart/example_edison_uart.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
example_websocket_client.comp: $(OUTDIR)example_websocket_client.o 
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)example_websocket_client.o: $(EXAMPLE_FILES)09_websocket_client/example_websocket_client.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
example_cat_monitoring.comp: $(OUTDIR)example_cat_monitoring.o 
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)example_cat_monitoring.o: $(EXAMPLE_FILES)10_cat_monitoring/example_cat_monitoring.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
example_cat_db_log.comp: $(OUTDIR)example_cat_db_log.o 
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)example_cat_db_log.o: $(EXAMPLE_FILES)11_example_cat_db_log/example_cat_db_log.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

example_filelog.comp: $(OUTDIR)example_filelog.o 
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)example_filelog.o: $(EXAMPLE_FILES)12_filelog/example_filelog.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
edison_gpio.comp: $(OUTDIR)edison_gpio.o 
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS) $(EDISON_LDLIBS)
$(OUTDIR)edison_gpio.o: $(COMPONENT_FILES)edison_gpio/edison_gpio.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
edison_uart.comp: $(OUTDIR)edison_uart.o 
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS) $(EDISON_LDLIBS)
$(OUTDIR)edison_uart.o: $(COMPONENT_FILES)edison_uart/edison_uart.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
edison_i2c.comp: $(OUTDIR)edison_i2c.o 
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS) $(EDISON_LDLIBS)
$(OUTDIR)edison_i2c.o: $(COMPONENT_FILES)edison_i2c/edison_i2c.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
tcpserver.comp: $(OUTDIR)tcpserver.o 
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)tcpserver.o: $(COMPONENT_FILES)tcpserver/tcpserver.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
serial.comp: $(OUTDIR)serial.o \
				$(OUTDIR)libserial.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)serial.o: $(COMPONENT_FILES)serial/serial.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
$(OUTDIR)libserial.o: $(COMPONENT_FILES)serial/libserial.cpp 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
wsclient.comp: $(OUTDIR)wsclient.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)wsclient.o: $(COMPONENT_FILES)websocket/wsclient.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
sqlitedb.comp: $(OUTDIR)sqlitedb.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)sqlitedb.o: $(COMPONENT_FILES)sqlitedb/sqlitedb.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
uart_protocol.comp: $(OUTDIR)uart_protocol.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)uart_protocol.o: $(COMPONENT_FILES)uart_protocol/uart_protocol.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
cat_protocol.comp: $(OUTDIR)cat_protocol.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)cat_protocol.o: $(COMPONENT_FILES)cat_protocol/cat_protocol.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
filelog.comp: $(OUTDIR)filelog.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)filelog.o: $(COMPONENT_FILES)filelog/filelog.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
compcontroller.comp: $(OUTDIR)compcontroller.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)compcontroller.o: $(COMPONENT_FILES)compcontroller/compcontroller.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
camcapture.comp: $(OUTDIR)camcapture.o \
					$(OUTDIR)message_any.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS) -lopencv_core -lopencv_videoio -lopencv_video -lopencv_highgui
$(OUTDIR)camcapture.o: $(COMPONENT_FILES)camcapture/camcapture.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
msapi_face.comp: $(OUTDIR)msapi_face.o \
					  $(OUTDIR)message_any.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS) -lpython2.7 -lopencv_core -lopencv_imgcodecs
$(OUTDIR)msapi_face.o: $(COMPONENT_FILES)msapi_face/msapi_face.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
rpi_spi.comp: $(OUTDIR)rpi_spi.o \
				$(OUTDIR)message_any.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS) -lbcm2835
$(OUTDIR)rpi_spi.o: $(COMPONENT_FILES)rpi_spi/rpi_spi.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
rpi_gpio.comp: $(OUTDIR)rpi_gpio.o \
				$(OUTDIR)message_any.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS) -lbcm2835
$(OUTDIR)rpi_gpio.o: $(COMPONENT_FILES)rpi_gpio/rpi_gpio.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
rpi_uart.comp: $(OUTDIR)rpi_uart.o \
				$(OUTDIR)message_any.o \
				$(OUTDIR)librpiuart.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)rpi_uart.o: $(COMPONENT_FILES)rpi_uart/rpi_uart.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
$(OUTDIR)librpiuart.o: $(COMPONENT_FILES)rpi_uart/libserial.cpp 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
imageviewer.comp: $(OUTDIR)imageviewer.o \
				$(OUTDIR)message_any.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)imageviewer.o: $(COMPONENT_FILES)imageviewer/imageviewer.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
rpi_i2c.comp: $(OUTDIR)rpi_i2c.o \
				$(OUTDIR)message_any.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS) -lbcm2835
$(OUTDIR)rpi_i2c.o: $(COMPONENT_FILES)rpi_i2c/rpi_i2c.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
emotion_adapter.comp: $(OUTDIR)emotion_adapter.o \
				$(OUTDIR)message_any.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)emotion_adapter.o: $(COMPONENT_FILES)emotion_adapter/emotion_adapter.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@	
	
app_picat.comp: $(OUTDIR)app_picat.o \
				$(OUTDIR)message_any.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)app_picat.o: $(COMPONENT_FILES)app_picat/app_picat.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

#UART Comoponent (may equal to serial component)	
uart.comp: $(OUTDIR)uart.o \
			$(OUTDIR)libuart.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)uart.o: $(COMPONENT_FILES)uart/uart.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
$(OUTDIR)libuart.o: $(COMPONENT_FILES)uart/libserial.cpp 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
app_timbo.comp: $(OUTDIR)app_timbo.o \
				$(OUTDIR)message_any.o \
				$(OUTDIR)app_timbo_func.o \
				$(OUTDIR)collector.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)app_timbo.o: $(COMPONENT_FILES)app_timbo/app_timbo.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
$(OUTDIR)app_timbo_func.o: $(COMPONENT_FILES)app_timbo/app_timbo_func.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
timboprotocol.comp: $(OUTDIR)timboprotocol.o \
				$(OUTDIR)message_any.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)timboprotocol.o: $(COMPONENT_FILES)timboprotocol/timboprotocol.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
nanopi.comp: $(OUTDIR)nanopi.o \
				$(OUTDIR)message_any.o
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS) -lwiringPi -lpthread
$(OUTDIR)nanopi.o: $(COMPONENT_FILES)nanopi/nanopi.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
nanopi_timbo.comp: $(OUTDIR)nanopi_timbo.o \
				$(OUTDIR)timbouart.o \
				$(OUTDIR)message_any.o 
	$(CXX) $(LDFLAGS) $(LD_LIBRARY_PATH) -shared -o $(OUTDIR)$@ $^ $(LDLIBS) -lwiringPi -lpthread
$(OUTDIR)nanopi_timbo.o: $(COMPONENT_FILES)nanopi_timbo/nanopi_timbo.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
$(OUTDIR)timbouart.o: $(COMPONENT_FILES)nanopi_timbo/libserial.cpp 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
	
$(OUTDIR)message_any.o: $(INCLUDE_FILES)base/message_any.cpp 
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
	
$(OUTDIR)localtime.o: $(INCLUDE_FILES)util/localtime.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

	
$(OUTDIR)ostream.o: $(INCLUDE_FILES)util/ostream.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)format.o: $(INCLUDE_FILES)util/format.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)tinyxml2.o: $(INCLUDE_FILES)ext/tinyxml2.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@

$(OUTDIR)collector.o: $(INCLUDE_FILES)file/collector.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@



# make cossb
all: cossb serial.comp tcpserver.comp example_tcpserver.comp example_uart.comp example_messageout.comp example_messageprint.comp
timbo : cossb timboprotocol.comp app_timbo.comp wsclient.comp wsbroadcaster nanopi_timbo.comp
picat : cossb cv_capture.comp msapi_emotion.comp
base: cossb
components: serial.comp tcpserver.comp uart_protocol.comp wsclient.comp cat_protocol.comp
edison: edison_i2c.comp edison_uart.comp edison_gpio.comp
test: cossb_test
examples: helloworld.comp example_tcpserver.comp example_uart.comp example_messageout.comp example_messageprint.comp example_edison_gpio.comp example_edison_i2c.comp example_edison_uart.comp example_websocket_client.comp example_cat_monitoring.comp example_filelog.comp
tutorial1 : example_messageout.comp example_messageprint.comp
util: wsbroadcaster
cat: cossb wsbroadcaster edison_uart.comp example_cat_monitoring.comp cat_protocol.comp wsclient.comp compcontroller.comp
cat2: cossb wsbroadcaster example_cat_monitoring.comp cat_protocol.comp wsclient.comp sqlitedb.comp compcontroller.comp
websocket: wsbroadcaster wsclient.comp example_websocket_client.comp

# Clean
clean: 
	$(RM) $(OUTDIR)*.o $(OUTDIR)cossb $(OUTDIR)cossb_test $(OUTDIR)*.so $(OUTDIR)*.comp
