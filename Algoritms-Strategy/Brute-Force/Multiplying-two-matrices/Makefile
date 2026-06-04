CXX ?= g++
CXXFLAGS ?= -Wall -std=c++17

THIS_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BUILD_DIR := $(THIS_DIR)build
SRC := $(THIS_DIR)main.cpp
OUT := $(BUILD_DIR)/Multiplying-two-matrices

.PHONY: all build run clean help
all: run

build: $(OUT)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OUT): $(SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run: $(OUT)
	$(OUT)

clean:
	rm -rf $(BUILD_DIR)

help:
	@echo "Usage: make [target]"
	@echo ""
	@echo "Targets:"
	@echo "  all     Build and run the program (default)"
	@echo "  build   Compile the source into build/ directory"
	@echo "  run     Build (if needed) and execute the program"
	@echo "  clean   Remove the build/ directory and all compiled files"
	@echo "  help    Show this help message"
	@echo ""
	@echo "Source:  $(notdir $(SRC))"
	@echo "Output:  $(notdir $(OUT))"
