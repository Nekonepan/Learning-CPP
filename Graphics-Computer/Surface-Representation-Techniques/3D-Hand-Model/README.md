# 3D Hand Model — Catmull-Clark Subdivision Surface (OpenGL / C++)

This project implements a **3D Hand Model** using the **Catmull-Clark Subdivision Technique** in C++ with the OpenGL/GLUT library. It generates a low-poly base control mesh of a hand procedurally and refines it dynamically through multiple subdivision iterations to produce a smooth, organic 3D hand model.

---

## 🎨 Visuals & Features

- **Procedural Palm & Fingers**: Generates a blocky palm control mesh and extrudes 5 fingers (pinky, ring, middle, index, and thumb) automatically.
- **Watertight Manifold**: Features closed-loop fingertips and a triangle fan cap at the wrist.
- **Dynamic Subdivision Levels (0 - 3)**: Recalculates and caches subdivision depths at startup to maintain 60 FPS real-time interactive rotation.
- **Flat vs. Smooth Shading**: Toggle between a faceted low-poly artistic look (Flat) and a smooth organic model (Smooth).
- **Wireframe Overlay**: Option to display the subdivision grid lines over the shaded surface.
- **Color Presets**: Toggle between 4 distinct lighting themes (Marble, Skin Tone, Bronze, Jade).

---

## 🎮 Controls

| Key | Action |
|---|---|
| **`+` / `=`** | **Increase Subdivision Level** (Level 0 $\rightarrow$ 3) |
| **`-` / `_`** | **Decrease Subdivision Level** (Level 3 $\rightarrow$ 0) |
| **`S` / `s`** | **Toggle Shading** (Flat Faceted / Smooth Shading) |
| **`W` / `w`** | **Toggle Wireframe Overlay** (ON / OFF) |
| **`1` / `2` / `3` / `4`** | **Switch Color Presets** (1: White, 2: Red, 3: Green, 4: Blue) |
| **`Space`** | **Toggle Auto-Rotation** |
| **`R` / `r`** | **Reset Camera & Zoom** |
| **Arrow Keys (`← → ↑ ↓`)** | Rotate hand horizontally/vertically |
| **Page Up / Page Down** | Zoom In / Out |
| **`ESC`** | Exit program |

---

## 🚀 How to Build & Run

From the project directory:

```bash
make run
```

This will automatically create a `build/` folder, compile the sources with `-O2` compiler optimization, and launch the GLUT rendering window.

### Manual Compilation
If `make` is unavailable, compile manually using `g++`:

```bash
g++ *.cpp -o 3D-Hand-Model -lglut -lGLU -lGL -O2 -std=c++17
./3D-Hand-Model
```

---

## 🛠️ Code Structure

```
3D-Hand-Model/
├── main.cpp          # Hand base mesh generator + Subdivision engine + GLUT loop
├── COLOR.h / .cpp    # RGBA color representation
├── VECTOR3D.h / .cpp # 3D vector math utility (dot, cross, normalization)
├── TIMER.h / .cpp    # High-resolution chrono timer
├── Makefile          # Project Makefile (Linux, macOS, Windows compatible)
└── README.md         # Documentation
```

---

## 📐 Mathematical Details (Catmull-Clark)

The **Catmull-Clark algorithm** operates on an arbitrary polygon mesh. In each subdivision step:

1. **Face Points ($f_p$)**: For each face, a new face point is created at the average position of all its original vertices.
   $$f_p = \frac{1}{v_n}\sum_{i=1}^{v_n} V_i$$
2. **Edge Points ($e_p$)**: For each edge, a new edge point is created at the average of its endpoints and the face points of the adjacent faces sharing the edge.
   $$e_p = \frac{V_1 + V_2 + F_1 + F_2}{4}$$
3. **Vertex Points ($v'_p$)**: Each original vertex $V$ is updated to a new position $V'$ based on its valence $n$ (the number of adjacent edges):
   $$V' = \frac{F + 2E + (n - 3)V}{n}$$
   Where $F$ is the average of sharing face points, and $E$ is the average of midpoints of all sharing edges.
