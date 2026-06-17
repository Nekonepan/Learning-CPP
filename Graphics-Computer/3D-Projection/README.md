# 3D Projection (Grafkom)

[![OpenGL](https://img.shields.io/badge/OpenGL-GLUT-brightgreen)](https://www.opengl.org/)
[![C++](https://img.shields.io/badge/C%2B%2B-17-blue)](https://isocpp.org/)

---

## Description

This project demonstrates **3D projection techniques** in computer graphics using OpenGL and GLUT. It includes implementations of:

- **Orthogonal Projection**: Parallel projection where object size is independent of distance from camera.
- **Perspective Projection**: Realistic projection with foreshortening where distant objects appear smaller.

Each demo renders 3D objects (cubes, spheres, cones, teapots, etc.) in a 480×480 window with interactive rotation.

---

## Features

- Interactive rotation of objects using arrow keys.
- Camera movement with Page Up / Page Down.
- Side-by-side comparison of orthogonal vs perspective projection.
- Multiple 3D primitives rendered with distinct colours.
- Built with standard C++17, OpenGL, GLUT.
- Simple Makefiles for easy build & run.

---

## Directory Structure

```
3D-Projection/
├── Orthogonal/
│   ├── Orthogonal.cpp
│   └── Makefile
├── Perspective/
│   ├── Perspective.cpp
│   └── Makefile
└── Post/
    ├── Post.cpp
    └── Makefile
```

---

## Build & Run

Each subdirectory is self-contained. From the subdirectory:

```bash
make run
```

This creates `build/` dir, compiles the `.cpp`, and runs the executable.

**Example for Orthogonal:**

```bash
cd Learning-CPP/Graphics-Computer/3D-Projection/Orthogonal
make run
```

### Manual Compilation (if no Makefile)

```bash
g++ *.cpp -o program -lGL -lGLU -lglut
./program
```

---

## Controls

- **← →**: Rotate horizontally
- **↑ ↓**: Rotate vertically
- **Page Up**: Move camera forward
- **Page Down**: Move camera backward

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
