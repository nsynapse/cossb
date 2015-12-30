# Makefile for all component project

# compiler flags
#	-g	--Enable debugging
#	-Wall	--Turn on all warnings
#	-D_USE_FIXED_PROTOTYPES_
#	--Force the compiler to use the correct headers
#	-ansi	--Don't use GNU ext; do use ansi standard.

CC = gcc
CXX = g++
CXXFLAGS = -O3 -fPIC -Wall -std=c++11 -D__cplusplus=201103L
CCFLAGS = $(CXXFLAGS)
LDFLAGS = -Wl,--export-dynamic
LDLIBS = -lpopt -lboost_system -lboost_thread -lboost_filesystem -ltinyxml2 -ldl
LDLIBS_TEST = -lpopt -lboost_system -lboost_thread -ltinyxml2 -ldl -lgtest -lpthread
INCLUDE = -I./include -I/usr/include -I/usr/local/include
RM	= rm -rf

OUTDIR		= ./bin/
INCLUDE_FILES = ./include/
EXAMPLE_FILES = ./examples/
LIB_FILES = ./lib/
UTIL_FILES = ./utils/
TEST_FILES = ./test/
SOURCE_FILES = ./src/
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
		$(OUTDIR)xmlprofile.o \
		$(OUTDIR)server.o \
		$(OUTDIR)client.o \
		$(OUTDIR)log.o
		$(CXX) $(LDFLAGS) -o $(OUTDIR)$@ $^ $(LDLIBS)
		
cossb_test:	$(OUTDIR)cossb_test.o \
		$(OUTDIR)sysmanager_test.o \
		$(OUTDIR)instance.o	\
		$(OUTDIR)manifest.o \
		$(OUTDIR)sysmanager.o \
		$(OUTDIR)compmanager.o \
		$(OUTDIR)driver.o \
		$(OUTDIR)xmlprofile.o \
		$(OUTDIR)server.o \
		$(OUTDIR)client.o \
		$(OUTDIR)log.o
		$(CXX) $(LDFLAGS) -o $(OUTDIR)$@ $^ $(LDLIBS_TEST)
		
#examples
helloworld.comp: $(OUTDIR)helloworld.o 
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)helloworld.o: $(EXAMPLE_FILES)01_Helloworld/helloworld.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
tcpserver.comp: $(OUTDIR)tcpserver.o 
	$(CXX) $(LDFLAGS) -shared -o $(OUTDIR)$@ $^ $(LDLIBS)
$(OUTDIR)tcpserver.o: $(EXAMPLE_FILES)02_tcpserver/tcpserver.cpp
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
	
$(OUTDIR)xmlprofile.o: $(INCLUDE_FILES)base/xmlprofile.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)log.o: $(INCLUDE_FILES)base/log.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)server.o: $(INCLUDE_FILES)net/server.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
$(OUTDIR)client.o: $(INCLUDE_FILES)net/client.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
#for test code	
$(OUTDIR)cossb_test.o: $(TEST_FILES)cossb_test.cpp 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@
	
$(OUTDIR)sysmanager_test.o: $(TEST_FILES)sysmanager_test.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^ -o $@


# make cossb
all: cossb helloworld.comp tcpserver.comp

test: cossb_test

example: helloworld.comp tcpserver.comp

# Clean
clean: 
	$(RM) $(OUTDIR)*.o $(OUTDIR)cossb $(OUTDIR)cossb_test $(OUTDIR)*.so $(OUTDIR)*.comp
