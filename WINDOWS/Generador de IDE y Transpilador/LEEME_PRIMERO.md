# 📦 PAQUETE COMPLETO - DSL Agricultura para Windows

## ✅ ¿Qué contiene este paquete?

He preparado **TODO lo necesario** para que tu proyecto funcione perfectamente en Windows.

---

## 📂 Estructura del Paquete

```
DSL-Agricultura-Windows/
│
├── 📄 README.md                          # Documentación principal
├── 🚀 INSTALAR.bat                       # Instalador automático
│
├── 📁 transpilador/                      # Backend del compilador
│   ├── Makefile.win                     # Makefile para Windows
│   ├── compile.bat                      # Compilar transpilador
│   ├── run_lexer.bat                    # Validar léxico
│   ├── run_parser.bat                   # Validar sintaxis
│   ├── run_codegen.bat                  # Generar código C++
│   └── run_simulator.bat                # Ejecutar simulación
│
├── 📁 ide/                               # Frontend Qt
│   ├── IDE-Agricultura.pro              # Proyecto Qt adaptado
│   ├── compile_ide.bat                  # Compilar IDE
│   └── mainwindow_windows_notes.cpp     # Notas de cambios
│
├── 📁 ejemplos/                          # Programas de ejemplo
│   ├── ejemplo_basico.agro              # Ejemplo simple
│   └── ejemplo_iot.agro                 # Ejemplo IoT completo
│
└── 📁 docs/                              # Documentación
    ├── INSTALACION_WINDOWS.md           # Guía completa paso a paso
    └── MODIFICACIONES_NECESARIAS.md     # Cambios en el código
```

---

## 🚀 Inicio Rápido (2 pasos)

### 1️⃣ Instalar Herramientas (Ver documento docs/MODIFICACIONES_NECESARIAS.md)

### 2️⃣ Ejecutar Instalador

```cmd
INSTALAR.bat
```

¡Listo! El instalador compilará todo automáticamente.

## 📖 Documentación Incluida

1. **README.md** - Visión general del proyecto
2. **INSTALACION_WINDOWS.md** - Guía detallada paso a paso

## 🐛 Solución Rápida de Problemas

### "flex no reconocido"
→ Agregar `C:\msys64\usr\bin` al PATH

### "qmake no reconocido"
→ Agregar `C:\Qt\6.x.x\mingw_64\bin` al PATH

### "No se encuentra transpilador.exe"
→ Compilar primero con `compile.bat`

### IDE no ejecuta programas
→ Verificar que `mainwindow.cpp` tiene las modificaciones

---

*Última actualización: 2025-11-03*  
*Versión: 2.0 - Windows Edition*  
*Compatible con: Windows 10/11 (64 bits)*

**¡Éxito con tu proyecto! 🌾**
