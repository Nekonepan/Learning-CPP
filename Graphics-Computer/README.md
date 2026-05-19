# Graphics-Computer

This folder contains various **Computer Graphics** projects and experiments implemented in **C++** using **OpenGL** and **GLUT** (FreeGLUT). These projects were created as part of learning computer graphics concepts such as line drawing algorithms, transformations, projections, and curve interpolation.

---

## 🛠️ Requirements

### Dependencies

- **C++ Compiler** (g++ recommended)
- **OpenGL**
- **GLU**
- **FreeGLUT** (for windowing and input handling)

### Installation by OS

#### - Linux (Ubuntu/Debian)
```
sudo apt update
sudo apt install g++ freeglut3-dev libgl1-mesa-dev libglu1-mesa-dev
```

#### - Arch Linux / Manjaro
```
sudo pacman -Syu base-devel freeglut mesa glu
```

#### - Windows (MSYS2 / MinGW)
```
# In MSYS2 terminal:
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-freeglut mingw-w64-x86_64-mesa
```

#### - macOS
```
brew install freeglut
```

---

## ▶️ How to Build and Run

Most projects include a Makefile. The recommended way is:

```
cd Graphics-Computer/<project-folder>/<sub-folder>
make run
```

This will:

1. Create a `build/` directory
2. Compile the program
3. Run the executable

### Manual Compilation (if no Makefile)
```
g++ main.cpp -o program -lGL -lGLU -lglut -std=c++17
./program
```

---

## 🎮 Controls (Common)

Many programs support:

- Arrow keys (`← → ↑ ↓`) for rotation / camera movement
- Check individual project `README.md` (if available) for specific controls

---

## 📝 Notes

- Projects are written in C++17 standard.
- These are learning/experimental implementations - code may not be optimized for production.
- Some folders contain Post/ which might include screenshots or additional notes.

---

## 🤝 Contributing

Feel free to improve the code, add comments, fix bugs, or add new graphics algorithms!

---

## 📜 License

This project is part of [Learning-CPP](https://github.com/Nekonepan/Learning-CPP) repository. See the root LICENSE file.
