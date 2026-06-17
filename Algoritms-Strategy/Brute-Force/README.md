# Brute Force (Algoritma & Strategi)

[![C++](https://img.shields.io/badge/C%2B%2B-17-blue)](https://isocpp.org/)

---

## Description

This project demonstrates **Brute Force algorithm strategies** — solving problems by exhaustively trying all possibilities. It includes implementations of:

- **Checking Prime Numbers**: Tests primality by trial division from 2 to n−1.
- **Exponentiation**: Computes a^n by repeated multiplication.
- **Multiplying Two Matrices**: Standard O(n³) matrix multiplication.
- **Search for the Smallest Element**: Linear scan to find the minimum value in an array.
- **Personal**: Custom brute-force problem solving exercise.

All programs are console-based and run in the terminal.

---

## Features

- Classic brute-force implementations for fundamental problems.
- Clear, readable C++ code with comments.
- Simple Makefiles for easy build & run.

---

## Directory Structure

```
Brute-Force/
├── Checking-prime-numbers/
│   ├── main.cpp
│   └── Makefile
├── Exponentiation/
│   ├── main.cpp
│   └── Makefile
├── Multiplying-two-matrices/
│   ├── main.cpp
│   └── Makefile
├── Search-for-the-smallest-element/
│   ├── main.cpp
│   └── Makefile
└── Personal/
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

**Example for Checking Prime Numbers:**

```bash
cd Learning-CPP/Algoritms-Strategy/Brute-Force/Checking-prime-numbers
make run
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
