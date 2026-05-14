CXX = g++

SRC = Insertion-sort.cpp
OUT = build/Insertion-sort

all: run

build:
	mkdir -p build

$(OUT): $(SRC) | build
	$(CXX) $(SRC) -o $(OUT)

run: $(OUT)
	./$(OUT)
