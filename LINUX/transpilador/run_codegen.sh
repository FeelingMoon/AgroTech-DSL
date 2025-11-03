#!/bin/bash

# Script para generar código C++ y compilarlo

ARCHIVO=$1

if [ -z "$ARCHIVO" ]; then
    echo "❌ Error: No se especificó archivo"
    exit 1
fi

echo "╔═══════════════════════════════════════╗"
echo "║  FASE 3: GENERACIÓN DE CÓDIGO C++     ║"
echo "╚═══════════════════════════════════════╝"
echo ""
echo "⚙️  Generando código C++ desde el AST..."
echo ""

# Ejecutar transpilador para generar C++
./transpilador "$ARCHIVO" > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "❌ Error al generar código C++"
    exit 1
fi

# Verificar que salida.cpp existe
if [ ! -f "salida.cpp" ]; then
    echo "❌ No se generó el archivo salida.cpp"
    exit 1
fi

echo "✅ Archivo salida.cpp generado"
echo ""
echo "🔨 Compilando C++ con g++..."
echo ""

# Compilar el C++ generado
COMPILE_OUTPUT=$(g++ salida.cpp -o simulador 2>&1)
COMPILE_EXIT=$?

if [ $COMPILE_EXIT -ne 0 ]; then
    echo "❌ Errores de compilación:"
    echo "$COMPILE_OUTPUT"
    exit 1
fi

# Verificar warnings
if echo "$COMPILE_OUTPUT" | grep -q "warning:"; then
    echo "⚠️  Advertencias de compilación:"
    echo "$COMPILE_OUTPUT" | grep "warning:"
    echo ""
fi

echo "✅ Compilación exitosa"
echo "✅ Ejecutable 'simulador' creado"
exit 0
