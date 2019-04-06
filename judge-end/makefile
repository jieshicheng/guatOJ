BUILD_DIR = ./build
CC = g++
LD = ld
LIB = -I ./ -I ./tp/cinatra/ -I ./tp/jsoncpp/
DLL = -luuid -lboost_system -lboost_filesystem -lpthread -lstdc++fs -lglog
COMFLAGS = -c $(LIB) $(DLL) -std=c++17
LDFLAGS = $(DLL)
OBJS =  $(BUILD_DIR)/oj_lib.o $(BUILD_DIR)/pipe_manage.o \
		$(BUILD_DIR)/compare.o $(BUILD_DIR)/compiler.o \
		$(BUILD_DIR)/jsoncpp.o $(BUILD_DIR)/resource_limit.o $(BUILD_DIR)/question.o \
		$(BUILD_DIR)/main.o 

## compiler

$(BUILD_DIR)/main.o : ./src/main.cc ./src/compiler.h ./src/compare.h ./src/pipe_manage.h \
						./lib/oj_lib.h ./src/question.h ./src/resource_limit.h
	$(CC) $(COMFLAGS) $< -o $@

$(BUILD_DIR)/compare.o : ./src/compare.cc ./lib/oj_lib.h ./src/pipe_manage.h ./src/resource_limit.h \
						./src/question.h
	$(CC) $(COMFLAGS) $< -o $@

$(BUILD_DIR)/compiler.o : ./src/compiler.cc ./lib/oj_lib.h ./src/pipe_manage.h ./src/resource_limit.h
	$(CC) $(COMFLAGS) $< -o $@

$(BUILD_DIR)/pipe_manage.o : ./src/pipe_manage.cc ./lib/oj_lib.h
	$(CC) $(COMFLAGS) $< -o $@

$(BUILD_DIR)/oj_lib.o : ./lib/oj_lib.cc
	$(CC) $(COMFLAGS) $< -o $@

$(BUILD_DIR)/jsoncpp.o : ./tp/jsoncpp/jsoncpp.cpp
	$(CC) $(COMFLAGS) $< -o $@

$(BUILD_DIR)/resource_limit.o : ./src/resource_limit.cc ./lib/oj_lib.h
	$(CC) $(COMFLAGS) $< -o $@

$(BUILD_DIR)/question.o : ./src/question.cc ./lib/oj_lib.h
	$(CC) $(COMFLAGS) $< -o $@
## ld

$(BUILD_DIR)/guatoj : $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

## command

clean :
	cd $(BUILD_DIR) && rm -rf ./*

build : $(BUILD_DIR)/guatoj
