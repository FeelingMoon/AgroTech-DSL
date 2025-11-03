#!/bin/bash

# Script para validar análisis léxico
# Usa el transpilador completo pero filtra solo errores léxicos

ARCHIVO=$1

if [ -z "$ARCHIVO" ]; then
    echo "❌ Error: No se especificó archivo"
    exit 1
fi

echo "╔═══════════════════════════════════════╗"
echo "║   FASE 1: ANÁLISIS LÉXICO (LEXER)    ║"
echo "╚═══════════════════════════════════════╝"
echo ""
echo "📝 Archivo: $ARCHIVO"
echo "🔍 Iniciando tokenización..."
echo ""

# Ejecutar el transpilador y capturar solo errores léxicos
OUTPUT=$(./transpilador "$ARCHIVO" 2>&1)
EXIT_CODE=$?

# Verificar si hay errores léxicos (caracteres no reconocidos)
if echo "$OUTPUT" | grep -q "Carácter no reconocido"; then
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo "❌ ERRORES LÉXICOS ENCONTRADOS:"
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo ""
    echo "$OUTPUT" | grep "Carácter no reconocido"
    echo ""
    echo "❌ Se encontraron caracteres no válidos"
    echo "💡 Revisa los caracteres marcados arriba"
    exit 1
fi

# Si llegamos aquí, el análisis léxico fue exitoso
echo "✅ Análisis léxico completado"
echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo "✓ Todos los tokens fueron identificados correctamente"
echo "✓ No se encontraron caracteres inválidos"
echo "✓ El vocabulario del lenguaje es correcto"
exit 0
