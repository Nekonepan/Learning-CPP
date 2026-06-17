# Surface Representation Techniques (Grafkom)

[![OpenGL](https://img.shields.io/badge/OpenGL-GLUT-brightgreen)](https://www.opengl.org/)
[![C++](https://img.shields.io/badge/C%2B%2B-17-blue)](https://isocpp.org/)

---

## Description

This project demonstrates **surface representation techniques** in computer graphics using OpenGL and GLUT. It includes implementations of:

- **NURBS Surfaces**: Non-Uniform Rational B-Spline surface rendering using GLU NURBS.
- **Control Point Visualisation**: Toggle display of control points over the surface.
- **Lighting & Materials**: Diffuse/specular material properties with OpenGL lighting.

Each demo renders a NURBS surface with a 4×4 control point grid in a 480×480 window with interactive rotation.

---

## Features

- Interactive rotation of the surface using arrow keys.
- Camera movement with Page Up / Page Down.
- Toggle control point display with F1.
- NURBS surface rendering with lighting and materials.
- Built with standard C++17, OpenGL, GLUT.
- Simple Makefiles for easy build & run.

---

## Directory Structure

```
Surface-Representation-Techniques/
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
- **F1**: Toggle control points visibility

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
