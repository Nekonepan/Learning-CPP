CXX = g++
CXXFLAGS = -Wall
LIBS = -lGL -lGLU -lglut

SRC = Post.cpp
OUT = build/Post

all: run

build:
	mkdir -p build

$(OUT): $(SRC) | build
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS) $(LIBS)

run: $(OUT)
	./$(OUT)
