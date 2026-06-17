# Divide and Conquer (Algoritma & Strategi)

[![C++](https://img.shields.io/badge/C%2B%2B-17-blue)](https://isocpp.org/)

---

## Description

This project demonstrates **Divide and Conquer algorithm strategies** — solving problems by dividing them into smaller subproblems, solving each recursively, then combining the results. It includes implementations of:

- **Merge Sort**: Sorting by recursively splitting the array in half, sorting each half, and merging them back.
- **Quick Sort**: Sorting by partitioning around a pivot element and recursively sorting the partitions.

All programs are console-based and run in the terminal.

---

## Features

- Classic divide-and-conquer sorting algorithm implementations.
- Step-by-step output showing sorting progress.
- Clear, readable C++ code with comments.
- Simple Makefiles for easy build & run.

---

## Directory Structure

```
Devide-and-Conquer/
├── Sorting/
│   ├── Sorting.cpp
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

**Example for Sorting:**

```bash
cd Learning-CPP/Algoritms-Strategy/Devide-and-Conquer/Sorting
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
