# Branch and Bound Algorithm

[![OpenGL](https://img.shields.io/badge/OpenGL-GLUT-brightgreen)](https://www.opengl.org/)
[![C++](https://img.shields.io/badge/C%2B%2B-17-blue)](https://isocpp.org/)

---

## Description

This project demonstrates the **Branch and Bound** algorithm applied to the **Travelling Salesman Problem (TSP)** using OpenGL and GLUT for visualization. The program builds a weighted undirected graph, computes the optimal tour using cost matrix reduction and recursive branching with pruning, and renders the result in an 800×480 window.

Based on the lecture: *Praktikum 8 - Branch and Bound* (Strategi Algoritma).

---

## Features

- Visual graph rendering with nodes, edges, and distance labels.
- Branch and Bound algorithm with cost matrix reduction for TSP.
- Optimal tour path highlighted in the visualization.
- Built with standard C++17, OpenGL, GLUT.
- Simple Makefiles for easy build & run.

---

## Directory Structure

```
Branch-and-Bound-Algorithm/
├── Branch-and-Bound/
│   ├── main.cpp        # Main program (TSP with 4 nodes)
│   ├── graph.h          # Graph data structure
│   ├── draws.h          # OpenGL drawing utilities
│   ├── glut.h           # GLUT header (bundled)
│   └── Makefile
└── Post/
    ├── main.cpp          # Post exercise version (TSP with 5 nodes)
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
cd Learning-CPP/Algoritms-Strategy/Branch-and-Bound-Algorithm/Branch-and-Bound
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
