BUILD_DIR = ./build
CC = g++
COMFLAGS = -std=c++11

# generate binary file
$(BUILD_DIR)/Limittest.out : ./Limittest.cpp
	$(CC) $(COMFLAGS) $< -o $@

$(BUILD_DIR)/Stringtest.out : ./Stringtest.cpp
	$(CC) $(COMFLAGS) $< -o $@


# make command
clean :
	cd $(BUILD_DIR) && rm -rf ./*.out 

Limittest : $(BUILD_DIR)/Limittest.out
	cd $(BUILD_DIR) && ./Limittest.out
Stringtest : $(BUILD_DIR)/Stringtest.out
	cd $(BUILD_DIR) && ./Stringtest.out
