# Backtracking Algorithm

[![OpenGL](https://img.shields.io/badge/OpenGL-GLUT-brightgreen)](https://www.opengl.org/)
[![C++](https://img.shields.io/badge/C%2B%2B-17-blue)](https://isocpp.org/)

---

## Description

This project demonstrates the **Backtracking** algorithm applied to the **Graph Coloring** problem using OpenGL and GLUT for visualization. The program builds an undirected graph, attempts to assign colors to each node such that no two adjacent nodes share the same color, and renders the result in an 800×480 window.

Based on the lecture: *Praktikum 7 - Backtracking Graph Coloring* (Strategi Algoritma).

---

## Features

- Visual graph rendering with nodes and edges.
- Graph coloring using backtracking algorithm.
- Colored nodes displayed when a valid coloring is found.
- Built with standard C++17, OpenGL, GLUT.
- Simple Makefiles for easy build & run.

---

## Directory Structure

```
Backtracking-Algorithm/
├── Backtracking-Algorithm/
│   ├── main.cpp        # Main program (Graph Coloring)
│   ├── graph.h          # Graph data structure
│   ├── draws.h          # OpenGL drawing utilities
│   ├── glut.h           # GLUT header (bundled)
│   └── Makefile
└── Post/
    ├── main.cpp          # Post exercise version
    ├── graph.h
    ├── draws.h
    ├── glut.h
    └── Makefile
```

---

## Build & Run

Each subdirectory is self-contained. From the subdirectory:

```bash
make run
```

This creates `build/` dir, compiles the `.cpp`, and runs the executable.

**Example:**

```bash
cd Learning-CPP/Algoritms-Strategy/Backtracking-Algorithm/Backtracking-Algorithm
make run
```

### Manual Compilation (if no Makefile)

```bash
g++ *.cpp -o program -lGL -lGLU -lglut
./program
```

To see all available Makefile targets:

```bash
make help
```

---

## Requirements / Dependencies

### Arch Linux / Manjaro

```bash
sudo pacman -Syu base-devel freeglut mesa glu
```

### Ubuntu/Debian (Linux)

```bash
sudo apt update
sudo apt install g++ freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev
```

### Windows (with MinGW/MSYS2)

```bash
# Install MSYS2, then:
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-freeglut mingw-w64-x86_64-mesa
```

### macOS (with Homebrew)

```bash
brew install freeglut
# g++ usually pre-installed
```

**Verify:**

```bash
g++ --version
pkg-config --modversion glut
```

---

## Dependencies (Linker flags)

- g++ compiler
- OpenGL, GLU, GLUT: `-lGL -lGLU -lglut`

---

## License

See [LICENSE](../../LICENSE) in parent repository.
