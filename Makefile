BIN_NAME := main
CXX ?= g++

FILE_NAME = main.cc

COMPILE_FLAGS = -Wall -std=c++11

all:
	$(CXX) -o $(BIN_NAME) $(FILE_NAME) $(COMPILE_FLAGS)

.PHONY : clean
clean:
	# Clean up
	-rm BIN_NAME
