CXX = g++
CXXFLAGS = -Wall
LIBS = -lGL -lGLU -lglut

SRC = main.cpp
OUT = build/main

all: run

build:
	mkdir -p build

$(OUT): $(SRC) | build
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS) $(LIBS)

run: $(OUT)
	./$(OUT)
