CXX = g++
CXXFLAGS = -Wall
LIBS = -lGL -lGLU -lglut

SRC = main2.cpp
OUT = build/main2

all: run

build:
	mkdir -p build

$(OUT): $(SRC) | build
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS) $(LIBS)

run: $(OUT)
	./$(OUT)
