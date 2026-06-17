# DDA (Grafkom)

[![OpenGL](https://img.shields.io/badge/OpenGL-GLUT-brightgreen)](https://www.opengl.org/)
[![C++](https://img.shields.io/badge/C%2B%2B-17-blue)](https://isocpp.org/)

---

## Description

This project demonstrates the **Digital Differential Analyzer (DDA) line-drawing algorithm** in computer graphics using OpenGL and GLUT. It includes implementations of:

- **DDA Line Drawing**: Rasterising a straight line between two endpoints using incremental calculation.
- **Multiple Line Rendering**: Drawing several lines with different slopes and orientations.

Each demo renders coloured lines in a 480×480 window.

---

## Features

- DDA algorithm implementation for line rasterisation.
- Multiple line segments drawn with distinct colours.
- Built with standard C++17, OpenGL, GLUT.
- Simple Makefiles for easy build & run.

---

## Directory Structure

```
DDA/
├── Main/
│   ├── main.cpp
│   └── Makefile
└── Post/
    ├── main2.cpp
    └── Makefile
```

---

## Build & Run

Each subdirectory is self-contained. From the subdirectory:

```bash
make run
```

This creates `build/` dir, compiles the `.cpp`, and runs the executable.

**Example for Main:**

```bash
cd Learning-CPP/Graphics-Computer/DDA/Main
make run
```

---

## Controls

No interactive controls — the lines are rendered statically.

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

See [LICENSE](../LICENSE) in parent repository.
