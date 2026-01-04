# 🧮 RAYCASTING - Fundamentos Matemáticos

[![es](https://img.shields.io/badge/lang-es-red.svg)](RAYCASTING_EXPLAINED.md)
[![en](https://img.shields.io/badge/lang-en-blue.svg)](RAYCASTING_EXPLAINED.en.md)

Explicación basada en [https://lodev.org/cgtutor/raycasting.html](https://lodev.org/cgtutor/raycasting.html)

El raycasting es una técnica de renderizado que simula gráficos 3D a partir de un mapa 2D. A continuación se explica detalladamente la matemática detrás del vector, el cálculo de dirección del rayo y el algoritmo DDA.

---

## 🧮 1. Vectores: Fundamentos del Raycasting

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

## 🎯 2. Dirección del Rayo para Cada Columna de la Pantalla

Para cada línea vertical (`x`) de la pantalla:

* Mapea el número de columna a un valor entre -1 y 1:

  $$
  \text{cameraX} = 2x / \text{screenWidth} - 1
  $$

  * `x = 0` → `cameraX = -1` (borde izquierdo)
  * `x = screenWidth/2` → `cameraX = 0` (centro)
  * `x = screenWidth - 1` → `cameraX = 1` (borde derecho)

Luego calcula la dirección del rayo para esta columna:

$$
\text{rayDir} = \text{dir} + \text{plane} \times \text{cameraX}
$$

> Así, cada rayo es una versión ligeramente rotada de la dirección hacia adelante del jugador, basada en su posición en la pantalla.

---

## 🔁 3. Algoritmo DDA (Digital Differential Analyzer)

DDA ayuda a encontrar **dónde un rayo golpea primero una pared** avanzando por la cuadrícula **celda por celda**. Así funciona la matemática:

### Paso 1: Encuentra el cuadrado de la cuadrícula actual donde está el jugador:

$$
\text{mapX} = \text{int}(pos.x) \quad , \quad \text{mapY} = \text{int}(pos.y)
$$

### Paso 2: Calcula los componentes de dirección del rayo:

$$
\text{rayDirX}, \text{rayDirY}
$$

### Paso 3: Calcula qué tan lejos debemos viajar para cruzar una línea de cuadrícula x o y:

$$
\text{deltaDistX} = \left| \frac{1}{\text{rayDirX}} \right| \quad , \quad \text{deltaDistY} = \left| \frac{1}{\text{rayDirY}} \right|
$$

* Esto indica qué tan lejos el rayo necesita moverse a lo largo de la dirección del rayo para moverse 1 unidad en x o y.

### Paso 4: Determina la dirección del paso y las distancias laterales iniciales:

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

### Paso 5: Ejecuta el bucle DDA:

* En cada paso, muévete al **cuadrado más cercano** (ya sea en dirección x o y), según cuál distancia lateral sea menor:

```cpp
while (hit == false) {
    if (sideDistX < sideDistY) {
        sideDistX += deltaDistX;
        mapX += stepX;
        side = 0;  // golpeó lado vertical
    } else {
        sideDistY += deltaDistY;
        mapY += stepY;
        side = 1;  // golpeó lado horizontal
    }

    // Verifica si el rayo golpeó una pared en map[mapX][mapY]
    if (worldMap[mapX][mapY] > 0) hit = true;
}
```

---

## 📏 4. Calcular la Distancia a la Pared

Después de golpear la pared, calcula la **distancia perpendicular a la pared** (para evitar distorsión de ojo de pez):

```cpp
if (side == 0)
    perpWallDist = (mapX - pos.x + (1 - stepX) / 2) / rayDirX;
else
    perpWallDist = (mapY - pos.y + (1 - stepY) / 2) / rayDirY;
```

---

## 🧱 5. Proyectar la Pared en la Pantalla

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

## 📌 Tabla Resumen de Variables Clave

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

---

## 📚 Referencias

- [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html)
- [Wolfenstein 3D Source Code](https://github.com/id-Software/wolf3d)
