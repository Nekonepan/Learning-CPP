# Interpolation and Curves (Grafkom)

[![OpenGL](https://img.shields.io/badge/OpenGL-GLUT-brightgreen)](https://www.opengl.org/)
[![C++](https://img.shields.io/badge/C%2B%2B-17-blue)](https://isocpp.org/)

---

## Description

This project demonstrates **curve interpolation algorithms** in computer graphics using OpenGL and GLUT. It includes implementations of:

- **Linear Interpolation**: Straight line between two control points.
- **Cubic Interpolation**: Smooth cubic spline using four control points.
- **Cosine Interpolation**: Smooth easing curve using cosine function.

Each demo renders a green curve in a 480x480 window with rotatable view.

---

## Features

- Interactive rotation using arrow keys.
- Rendered curves with highlighted sample points.
- Built with standard C++17, OpenGL, GLUT.
- Simple Makefiles for easy build & run.

---

## Directory Structure

```
Interpolation-and-Curves/
├── Interpolation-linear/
│   ├── interpolation-linear.cpp
│   └── Makefile
├── Interpolation-cubic/
│   ├── interpolation-cubic.cpp
│   └── Makefile
├── Interpolation-cosine/
│   ├── interpolation-cosine.cpp
│   └── Makefile
└── Post/
    ├── post.cpp
    └── Makefile
```

---

## Build & Run

Each subdirectory is self-contained. From the subdirectory:

```bash
make run
```

This creates `build/` dir, compiles the `.cpp`, and runs the executable.

**Example for Linear:**

```bash
cd Learning-CPP/Graphics-Computer/Interpolation-and-Curves/Interpolation-linear
make run
```

---

## Controls

- **← →**: Rotate horizontally
- **↑ ↓**: Rotate vertically

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
