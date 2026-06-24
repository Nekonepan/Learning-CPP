# 3D Object Modeling Technique (Grafkom)

[![OpenGL](https://img.shields.io/badge/OpenGL-GLUT-brightgreen)](https://www.opengl.org/)
[![C++](https://img.shields.io/badge/C%2B%2B-17-blue)](https://isocpp.org/)

---

## Description

This project demonstrates **3D object modeling techniques** in computer graphics using OpenGL and GLUT. It implements:

- **Metaball Rendering**: Generating smooth, organic 3D surfaces using the Marching Cubes algorithm on an implicit scalar field defined by metaballs.
- **Marching Cubes Algorithm**: Extracting iso-surfaces from a 3D scalar field using a cube grid.
- **Dynamic Animation**: Animated metaballs that move along sinusoidal paths over time.
- **Lighting & Shading**: Smooth shading with ambient, diffuse, and specular lighting on the metaball surface.

The demo renders animated metaball surfaces in a 480×480 window with interactive rotation.

---

## Features

- Real-time metaball surface generation using Marching Cubes.
- Animated metaball positions with smooth motion.
- Interactive rotation of the scene using arrow keys.
- Camera movement with Page Up / Page Down.
- Switchable diffuse colour presets.
- Built with standard C++17, OpenGL, GLUT.
- Simple Makefile for easy build & run.

---

## Directory Structure

```
3D-Object-Modeling-Technique/
├── 3D-Object-Modeling-Technique/
│   ├── main.cpp              # Main program with metaball animation
│   ├── COLOR.h / COLOR.cpp   # RGBA colour class
│   ├── CUBE_GRID.h / .cpp    # Cube grid & Marching Cubes surface extraction
│   ├── METABALL.h             # Metaball data structure
│   ├── VECTOR3D.h / .cpp     # 3D vector math class
│   ├── TIMER.h / TIMER.cpp   # Cross-platform timer (std::chrono)
│   └── Makefile
└── Post/
    ├── main.cpp              # Post exercise version
    ├── COLOR.h / COLOR.cpp
    ├── CUBE_GRID.h / .cpp
    ├── METABALL.h
    ├── VECTOR3D.h / .cpp
    ├── TIMER.h / TIMER.cpp
    └── Makefile
```

---

## Build & Run

Each subdirectory is self-contained. From the subdirectory:

```bash
make run
```

This creates `build/` dir, compiles all `.cpp` files, and runs the executable.

**Example:**

```bash
cd Learning-CPP/Graphics-Computer/3D-Object-Modeling-Technique/3D-Object-Modeling-Technique
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
