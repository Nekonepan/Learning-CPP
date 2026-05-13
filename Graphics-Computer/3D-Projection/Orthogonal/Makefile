CXX = g++
CXXFLAGS = -Wall
LIBS = -lGL -lGLU -lglut

SRC = Orthogonal.cpp
OUT = build/Orthogonal

all: run

build:
	mkdir -p build

$(OUT): $(SRC) | build
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS) $(LIBS)

run: $(OUT)
	./$(OUT)
