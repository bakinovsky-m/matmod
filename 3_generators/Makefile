CC = g++
CXXFLAGS += -std=c++11
DEBUG = -g -Wall -Wextra -Wpedantic -O0

SRC_DIR = ./src
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)

all: compile
	./build/main

compile:
	mkdir -p build
	g++ $(CXXFLAGS) $(SRC_FILES) -o ./build/main $(DEBUG)

clean:
	rm -rf build

.PHONY: all compile clean