CXX = g++

SRC = Sorting.cpp
OUT = build/Sorting

all: run

build:
	mkdir -p build

$(OUT): $(SRC) | build
	$(CXX) $(SRC) -o $(OUT)

run: $(OUT)
	./$(OUT)
