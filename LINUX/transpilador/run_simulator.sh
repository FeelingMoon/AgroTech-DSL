#!/bin/bash

# Script para ejecutar la simulación final

echo "╔═══════════════════════════════════════╗"
echo "║     FASE 4: SIMULACIÓN FINAL          ║"
echo "╚═══════════════════════════════════════╝"
echo ""
echo "▶️  Ejecutando simulador..."
echo "🌱 Sistema de agricultura automatizada"
echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo ""

# Verificar que el simulador existe
if [ ! -f "./simulador" ]; then
    echo "❌ El ejecutable 'simulador' no existe"
    exit 1
fi

# Ejecutar el simulador
./simulador
EXIT_CODE=$?

echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo ""

if [ $EXIT_CODE -eq 0 ]; then
    echo "✅ Simulación completada exitosamente"
    exit 0
else
    echo "❌ Error durante la simulación"
    exit 1
fi
