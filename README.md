# cub3D

[![Español](https://img.shields.io/badge/🇪🇸-Español-red)](README.md)
[![English](https://img.shields.io/badge/🇺🇸-English-blue)](README.en.md)

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

## 📚 Recursos Adicionales

### 🧮 Fundamentos de Raycasting

Este proyecto utiliza la técnica de **raycasting** para renderizar gráficos 3D a partir de un mapa 2D.

**Para entender en profundidad la matemática detrás del raycasting** (vectores, algoritmo DDA, cálculo de distancias, etc.), consulta:

📖 **[RAYCASTING_EXPLAINED.md](RAYCASTING_EXPLAINED.md)** - Explicación detallada en español

### Enlaces útiles
- [Lode's Computer Graphics Tutorial](https://lodev.org/cgtutor/raycasting.html) - Tutorial completo de raycasting
- [Wolfenstein 3D Source Code](https://github.com/id-Software/wolf3d) - Código fuente del juego original
