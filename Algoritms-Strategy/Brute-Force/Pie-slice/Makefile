CXX = g++

SRC = Pie-slice.cpp
OUT = build/Pie-slice

all: run

build:
	mkdir -p build

$(OUT): $(SRC) | build
	$(CXX) $(SRC) -o $(OUT)

run: $(OUT)
	./$(OUT)
