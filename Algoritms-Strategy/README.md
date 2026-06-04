# Algoritms-Strategy

This folder contains various **Algorithm Strategy** implementations in **C++**. These projects were created as part of learning fundamental algorithm design techniques such as Brute Force, Decrease and Conquer, Divide and Conquer, and Greedy algorithms.

---

## 🛠️ Requirements

### Dependencies

- **C++ Compiler** (g++ recommended)

### Installation by OS

#### - Linux (Ubuntu/Debian)
```
sudo apt update
sudo apt install g++ make
```

#### - Arch Linux / Manjaro
```
sudo pacman -Syu base-devel
```

#### - Windows (MSYS2 / MinGW)
```
# In MSYS2 terminal:
pacman -S mingw-w64-x86_64-gcc make
```

#### - macOS
```
xcode-select --install
```

---

## ▶️ How to Build and Run

Every project includes a Makefile. The recommended way is:

```
cd Algoritms-Strategy/<category>/<project-folder>
make run
```

This will:

1. Create a `build/` directory
2. Compile the program
3. Run the executable

To see all available Makefile targets and project info, run:

```
make help
```

Example output:
```
Usage: make [target]

Targets:
  all     Build and run the program (default)
  build   Compile the source into build/ directory
  run     Build (if needed) and execute the program
  clean   Remove the build/ directory and all compiled files
  help    Show this help message

Source:  main.cpp
Output:  Checking-prime-numbers
```

### Manual Compilation (if no Makefile)
```
g++ main.cpp -o program -std=c++17
./program
```

---

## 📝 Notes

- Projects are written in C++17 standard.
- These are learning/experimental implementations - code may not be optimized for production.
- Most programs are interactive and require user input via the terminal.
- Some folders contain `Post/` which include post-exercise or improved versions.

---

## 🤝 Contributing

Feel free to improve the code, add comments, fix bugs, or add new algorithm implementations!

---

## 📜 License

This project is part of [Learning-CPP](https://github.com/Nekonepan/Learning-CPP) repository. See the root LICENSE file.
