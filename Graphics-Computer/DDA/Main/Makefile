CXX ?= g++
CXXFLAGS ?= -Wall
PKG_CONFIG ?= pkg-config
UNAME_S := $(shell uname -s 2>/dev/null)

ifeq ($(origin LDLIBS), undefined)
  ifeq ($(UNAME_S), Darwin)
    PKG_CFLAGS := $(shell $(PKG_CONFIG) --cflags glut glu 2>/dev/null)
    PKG_LDLIBS := $(shell $(PKG_CONFIG) --libs glut glu 2>/dev/null)
    CXXFLAGS += $(PKG_CFLAGS)
    ifneq ($(strip $(PKG_LDLIBS)),)
      LDLIBS := $(PKG_LDLIBS)
    else
      LDLIBS := -framework OpenGL -framework GLUT
    endif
  else ifneq (,$(findstring MINGW,$(UNAME_S)))
    LDLIBS := -lfreeglut -lopengl32 -lglu32
  else ifneq (,$(findstring MSYS,$(UNAME_S)))
    LDLIBS := -lfreeglut -lopengl32 -lglu32
  else ifneq (,$(findstring CYGWIN,$(UNAME_S)))
    LDLIBS := -lglut -lGLU -lGL
  else
    PKG_CFLAGS := $(shell $(PKG_CONFIG) --cflags glut glu 2>/dev/null)
    PKG_LDLIBS := $(shell $(PKG_CONFIG) --libs glut glu 2>/dev/null)
    CXXFLAGS += $(PKG_CFLAGS)
    ifneq ($(strip $(PKG_LDLIBS)),)
      LDLIBS := $(PKG_LDLIBS)
    else
      LDLIBS := -lGL -lGLU -lglut
    endif
  endif
endif

THIS_DIR := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
BUILD_DIR := $(THIS_DIR)build
SRC := $(THIS_DIR)main.cpp
OUT := $(BUILD_DIR)/main

.PHONY: all build run clean
all: run

build: $(OUT)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OUT): $(SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDLIBS)

run: $(OUT)
	$(OUT)

clean:
	rm -rf $(BUILD_DIR)
