CXX = g++

SRC = Binary-search.cpp
OUT = build/Binary-search

all: run

build:
	mkdir -p build

$(OUT): $(SRC) | build
	$(CXX) $(SRC) -o $(OUT)

run: $(OUT)
	./$(OUT)
