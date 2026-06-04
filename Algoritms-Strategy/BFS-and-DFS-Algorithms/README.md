# BFS and DFS Algorithms

[![OpenGL](https://img.shields.io/badge/OpenGL-GLUT-brightgreen)](https://www.opengl.org/)
[![C++](https://img.shields.io/badge/C%2B%2B-17-blue)](https://isocpp.org/)

---

## Description

This project demonstrates **Breadth-First Search (BFS)** and **Depth-First Search (DFS)** graph traversal algorithms with a visual representation using OpenGL and GLUT. The program builds a directed graph, applies the selected traversal algorithm, and renders the graph with the traversal path highlighted in an 800×480 window.

Based on the lecture slides: *Strategi Algoritma - BFS dan DFS* (page 14).

---

## Features

- Visual graph rendering with nodes and directed edges.
- BFS and DFS traversal with path highlighting.
- Traversal order displayed on each node.
- Built with standard C++17, OpenGL, GLUT.
- Simple Makefiles for easy build & run.

---

## Directory Structure

```
BFS-and-DFS-Algorithms/
├── BFS-and-DFS/
│   ├── main.cpp        # Main program (BFS/DFS traversal)
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
cd Learning-CPP/Algoritms-Strategy/BFS-and-DFS-Algorithms/BFS-and-DFS
make run
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
