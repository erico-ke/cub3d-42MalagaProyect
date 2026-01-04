# cub3D

[![es](https://img.shields.io/badge/lang-es-red.svg)](README.md)
[![en](https://img.shields.io/badge/lang-en-blue.svg)](README.en.md)

![42 Project](https://img.shields.io/badge/42-Project-blue)

## 📋 Descripción del Proyecto

**cub3D** es un proyecto de 42 School inspirado en el legendario **Wolfenstein 3D**, considerado el primer FPS de la historia. El objetivo es crear una vista 3D realista dentro de un laberinto desde una perspectiva en primera persona usando la técnica de **raycasting**.

Este proyecto es una introducción a los gráficos 3D en programación, permitiendo explorar los conceptos matemáticos y algorítmicos detrás de la renderización de entornos 3D en tiempo real.

---

## 🎯 Objetivos del Proyecto

- Implementar un motor de raycasting funcional desde cero
- Parsear y validar archivos de configuración `.cub` que definen el mapa y las texturas
- Renderizar un entorno 3D navegable en tiempo real
- Gestionar eventos de teclado para movimiento y rotación del jugador
- Aplicar texturas a las paredes según su orientación
- Manejar correctamente la memoria y evitar memory leaks

---

## 🛠️ Requisitos Técnicos

### Compilación
- **Lenguaje**: C
- **Norma**: Código conforme a la Norma de 42
- **Compilador**: `gcc` con flags `-Wall -Wextra -Werror`
- **Makefile**: Debe incluir las reglas: `all`, `clean`, `fclean`, `re`

### Librerías Utilizadas
- **MLX42**: Librería gráfica para gestionar ventanas, imágenes y eventos
- **libft**: Librería personal de funciones C
- **math.h**: Para cálculos matemáticos del raycasting

### Funcionalidad Mínima

#### 1. **Archivo de Configuración (.cub)**
El programa debe aceptar como argumento un archivo `.cub` con el siguiente formato:

```
NO ./path_to_north_texture.png
SO ./path_to_south_texture.png
WE ./path_to_west_texture.png
EA ./path_to_east_texture.png

F 220,100,0     (Color del suelo en RGB)
C 225,30,0      (Color del techo en RGB)

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

**Características del mapa:**
- `0`: espacio vacío (navegable)
- `1`: pared
- `N`, `S`, `E`, `W`: posición inicial y orientación del jugador
- El mapa debe estar rodeado de paredes (`1`)

#### 2. **Controles**
- `W`, `A`, `S`, `D`: Movimiento (adelante, izquierda, atrás, derecha)
- `←`, `→`: Rotación de la cámara (izquierda/derecha)
- `ESC`: Cerrar la ventana y salir del programa

#### 3. **Renderizado**
- Vista 3D usando raycasting
- Texturas diferentes para cada orientación de pared (Norte, Sur, Este, Oeste)
- Colores sólidos para techo y suelo
- Ventana de tamaño: 1200x600 píxeles

#### 4. **Validación de Errores**
El programa debe manejar errores como:
- Archivo inexistente o inaccesible
- Extensión incorrecta (debe ser `.cub`)
- Texturas faltantes o inválidas
- Valores RGB fuera del rango [0-255]
- Mapa no cerrado por paredes
- Caracteres inválidos en el mapa
- Múltiples posiciones de jugador o ninguna

---

## 📂 Estructura del Proyecto

```
cub3d/
├── includes/
│   └── cub3d.h              # Definiciones, estructuras y prototipos
├── libs/
│   ├── libft/               # Librería personal de funciones C
│   └── MLX42/               # Librería gráfica MLX42
├── src/
│   ├── main.c               # Punto de entrada del programa
│   ├── parser*.c            # Parseo y validación del archivo .cub
│   ├── mlx*.c               # Inicialización y gestión de MLX
│   ├── raycast*.c           # Motor de raycasting
│   ├── texture*.c           # Carga y aplicación de texturas
│   └── debug.c              # Utilidades de depuración
├── textures/                # Texturas PNG para las paredes
├── test_maps/               # Mapas de prueba con casos edge
├── Makefile
└── README.md
```

---

## 🚀 Compilación y Uso

### Compilar el proyecto
```bash
make
```

### Ejecutar el programa
```bash
./cub3d maps/example.cub
```

### Limpiar archivos objeto
```bash
make clean
```

### Limpiar completamente
```bash
make fclean
```

---

## 🧮 RAYCASTING - Fundamentos Matemáticos

Explicación basada en [https://lodev.org/cgtutor/raycasting.html](https://lodev.org/cgtutor/raycasting.html)

El raycasting es una técnica de renderizado que simula gráficos 3D a partir de un mapa 2D. A continuación se explica detalladamente la matemática detrás del vector, el cálculo de dirección del rayo y el algoritmo DDA.

---

### 🧮 1. Vectores: Fundamentos del Raycasting

Raycasting en 2D usa **vectores** para representar:

* La **posición del jugador**:

  $$
  \text{pos} = (x, y)
  $$

* La **dirección hacia donde mira el jugador**:

  $$
  \text{dir} = (x, y)
  $$

  * Este es un **vector unitario** que apunta hacia adelante.

* El **plano de la cámara**:

  $$
  \text{plane} = (x, y)
  $$

  * Este es **perpendicular** a `dir`.
  * Determina el campo de visión (FOV).

> Piensa en `dir` como "hacia adelante", y `plane` como "de izquierda a derecha" a través de la pantalla.

---

### 🎯 2. Ray Direction for Each Screen Column

For every vertical stripe (`x`) of the screen:

* Map the column number to a value between -1 and 1:

  $$
  \text{cameraX} = 2x / \text{screenWidth} - 1
  $$

  * `x = 0` → `cameraX = -1` (left edge)
  * `x = screenWidth/2` → `cameraX = 0` (center)
  * `x = screenWidth - 1` → `cameraX = 1` (right edge)

Then calculate the direction of the ray for this column:

$$
\text{rayDir} = \text{dir} + \text{plane} \times \text{cameraX}
$$

> So every ray is a slightly rotated version of the player’s forward direction, based on its position on the screen.

---

### 🔁 3. Algoritmo DDA (Digital Differential Analyzer)

DDA ayuda a encontrar **dónde un rayo golpea primero una pared** avanzando por la cuadrícula **celda por celda**. Así funciona la matemática:

#### Paso 1: Encuentra el cuadrado de la cuadrícula actual donde está el jugador:

$$
\text{mapX} = \text{int}(pos.x) \quad , \quad \text{mapY} = \text{int}(pos.y)
$$

#### Paso 2: Calcula los componentes de dirección del rayo:

$$
\text{rayDirX}, \text{rayDirY}
$$

#### Paso 3: Calcula qué tan lejos debemos viajar para cruzar una línea de cuadrícula x o y:

$$
\text{deltaDistX} = \left| \frac{1}{\text{rayDirX}} \right| \quad , \quad \text{deltaDistY} = \left| \frac{1}{\text{rayDirY}} \right|
$$

* Esto indica qué tan lejos el rayo necesita moverse a lo largo de la dirección del rayo para moverse 1 unidad en x o y.

#### Paso 4: Determina la dirección del paso y las distancias laterales iniciales:

```cpp
if (rayDirX < 0) {
    stepX = -1;
    sideDistX = (pos.x - mapX) * deltaDistX;
} else {
    stepX = 1;
    sideDistX = (mapX + 1.0 - pos.x) * deltaDistX;
}

if (rayDirY < 0) {
    stepY = -1;
    sideDistY = (pos.y - mapY) * deltaDistY;
} else {
    stepY = 1;
    sideDistY = (mapY + 1.0 - pos.y) * deltaDistY;
}
```

#### Paso 5: Ejecuta el bucle DDA:

* En cada paso, muévete al **cuadrado más cercano** (ya sea en dirección x o y), según cuál distancia lateral sea menor:

```cpp
while (hit == false) {
    if (sideDistX < sideDistY) {
        sideDistX += deltaDistX;
        mapX += stepX;
        side = 0;  // hit vertical side
    } else {
        sideDistY += deltaDistY;
        mapY += stepY;
        side = 1;  // hit horizontal side
    }

    // Verifica si el rayo golpeó una pared en map[mapX][mapY]
    if (worldMap[mapX][mapY] > 0) hit = true;
}
```

---

### 📏 4. Calcular la Distancia a la Pared

Después de golpear la pared, calcula la **distancia perpendicular a la pared** (para evitar distorsión de ojo de pez):

```cpp
if (side == 0)
    perpWallDist = (mapX - pos.x + (1 - stepX) / 2) / rayDirX;
else
    perpWallDist = (mapY - pos.y + (1 - stepY) / 2) / rayDirY;
```

---

### 🧱 5. Proyectar la Pared en la Pantalla

Ahora convierte la distancia a una altura de línea en pantalla:

$$
\text{lineHeight} = \frac{\text{screenHeight}}{\text{perpWallDist}}
$$

Luego calcula las coordenadas y de inicio y fin para dibujar la línea vertical de la pared:

```cpp
int drawStart = -lineHeight / 2 + screenHeight / 2;
int drawEnd = lineHeight / 2 + screenHeight / 2;
```

---

### 📌 Tabla Resumen de Variables Clave

| Variable       | Significado                                       |
| -------------- | --------------------------------------------------|
| `pos`          | Vector de posición del jugador `(x, y)`           |
| `dir`          | Vector de dirección de vista                      |
| `plane`        | Plano de cámara (perpendicular a `dir`)           |
| `rayDir`       | Dirección del rayo actual                         |
| `deltaDistX/Y` | Distancia a la siguiente línea de cuadrícula x/y  |
| `sideDistX/Y`  | Distancia acumulada al siguiente lado             |
| `stepX/Y`      | Dirección de paso en la cuadrícula del mapa       |
| `perpWallDist` | Distancia corregida a la pared                    |
| `lineHeight`   | Altura de la pared a dibujar                      |
