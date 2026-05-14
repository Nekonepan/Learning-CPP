CXX = g++

SRC = Post.cpp
OUT = build/Post

all: run

build:
	mkdir -p build

$(OUT): $(SRC) | build
	$(CXX) $(SRC) -o $(OUT)

run: $(OUT)
	./$(OUT)
