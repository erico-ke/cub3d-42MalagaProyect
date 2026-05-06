#!/bin/bash

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}  CUB3D - BATERÍA DE PRUEBAS${NC}"
echo -e "${BLUE}========================================${NC}\n"

# Crear directorio para mapas de prueba si no existe
mkdir -p test_maps

# Test 1: Mapa válido (example.cub)
echo -e "${YELLOW}Test 1: Mapa válido (example.cub)${NC}"
./cub3d example.cub > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo -e "${GREEN}✓ PASS: Mapa válido aceptado${NC}\n"
else
    echo -e "${RED}✗ FAIL: Mapa válido rechazado${NC}\n"
fi

# Test 2: RGB con letras
echo -e "${YELLOW}Test 2: RGB inválido - con letras (255a,100,50)${NC}"
cat > test_maps/invalid_rgb_letters.cub << 'EOF'
NO ./textures/north.png
SO ./textures/south.png
WE ./textures/west.png
EA ./textures/east.png
F 255a,100,50
C 225,30,0
        1111111111111111111111111
        1000000000110000000000001
        10110000011100000N0000001
        1111111111111111111111111
EOF
./cub3d test_maps/invalid_rgb_letters.cub 2>&1 | grep -i "error"
echo ""

# Test 3: RGB fuera de rango
echo -e "${YELLOW}Test 3: RGB inválido - fuera de rango (300,100,50)${NC}"
cat > test_maps/invalid_rgb_range.cub << 'EOF'
NO ./textures/north.png
SO ./textures/south.png
WE ./textures/west.png
EA ./textures/east.png
F 300,100,50
C 225,30,0
        1111111111111111111111111
        1000000000110000000000001
        10110000011100000N0000001
        1111111111111111111111111
EOF
./cub3d test_maps/invalid_rgb_range.cub 2>&1 | grep -i "error"
echo ""

# Test 4: Textura duplicada
echo -e "${YELLOW}Test 4: Textura duplicada (NO aparece dos veces)${NC}"
cat > test_maps/duplicate_texture.cub << 'EOF'
NO ./textures/north.png
NO ./textures/north.png
SO ./textures/south.png
WE ./textures/west.png
EA ./textures/east.png
F 120,200,0
C 225,30,0
        1111111111111111111111111
        1000000000110000000000001
        10110000011100000N0000001
        1111111111111111111111111
EOF
./cub3d test_maps/duplicate_texture.cub 2>&1 | grep -i "error"
echo ""

# Test 5: Textura vacía
echo -e "${YELLOW}Test 5: Textura vacía (NO sin ruta)${NC}"
cat > test_maps/empty_texture.cub << 'EOF'
NO
SO ./textures/south.png
WE ./textures/west.png
EA ./textures/east.png
F 120,200,0
C 225,30,0
        1111111111111111111111111
        1000000000110000000000001
        10110000011100000N0000001
        1111111111111111111111111
EOF
./cub3d test_maps/empty_texture.cub 2>&1 | grep -i "error"
echo ""

# Test 6: RGB con espacios
echo -e "${YELLOW}Test 6: RGB inválido - con espacios (255, 100, 50)${NC}"
cat > test_maps/invalid_rgb_spaces.cub << 'EOF'
NO ./textures/north.png
SO ./textures/south.png
WE ./textures/west.png
EA ./textures/east.png
F 255, 100, 50
C 225,30,0
        1111111111111111111111111
        1000000000110000000000001
        10110000011100000N0000001
        1111111111111111111111111
EOF
./cub3d test_maps/invalid_rgb_spaces.cub 2>&1 | grep -i "error"
echo ""

# Test 7: RGB con valores extra
echo -e "${YELLOW}Test 7: RGB inválido - demasiados valores (255,100,50,200)${NC}"
cat > test_maps/invalid_rgb_extra.cub << 'EOF'
NO ./textures/north.png
SO ./textures/south.png
WE ./textures/west.png
EA ./textures/east.png
F 255,100,50,200
C 225,30,0
        1111111111111111111111111
        1000000000110000000000001
        10110000011100000N0000001
        1111111111111111111111111
EOF
./cub3d test_maps/invalid_rgb_extra.cub 2>&1 | grep -i "error"
echo ""

# Test 8: Textura faltante
echo -e "${YELLOW}Test 8: Textura faltante (sin NO)${NC}"
cat > test_maps/missing_texture.cub << 'EOF'
SO ./textures/south.png
WE ./textures/west.png
EA ./textures/east.png
F 120,200,0
C 225,30,0
        1111111111111111111111111
        1000000000110000000000001
        10110000011100000N0000001
        1111111111111111111111111
EOF
./cub3d test_maps/missing_texture.cub 2>&1 | grep -i "error"
echo ""

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}  FIN DE PRUEBAS${NC}"
echo -e "${BLUE}========================================${NC}"
