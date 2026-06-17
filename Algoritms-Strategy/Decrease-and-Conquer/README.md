# Decrease and Conquer (Algoritma & Strategi)

[![C++](https://img.shields.io/badge/C%2B%2B-17-blue)](https://isocpp.org/)

---

## Description

This project demonstrates **Decrease and Conquer algorithm strategies** — solving problems by reducing the problem size by a constant factor at each step. It includes implementations of:

- **Binary Search**: Efficiently finding an element in a sorted array by halving the search space each step.
- **Insertion Sort**: Sorting by repeatedly inserting the next element into its correct position in the sorted portion.
- **Selection Sort**: Sorting by repeatedly selecting the minimum element from the unsorted portion.

All programs are console-based and run in the terminal.

---

## Features

- Classic decrease-and-conquer implementations for searching and sorting.
- Step-by-step output showing algorithm progress.
- Clear, readable C++ code with comments.
- Simple Makefiles for easy build & run.

---

## Directory Structure

```
Decrease-and-Conquer/
├── Binary-Search/
│   ├── Binary-search.cpp
│   └── Makefile
├── Insertion-Sort/
│   ├── Insertion-sort.cpp
│   └── Makefile
├── Selection-Sort/
│   ├── Selection-sort.cpp
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

**Example for Binary Search:**

```bash
cd Learning-CPP/Algoritms-Strategy/Decrease-and-Conquer/Binary-Search
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
