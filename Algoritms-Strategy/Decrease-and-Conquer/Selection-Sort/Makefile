CXX = g++

SRC = Selection-sort.cpp
OUT = build/Selection-sort

all: run

build:
	mkdir -p build

$(OUT): $(SRC) | build
	$(CXX) $(SRC) -o $(OUT)

run: $(OUT)
	./$(OUT)
