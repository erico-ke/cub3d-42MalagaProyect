# cub3D

[![es](https://img.shields.io/badge/lang-es-red.svg)](README.md)
[![en](https://img.shields.io/badge/lang-en-blue.svg)](README.en.md)

![42 Project](https://img.shields.io/badge/42-Project-blue)

## 📋 Project Description

**cub3D** is a 42 School project inspired by the legendary **Wolfenstein 3D**, considered the first FPS in history. The goal is to create a realistic 3D view inside a maze from a first-person perspective using the **raycasting** technique.

This project is an introduction to 3D graphics programming, allowing exploration of mathematical and algorithmic concepts behind real-time 3D environment rendering.

---

## 🎯 Project Objectives

- Implement a functional raycasting engine from scratch
- Parse and validate `.cub` configuration files that define the map and textures
- Render a navigable 3D environment in real-time
- Handle keyboard events for player movement and rotation
- Apply textures to walls based on their orientation
- Properly manage memory and avoid memory leaks

---

## 🛠️ Technical Requirements

### Compilation
- **Language**: C
- **Norm**: Code compliant with 42 Norm
- **Compiler**: `gcc` with flags `-Wall -Wextra -Werror`
- **Makefile**: Must include rules: `all`, `clean`, `fclean`, `re`

### Libraries Used
- **MLX42**: Graphics library for managing windows, images, and events
- **libft**: Personal C function library
- **math.h**: For raycasting mathematical calculations

### Minimum Functionality

#### 1. **Configuration File (.cub)**
The program must accept a `.cub` file as an argument with the following format:

```
NO ./path_to_north_texture.png
SO ./path_to_south_texture.png
WE ./path_to_west_texture.png
EA ./path_to_east_texture.png

F 220,100,0     (Floor color in RGB)
C 225,30,0      (Ceiling color in RGB)

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011111N111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

**Map characteristics:**
- `0`: empty space (walkable)
- `1`: wall
- `N`, `S`, `E`, `W`: initial position and player orientation
- The map must be surrounded by walls (`1`)

#### 2. **Controls**
- `W`, `A`, `S`, `D`: Movement (forward, left, backward, right)
- `←`, `→`: Camera rotation (left/right)
- `ESC`: Close the window and exit the program

#### 3. **Rendering**
- 3D view using raycasting
- Different textures for each wall orientation (North, South, East, West)
- Solid colors for ceiling and floor
- Window size: 1200x600 pixels

#### 4. **Error Validation**
The program must handle errors such as:
- Non-existent or inaccessible file
- Incorrect extension (must be `.cub`)
- Missing or invalid textures
- RGB values out of range [0-255]
- Map not closed by walls
- Invalid characters in the map
- Multiple player positions or none

---

## 📂 Project Structure

```
cub3d/
├── includes/
│   └── cub3d.h              # Definitions, structures, and prototypes
├── libs/
│   ├── libft/               # Personal C function library
│   └── MLX42/               # MLX42 graphics library
├── src/
│   ├── main.c               # Program entry point
│   ├── parser*.c            # .cub file parsing and validation
│   ├── mlx*.c               # MLX initialization and management
│   ├── raycast*.c           # Raycasting engine
│   ├── texture*.c           # Texture loading and application
│   └── debug.c              # Debug utilities
├── textures/                # PNG textures for walls
├── test_maps/               # Test maps with edge cases
├── Makefile
└── README.md
```

---

## 🚀 Compilation and Usage

### Compile the project
```bash
make
```

### Run the program
```bash
./cub3d maps/example.cub
```

### Clean object files
```bash
make clean
```

### Full clean
```bash
make fclean
```

---

## 📚 Additional Resources

### 🧮 Raycasting Fundamentals

This project uses the **raycasting** technique to render 3D graphics from a 2D map.

**To understand in depth the math behind raycasting** (vectors, DDA algorithm, distance calculations, etc.), see:

📖 **[RAYCASTING_EXPLAINED.en.md](RAYCASTING_EXPLAINED.en.md)** - Detailed explanation in English

### Useful links
- [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html) - Complete raycasting tutorial
- [Wolfenstein 3D Source Code](https://github.com/id-Software/wolf3d) - Original game source code
