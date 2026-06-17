# Greedy Algorithm (Algoritma & Strategi)

[![C++](https://img.shields.io/badge/C%2B%2B-17-blue)](https://isocpp.org/)

---

## Description

This project demonstrates **Greedy algorithm strategies** — solving optimisation problems by making the locally optimal choice at each step. It includes implementations of:

- **Coin Change (Greedy)**: Finding the minimum number of coins to make a given amount using the greedy approach (largest denomination first).
- **Post**: Extended greedy problem solving exercise.
- **Post-Improvement**: Improved/optimised version of the greedy exercise.

All programs are console-based and run in the terminal.

---

## Features

- Classic greedy algorithm implementation for the coin change problem.
- Multiple solution variants showing iterative improvement.
- Clear, readable C++ code with comments.
- Simple Makefiles for easy build & run.

---

## Directory Structure

```
Greedy-algorithm/
├── Greedy-Algorithm/
│   ├── Greedy-algorithm.cpp
│   └── Makefile
└── Post/
    ├── Post/
    │   ├── post.cpp
    │   └── Makefile
    └── Post-Improvement/
        ├── post-improvement.cpp
        └── Makefile
```

---

## Build & Run

Each subdirectory is self-contained. From the subdirectory:

```bash
make run
```

This creates `build/` dir, compiles the `.cpp`, and runs the executable.

**Example for Greedy Algorithm:**

```bash
cd Learning-CPP/Algoritms-Strategy/Greedy-algorithm/Greedy-Algorithm
make run
```

### Manual Compilation (if no Makefile)

```bash
g++ *.cpp -o program -std=c++17
./program
```

---

## Requirements / Dependencies

- g++ compiler (C++17 or later)

### Arch Linux / Manjaro

```bash
sudo pacman -Syu base-devel
```

### Ubuntu/Debian (Linux)

```bash
sudo apt update
sudo apt install g++
```

**Verify:**

```bash
g++ --version
```

---

## License

See [LICENSE](../LICENSE) in parent repository.
