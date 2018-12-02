BUILD_DIR = ./build
CC = g++
LD = ld
LIB = -I ./lib -I ../tp/cinatra -I ../tp/jsoncpp
DLL = -luuid -lboost_system -lboost_filesystem -lpthread -lstdc++fs
COMFLAGS = -c $(LIB) $(DLL) -std=c++17
LDFLAGS = $(DLL)
OBJS = $(BUILD_DIR)/OJlib.o $(BUILD_DIR)/single_pipe.o $(BUILD_DIR)/compare.o $(BUILD_DIR)/compiler.o $(BUILD_DIR)/main.o 

## compiler

$(BUILD_DIR)/main.o : ./main.cpp ./compiler.h ./compare.h ./single_pipe.h ./lib/OJlib.h
	$(CC) $(COMFLAGS) $< -o $@

$(BUILD_DIR)/compare.o : ./compare.cpp ./lib/OJlib.h ./single_pipe.h
	$(CC) $(COMFLAGS) $< -o $@

$(BUILD_DIR)/compiler.o : ./compiler.cpp ./lib/OJlib.h ./single_pipe.h
	$(CC) $(COMFLAGS) $< -o $@

$(BUILD_DIR)/single_pipe.o : ./single_pipe.cpp ./lib/OJlib.h
	$(CC) $(COMFLAGS) $< -o $@

$(BUILD_DIR)/OJlib.o : ./lib/OJlib.cpp
	$(CC) $(COMFLAGS) $< -o $@
## ld

$(BUILD_DIR)/guatoj : $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

## command

clean :
	cd $(BUILD_DIR) && rm -rf ./*

build : $(BUILD_DIR)/guatoj
