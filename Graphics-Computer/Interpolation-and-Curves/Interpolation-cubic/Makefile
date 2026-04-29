CXX = g++
CXXFLAGS = -Wall
LIBS = -lGL -lGLU -lglut

SRC = interpolation-cubic.cpp
OUT = build/interpolation-cubic

all: run

build:
	mkdir -p build

$(OUT): $(SRC) | build
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS) $(LIBS)

run: $(OUT)
	./$(OUT)
