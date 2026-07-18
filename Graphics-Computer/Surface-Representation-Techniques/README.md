# Surface Representation Techniques (Grafkom)

[![OpenGL](https://img.shields.io/badge/OpenGL-GLUT-brightgreen)](https://www.opengl.org/)
[![C++](https://img.shields.io/badge/C%2B%2B-17-blue)](https://isocpp.org/)

---

## Description

This project demonstrates **surface representation techniques** in computer graphics using OpenGL and GLUT. It includes implementations of:

- **NURBS Surfaces**: Non-Uniform Rational B-Spline surface rendering using GLU NURBS.
- **Subdivision Surfaces**: 3D hand model generated procedurally and refined dynamically via Catmull-Clark subdivision algorithm.
- **Control Point & Wireframe Visualisation**: Toggle display of control points / subdivision meshes.
- **Lighting & Materials**: Diffuse/specular material properties with OpenGL lighting.

---

## Features

- Interactive rotation of the surface using arrow keys.
- Camera movement with Page Up / Page Down.
- Toggle control point display (for NURBS) or wireframe overlay (for Subdivision).
- NURBS surface and Subdivision mesh rendering with lightings.
- Built with standard C++17, OpenGL, GLUT.
- Simple Makefiles for easy build & run.

---

## Directory Structure

```
Surface-Representation-Techniques/
├── 3D-Hand-Model/
│   ├── main.cpp              # 3D hand model using Catmull-Clark subdivision
│   ├── COLOR.h / COLOR.cpp   # RGBA color helper class
│   ├── VECTOR3D.h / .cpp     # 3D vector helper class
│   ├── TIMER.h / TIMER.cpp   # Timer helper class
│   └── Makefile
├── Surface-Representation-Techniques-V1/
│   ├── main.cpp
│   └── Makefile
├── Surface-Representation-Techniques-V2/
│   ├── main.cpp
│   └── Makefile
└── Post/
    ├── main.cpp
    └── Makefile
```

---

## Build & Run

Each subdirectory is self-contained. From the subdirectory:

```bash
make run
```

This creates `build/` dir, compiles the `.cpp`, and runs the executable.

**Example for V1:**

```bash
cd Learning-CPP/Graphics-Computer/Surface-Representation-Techniques/Surface-Representation-Techniques-V1
make run
```

**Example for 3D Hand Model (Subdivision):**

```bash
cd Learning-CPP/Graphics-Computer/Surface-Representation-Techniques/3D-Hand-Model
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
- **Page Up**: Zoom in / Move camera forward
- **Page Down**: Zoom out / Move camera backward
- **F1**: Toggle control points visibility (NURBS only)
- **+ / -**: Increase/Decrease subdivision level (Subdivision only)
- **S / s**: Toggle Shading (Flat Faceted / Smooth Organic - Subdivision only)
- **W / w**: Toggle Wireframe Overlay (Subdivision only)
- **1 - 4**: Switch colors (Subdivision only)
- **Space**: Toggle auto-rotation (Subdivision only)
- **R / r**: Reset camera (Subdivision only)

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
