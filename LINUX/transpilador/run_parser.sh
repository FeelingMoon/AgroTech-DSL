#!/bin/bash

# Script para validar análisis sintáctico
# Asume que el léxico ya pasó

ARCHIVO=$1

if [ -z "$ARCHIVO" ]; then
    echo "❌ Error: No se especificó archivo"
    exit 1
fi

echo "╔═══════════════════════════════════════╗"
echo "║  FASE 2: ANÁLISIS SINTÁCTICO (PARSER) ║"
echo "╚═══════════════════════════════════════╝"
echo ""
echo "🔍 Verificando estructura gramatical..."
echo "🌳 Construyendo AST..."
echo ""

# Ejecutar el transpilador completo
OUTPUT=$(./transpilador "$ARCHIVO" 2>&1)
EXIT_CODE=$?

# Buscar errores sintácticos específicos
HAS_SYNTAX_ERROR=0

if echo "$OUTPUT" | grep -q "Error en línea"; then
    HAS_SYNTAX_ERROR=1
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo "❌ ERRORES SINTÁCTICOS ENCONTRADOS:"
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo ""
    echo "$OUTPUT" | grep "Error en línea"
    echo ""
fi

if echo "$OUTPUT" | grep -q "syntax error"; then
    HAS_SYNTAX_ERROR=1
    if [ $HAS_SYNTAX_ERROR -eq 0 ]; then
        echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
        echo "❌ ERRORES SINTÁCTICOS ENCONTRADOS:"
        echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
        echo ""
    fi
    echo "$OUTPUT" | grep -i "syntax error"
    echo ""
fi

# Si hubo errores, terminar
if [ $HAS_SYNTAX_ERROR -eq 1 ]; then
    echo "❌ La estructura gramatical tiene errores"
    echo "💡 Revisa las estructuras: INICIAR/FINALIZAR, LOTE, CULTIVO"
    echo "💡 Verifica que todas las instrucciones estén bien escritas"
    exit 1
fi

# Verificar que el transpilador terminó correctamente
if [ $EXIT_CODE -ne 0 ]; then
    echo "❌ El análisis no se completó correctamente"
    exit 1
fi

# Verificar que se generó el análisis sintáctico
if echo "$OUTPUT" | grep -q "Análisis sintáctico completado"; then
    echo "✅ Análisis sintáctico completado"
    echo ""
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo "✓ La estructura del programa es correcta"
    echo "✓ Todas las reglas gramaticales se cumplen"
    echo "✓ AST generado exitosamente"
    exit 0
else
    echo "⚠️ No se pudo confirmar el análisis sintáctico"
    exit 1
fi
