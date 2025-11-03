# 🌾 AgroTech DSL - Lenguaje de Automatización Agrícola

## Versión 3.1 (Edición Multiplataforma)

![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-blue)
![Qt](https://img.shields.io/badge/Qt-6.x-green)
![C++](https://img.shields.io/badge/C%2B%2B-17-orange)
![License](https://img.shields.io/badge/license-GNU%20GPL-lightgrey)

---

## 🎯 Descripción

**AgroTech DSL** es un lenguaje de dominio específico (DSL) diseñado para programar sistemas de automatización agrícola de forma simple e intuitiva. Incluye:

- 🔧 **Transpilador** - Convierte código DSL a C++ optimizado.
- 🖥️ **IDE Gráfico** - Editor con resaltado de sintaxis, validación en tiempo real y múltiples pestañas.
- 🌱 **Simulador** - Ejecuta y prueba tus programas agrícolas, simulando lecturas de sensores con valores aleatorios.
- 📊 **Visualización Jerárquica** - Salida clara con emojis, colores y estructura en árbol para una fácil comprensión.

El sistema soporta manejo de sensores IoT (temperatura, humedad, pH, etc.), control de actuadores (riego, fertilización), condiciones lógicas avanzadas, programación de tareas y sistema de alertas. La sintaxis está en español para mayor accesibilidad.

**Nota importante:** Actualmente, el sistema es un simulador académico/educativo. En un futuro se agregará soporte para sensores y dispositivos reales (IoT físico), convirtiéndolo en un sistema completamente funcional para entornos de producción agrícola.

---

## ✨ Características

### Lenguaje DSL
- ✅ Sintaxis clara en español.
- ✅ Manejo de sensores IoT (temperatura, humedad, pH, luz, CO2, presión, viento).
- ✅ Control de actuadores (riego, fertilización, activación de dispositivos).
- ✅ Condiciones lógicas avanzadas con operadores (Y, O, NO, <, >, ==, etc.) y expresiones anidadas.
- ✅ Programación de tareas y monitoreo periódico.
- ✅ Sistema de alertas y reportes.
- ✅ Soporte para expresiones matemáticas (+, -, *, /, %).
- ✅ Vinculación de variables a dispositivos.
- ✅ Soporte completo para IoT (dispositivos IP y serial).

### IDE
- ✅ Editor multi-pestaña con números de línea.
- ✅ Resaltado de sintaxis especializado en colores.
- ✅ Validación en tiempo real (detecta errores mientras escribes).
- ✅ Auto-guardado y protección contra pérdida de datos.
- ✅ Panel de errores con indicaciones específicas (número de línea, tipo de error).
- ✅ Compilación y ejecución integrada.
- ✅ Visualización del código C++ generado.
- ✅ Consola integrada para salida de simulación.
- ✅ Barra de estado con indicadores de validación, línea/columna y estado del archivo.
- ✅ Atajos de teclado (Ctrl+N, Ctrl+O, Ctrl+S, F5, etc.).
- ✅ Resaltado de línea actual y auto-completado de llaves.

### Transpilador
- ✅ Análisis léxico robusto (Flex).
- ✅ Parser con manejo de errores (Bison).
- ✅ Generación de código C++ optimizado.
- ✅ Visualización jerárquica perfecta en la salida del simulador.

### Simulador
- ✅ Ejecución en tiempo real con valores aleatorios para sensores.
- ✅ Salida colorida con emojis y estructura en árbol.
- ✅ Identación clara para jerarquías (lotes, cultivos, condiciones).

---

## 📋 Requisitos

### Sistema Operativo
- **Linux**: Ubuntu (desarrollado y probado aquí) o distribuciones compatibles.
- **Windows**: Windows 10 o superior (64 bits).

### Herramientas Comunes
- **Flex** (2.6.x o superior) y **Bison** (3.x o superior) para el transpilador.
- **GCC/G++** (11.x o superior) para compilación.
- **Qt 6.x** con MinGW 64-bit (para Windows) o qt6-base-dev (para Linux).
- **Make** para automatización de compilación.

### Requisitos Específicos por Plataforma
- **Linux (Ubuntu)**: `sudo apt-get install flex bison g++ make qt6-base-dev qt6-tools-dev`.
- **Windows**: MSYS2 con GCC, Flex, Bison y Make; Qt 6.x con MinGW.

---

## 🚀 Instalación Rápida

El repositorio está estructurado para facilitar la instalación en ambas plataformas. El código fuente del transpilador genera un archivo de salida C++ (`salida.cpp`) en la carpeta `transpilador` (o equivalente), independientemente del SO. Este archivo contiene el código transpilado y se puede compilar con `g++` para ejecutar el simulador.

### Estructura del Repositorio
```
Agricultura-DSL/
├── README.md                  # Este archivo con documentación completa
├── GRAMATICA/                 # Gramática del lenguaje
│   └── gramatica.txt          # Descripción detallada de la gramática en formato texto
├── SCRIPT(S) - EJEMPLO/       # Ejemplos de código DSL
│   └── ejemplo_completo.agro  # Archivo .agro con un programa de ejemplo
├── LINUX/                     # Fuentes para Linux (desarrollado en Ubuntu)
│   ├── transpilador/          # Backend del compilador
│   │   ├── lexer.l            # Analizador léxico
│   │   ├── parser.y           # Analizador sintáctico
│   │   ├── ast.h              # Árbol de sintaxis abstracta
│   │   ├── codegen.h          # Generador de código
│   │   ├── Makefile           # Makefile para compilación
│   │   ├── run_lexer.sh       # Validar léxico
│   │   ├── run_parser.sh      # Validar sintaxis
│   │   ├── run_codegen.sh     # Generar código
│   │   └── run_simulator.sh   # Ejecutar simulación
│   └── IDE-Agricultura/       # Frontend gráfico
│       ├── main.cpp           # Punto de entrada
│       ├── mainwindow.cpp/.h  # Ventana principal
│       ├── codeeditor.cpp/.h  # Editor de código
│       ├── highlighter.cpp/.h # Resaltado de sintaxis
│       ├── IDE-Agricultura.pro# Proyecto Qt
│       └── build/             # Archivos compilados (generados)
└── WINDOWS/                   # Fuentes y binarios para Windows
    ├── Generador de IDE y Transpilador/  # Fuentes para generar manualmente
    │   ├── transpilador/      # Similar a LINUX/transpilador, con .bat
    │   │   ├── lexer.l
    │   │   ├── parser.y
    │   │   ├── ast.h
    │   │   ├── codegen.h
    │   │   └── Makefile.win   # Makefile para Windows
    │   └── IDE/               # Similar a LINUX/IDE-Agricultura, con .bat
    │       ├── main.cpp
    │       ├── mainwindow.cpp/.h
    │       ├── codeeditor.cpp/.h
    │       ├── highlighter.cpp/.h
    │       ├── IDE-Agricultura.pro
    │       └── compile_ide.bat# Compilar IDE
    └── Listo para usar/       # Binarios precompilados para uso inmediato
        └── Iniciar-IDE.bat    # Script para lanzar el IDE
```

### Instalación en Linux (Ubuntu)
1. Instalar requisitos: `sudo apt-get install flex bison g++ make qt6-base-dev qt6-tools-dev`.
2. Compilar Transpilador: `cd LINUX/transpilador && make`.
3. Compilar IDE: `cd LINUX/IDE-Agricultura && qmake IDE-Agricultura.pro && make`.
4. Ejecutar: `cd LINUX/IDE-Agricultura/bin && ./IDE-Agricultura`.

### Instalación en Windows (Revisar antes documento de instrucciones incluido)
- **Opción 1: Generar manualmente** (usando carpeta "Generador de IDE y Transpilador"):
  1. Instalar MSYS2: Descargar de https://www.msys2.org/. Ejecutar: `pacman -Syu && pacman -S mingw-w64-x86_64-gcc flex bison make`.
  2. Instalar Qt: Descargar de https://www.qt.io/download (Qt 6.x con MinGW).
  3. Compilar Transpilador: `cd WINDOWS/Generador de IDE y Transpilador/transpilador && compile.bat`.
  4. Compilar IDE: `cd WINDOWS/Generador de IDE y Transpilador/IDE && compile_ide.bat`.
  5. Ver guía detallada: `docs/INSTALACION_WINDOWS.md`.

- **Opción 2: Listo para usar** (recomendado para principiantes):
  1. Ir a `WINDOWS/Listo para usar`.
  2. Ejecutar `Iniciar-IDE.bat` o directamente `IDE-Agricultura.exe`.
  3. Todo está precompilado; no necesitas instalar herramientas adicionales.

---

## 💻 Uso del IDE

### 1. Crear un Nuevo Programa
Abre el IDE, crea un archivo nuevo (Ctrl+N) y escribe código DSL. Ejemplo básico:
```dsl
INICIAR PROGRAMA
    LOTE invernadero1
        CULTIVO tomate
    
    VAR temp_actual : Temperatura
    VAR humedad_suelo : Humedad
    
    CONDICION temp_actual > 30
        RIEGO EN invernadero1 DURACION 15
    FIN_CONDICION
    
    CONDICION humedad_suelo < 40
        ACTIVAR riego_automatico
    FIN_CONDICION
FINALIZAR PROGRAMA
```

### 2. Guardar y Ejecutar
- **Guardar:** Ctrl+S o menú Archivo → Guardar.
- **Ejecutar:** F5 o botón "▶ Ejecutar".
- **Ver Resultados:**
  - Pestaña "Salida": Output del simulador con estructura jerárquica.
  - Pestaña "Log de Procesos": Detalles de transpilación/compilación.
  - Pestaña "Código C++": Código generado para inspección.
  - Panel de Errores: Muestra problemas en tiempo real.

El archivo de salida C++ se genera en la carpeta `transpilador` (o equivalente en tu plataforma).

### Interfaz del IDE
```
╔══════════════════════════════════════════════════════════════╗
║  IDE AGRICULTURA - EDITOR MULTI-PESTAÑA                      ║
╠══════════════════════════════════════════════════════════════╣
║  Archivo  Ayuda                                   [ ▶️ F5 ]  ║
╠══════════════════════════════════════════════════════════════╣
║                                                               ║
║  ┌─ EDITOR ──────────────────┐  ┌─ ERRORES ────────┐       ║
║  │ 1 | INICIAR               │  │ ⚡ VALIDACIÓN     │       ║
║  │ 2 |   CONST umbral = 40   │  │                  │       ║
║  │ 3 |                       │  │ ✅ Sin errores   │       ║
║  │ 4 |   LOTE "Inv" INICIAR  │  │ ✅ Sintaxis OK   │       ║
║  │ 5 |     ...               │  │                  │       ║
║  │ 6 |   FINALIZAR           │  └──────────────────┘       ║
║  │ 7 | FINALIZAR             │                             ║
║  └───────────────────────────┘                             ║
║                                                               ║
║  ┌─ PESTAÑAS DE SALIDA ───────────────────────────────┐    ║
║  │  ▶️ Salida  │  📋 Proceso  │  ⚙️ Código C++        │    ║
║  ├──────────────────────────────────────────────────────┤    ║
║  │ ╔════════════════════════════════════════╗          │    ║
║  │ ║ SISTEMA DE AGRICULTURA V3.1            ║          │    ║
║  │ ╚════════════════════════════════════════╝          │    ║
║  │ 📦 LOTE: Invernadero Principal                      │    ║
║  │   └─ 🌱 CULTIVO: Tomates Premium                    │    ║
║  │      ├─ ⚙️ EVALUANDO CONDICIÓN                      │    ║
║  │      │   📊 humedad < 40                            │    ║
║  │      │      → 35.2% ✓                               │    ║
║  │      └─ ✓ CONDICIÓN CUMPLIDA                        │    ║
║  │         └─ 💧 RIEGO                                  │    ║
║  └──────────────────────────────────────────────────────┘    ║
╠══════════════════════════════════════════════════════════════╣
║  ✓ Sin errores - Código válido | Línea: 5, Col: 12         ║
╚══════════════════════════════════════════════════════════════╝
```

### Colores del Resaltado de Sintaxis
| Elemento | Color | Ejemplo |
|----------|-------|---------|
| Palabras clave estructurales | 🔵 Azul | `INICIAR`, `FINALIZAR`, `LOTE` |
| Comandos/Acciones | 🟣 Magenta | `RIEGO`, `ACTIVAR`, `MONITOREAR` |
| Operadores lógicos | 🟠 Naranja | `Y`, `O`, `NO` |
| Tipos de datos | 🔷 Cyan | `Humedad`, `Temperatura`, `Ph` |
| Variables | 🟢 Verde claro | `humedad_suelo`, `temp_dia` |
| Constantes | 🟣 Morado | `UMBRAL_HUMEDAD`, `TEMP_MAX` |
| Strings | 🔴 Rojo | `"Zona_A"`, `"Sensor_1"` |
| Números | 🔵 Cian oscuro | `40`, `3.14`, `-10` |
| Operadores | 🟠 Naranja | `<`, `>`, `==`, `+`, `-` |
| Comentarios | ⚫ Gris | `// comentario`, `/* bloque */` |

### Atajos de Teclado
| Acción | Atajo | Descripción |
|--------|-------|-------------|
| Nuevo archivo | Ctrl+N | Crea nueva pestaña |
| Abrir | Ctrl+O | Abre archivo |
| Guardar | Ctrl+S | Guarda actual |
| Guardar Como | Ctrl+Shift+S | Guarda con nombre |
| Ejecutar | F5 | Transpila y ejecuta |
| Cerrar pestaña | Ctrl+W | Cierra actual |
| Salir | Ctrl+Q | Cierra IDE |

---

## 📖 Lenguaje DSL - Especificación Completa

### 🔤 Palabras Clave

#### Estructura del Programa:
```
INICIAR ... FINALIZAR    - Delimita el programa completo
LOTE ... INICIAR ... FINALIZAR - Define un lote de cultivo
CULTIVO ... INICIAR ... FINALIZAR - Define un cultivo específico
```

#### Declaraciones:
```
VAR nombre: Tipo          - Declara una variable
CONST nombre = valor      - Declara una constante
DISPOSITIVO               - Registra un dispositivo
IP ... PUERTO ...         - Dispositivo de red
SERIAL ...                - Dispositivo serial
```

#### Control de Flujo:
```
CONDICION SI ... ENTONCES ... FIN_CONDICION
CONDICION SI ... ENTONCES ... SINO ... FIN_CONDICION
CONDICION SI ... ENTONCES ... SINO_SI ... ENTONCES ... FIN_CONDICION
```

#### Operadores Lógicos:
```
Y     - AND lógico
O     - OR lógico
NO    - NOT lógico
()    - Agrupación/Prioridad
```

#### Operadores de Comparación:
```
<     - Menor que
>     - Mayor que
<=    - Menor o igual
>=    - Mayor o igual
==    - Igual a
```

#### Operadores Matemáticos:
```
+     - Suma
-     - Resta
*     - Multiplicación
/     - División
%     - Módulo
```

#### Acciones:
```
RIEGO "sector" DURACION valor
RIEGO_AVANZADO "sector" CAUDAL valor DURACION valor
ACTIVAR "dispositivo" DURACION valor
FERTILIZACION TIPO "tipo" CANTIDAD valor
MONITOREAR variable CADA n HORAS
REPORTE "título"
ENVIAR_ALERTA "mensaje"
CALCULAR variable = expresión
VINCULAR variable A "dispositivo"
```

#### Tipos de Datos:
```
Humedad       - Porcentaje de humedad (0-100%)
Temperatura   - Temperatura en grados Celsius
Ph            - Nivel de pH (0-14)
Luz           - Intensidad lumínica
Co2           - Nivel de CO2
Presion       - Presión atmosférica
Viento        - Velocidad del viento
Numero        - Número genérico (float)
```

### 💡 Ejemplos por Categoría

#### 1. Declaración de Variables y Constantes
```
// Constantes globales
CONST umbral_humedad = 40
CONST temperatura_optima = 22
CONST duracion_riego = 30

// Variables
VAR humedad_suelo: Humedad
VAR temperatura: Temperatura
VAR ph_actual: Ph
VAR nivel_agua: Numero
```

#### 2. Registro de Dispositivos
```
// Dispositivos IP
DISPOSITIVO "Sensor_Humedad_1" IP "192.168.1.10" PUERTO 8080
DISPOSITIVO "Bomba_Riego" IP "192.168.1.20" PUERTO 9090

// Dispositivos Serial
DISPOSITIVO "Sensor_pH" SERIAL "/dev/ttyUSB0"
DISPOSITIVO "Estacion_Meteo" SERIAL "/dev/ttyUSB1"
```

#### 3. Vinculación de Variables
```
VINCULAR humedad_suelo A "Sensor_Humedad_1"
VINCULAR temperatura A "Estacion_Meteo"
VINCULAR ph_actual A "Sensor_pH"
```

#### 4. Cálculos Matemáticos
```
// Operaciones simples
CALCULAR promedio = (temp_dia + temp_noche) / 2

// Operaciones complejas
CALCULAR indice_estres = ((100 - humedad) * 0.4) + ((temp - 22) * 0.6)

// Con constantes
CALCULAR deficit = umbral_humedad - humedad_actual
```

#### 5. Condiciones Simples
```
// Condición básica
CONDICION SI humedad_suelo < 30 ENTONCES
    RIEGO "Zona_A" DURACION 20
    ENVIAR_ALERTA "Riego activado"
FIN_CONDICION

// Con constante
CONDICION SI temperatura > temperatura_optima ENTONCES
    ACTIVAR "Ventilador" DURACION 60
FIN_CONDICION
```

#### 6. Condiciones con SINO
```
CONDICION SI temperatura > 35 ENTONCES
    ACTIVAR "Ventilador" DURACION 120
    ENVIAR_ALERTA "Temperatura alta"
SINO
    ENVIAR_ALERTA "Temperatura normal"
FIN_CONDICION
```

#### 7. Condiciones con SINO_SI
```
CONDICION SI ph_actual < 6.0 ENTONCES
    FERTILIZACION TIPO "Caliza" CANTIDAD 20
    ENVIAR_ALERTA "Corrigiendo pH bajo"
SINO_SI ph_actual > 7.5 ENTONCES
    FERTILIZACION TIPO "Azufre" CANTIDAD 15
    ENVIAR_ALERTA "Corrigiendo pH alto"
SINO
    ENVIAR_ALERTA "pH óptimo"
FIN_CONDICION
```

#### 8. Expresiones Lógicas con Y
```
CONDICION SI humedad < 30 Y temperatura > 35 ENTONCES
    RIEGO "Zona_Critica" DURACION 40
    ACTIVAR "Ventilador" DURACION 120
    ENVIAR_ALERTA "Emergencia: calor y sequía"
FIN_CONDICION
```

#### 9. Expresiones Lógicas con O
```
CONDICION SI humedad < 20 O temperatura > 40 ENTONCES
    ENVIAR_ALERTA "Condición crítica detectada"
    RIEGO "Todas_Zonas" DURACION 60
FIN_CONDICION
```

#### 10. Expresiones Lógicas con NO
```
CONDICION SI NO (humedad > 80) ENTONCES
    ENVIAR_ALERTA "Humedad no excesiva"
    FERTILIZACION TIPO "NPK" CANTIDAD 25
FIN_CONDICION
```

#### 11. Expresiones Complejas Anidadas
```
// Ejemplo: (A Y B) O (C Y D)
CONDICION SI (humedad < 30 Y temperatura > 35) O (lluvia == 0 Y viento < 20) ENTONCES
    RIEGO_AVANZADO "Zona_Especial" CAUDAL 15.5 DURACION 45
    ENVIAR_ALERTA "Condición compleja detectada"
FIN_CONDICION
```

#### 12. Expresiones con NO Anidado
```
// Ejemplo: A Y NO(B O C)
CONDICION SI humedad < 40 Y NO (temperatura > 40 O lluvia > 0) ENTONCES
    RIEGO "Zona_A" DURACION 30
FIN_CONDICION
```

#### 13. Riego Avanzado
```
// Con valores literales
RIEGO_AVANZADO "Zona_Premium" CAUDAL 12.5 DURACION 30

// Con constantes
RIEGO_AVANZADO "Zona_B" CAUDAL caudal_bajo DURACION duracion_media
```

#### 14. Monitoreo Continuo
```
MONITOREAR humedad_suelo CADA 1 HORAS
MONITOREAR temperatura CADA 2 HORAS
MONITOREAR ph_actual CADA 6 HORAS
```

#### 15. Reportes
```
REPORTE "Estado completo del invernadero"
REPORTE "Análisis diario de cultivo"
```

#### 16. Control de Riego Básico
```dsl
INICIAR PROGRAMA
    LOTE campo_norte
        CULTIVO maiz
    
    VAR sensor_humedad : Humedad
    
    MONITOREAR sensor_humedad CADA 2 HORAS
    
    CONDICION sensor_humedad < 50
        RIEGO EN campo_norte DURACION 20
    FIN_CONDICION
FINALIZAR PROGRAMA
```

#### 17. Sistema IoT con Alertas
```dsl
INICIAR PROGRAMA
    LOTE invernadero_a
        CULTIVO fresa
    
    DISPOSITIVO controlador1 IP "192.168.1.100" PUERTO 8080
    SENSOR temp1 : Temperatura
    ACTUADOR valvula_riego : Valvula
    
    UBICAR_SENSOR temp1 EN controlador1
    UBICAR_ACTUADOR valvula_riego EN controlador1
    VINCULAR temp1 A invernadero_a
    
    CONDICION temp1 > 35
        ALERTA critica
            ENVIAR_ALERTA "Temperatura crítica" A "admin@farm.com"
            ACTIVAR valvula_riego
        FIN_ALERTA
    FIN_CONDICION
FINALIZAR PROGRAMA
```

#### 18. Programa Completo de Ejemplo
```
INICIAR
  // ========== CONSTANTES ==========
  CONST umbral_humedad = 40
  CONST temperatura_max = 35
  CONST ph_min = 6.0
  CONST ph_max = 7.5
  
  // ========== LOTE ==========
  LOTE "Invernadero Principal" INICIAR
      
      // ========== CULTIVO ==========
      CULTIVO "Tomates Premium" INICIAR
          
          // Variables
          VAR humedad_suelo: Humedad
          VAR temperatura_dia: Temperatura
          VAR ph_suelo: Ph
          VAR promedio_temp: Temperatura
          
          // Dispositivos
          DISPOSITIVO "Sensor_Hum_1" IP "192.168.1.10" PUERTO 8080
          DISPOSITIVO "Sensor_Temp_1" IP "192.168.1.11" PUERTO 8080
          DISPOSITIVO "Sensor_pH_1" SERIAL "/dev/ttyUSB0"
          DISPOSITIVO "Bomba_Riego_1" IP "192.168.1.20" PUERTO 9090
          
          // Vinculaciones
          VINCULAR humedad_suelo A "Sensor_Hum_1"
          VINCULAR temperatura_dia A "Sensor_Temp_1"
          VINCULAR ph_suelo A "Sensor_pH_1"
          
          // Cálculos
          CALCULAR promedio_temp = (temperatura_dia + 18) / 2
          
          // Control de Riego
          CONDICION SI humedad_suelo < umbral_humedad ENTONCES
              RIEGO "Zona_A" DURACION 30
              ENVIAR_ALERTA "Riego activado"
          FIN_CONDICION
          
          // Control de Temperatura
          CONDICION SI temperatura_dia > temperatura_max ENTONCES
              ACTIVAR "Ventilador" DURACION 120
              ENVIAR_ALERTA "Ventilación activada"
          FIN_CONDICION
          
          // Control de pH
          CONDICION SI ph_suelo < ph_min ENTONCES
              FERTILIZACION TIPO "Caliza" CANTIDAD 20
              ENVIAR_ALERTA "Corrigiendo pH bajo"
          SINO_SI ph_suelo > ph_max ENTONCES
              FERTILIZACION TIPO "Azufre" CANTIDAD 15
              ENVIAR_ALERTA "Corrigiendo pH alto"
          SINO
              ENVIAR_ALERTA "pH óptimo"
          FIN_CONDICION
          
          // Condición Compleja
          CONDICION SI (humedad_suelo < 30 Y temperatura_dia > 35) O NO (ph_suelo >= ph_min Y ph_suelo <= ph_max) ENTONCES
              RIEGO_AVANZADO "Zona_Critica" CAUDAL 15.5 DURACION 45
              ACTIVAR "Ventilador" DURACION 180
              ENVIAR_ALERTA "EMERGENCIA: Múltiples condiciones críticas"
          FIN_CONDICION
          
          // Monitoreo
          MONITOREAR humedad_suelo CADA 1 HORAS
          MONITOREAR temperatura_dia CADA 2 HORAS
          MONITOREAR ph_suelo CADA 6 HORAS
          
          // Reporte
          REPORTE "Estado completo de Tomates Premium"
          
      FINALIZAR
  FINALIZAR
FINALIZAR
```

Ver más ejemplos en `SCRIPT(S) - EJEMPLO/`.

### 🎨 Visualización de Salida

#### Ejemplo de Expresión Simple:
```
├─ ⚙️  EVALUANDO CONDICIÓN
       📊 humedad < 30
          → 25.3% ✓
│
└─ ✓ CONDICIÓN CUMPLIDA
       ├─ 💧 RIEGO
       │   • Sector: Zona_A
       │   • Duración: 30 min
       └─ 🚨 ALERTA: Riego activado
```

#### Ejemplo de Expresión Compleja:
```
├─ ⚙️  EVALUANDO CONDICIÓN
       🔗 O (OR)
          🔗 Y (AND)
           [→ 192.168.1.10:8080]
             📊 humedad < 30
                → 25.2% ✓
           [→ 192.168.1.11:8080]
             📊 temperatura > 35
                → 38.5°C ✓
          🔗 NO (NOT)
             🔗 Y (AND)
              [→ /dev/ttyUSB0]
                📊 ph >= 6.0
                   → 5.2 pH ✗
                📊 ph <= 7.5
                   → 5.2 pH ✓
│
└─ ✓ CONDICIÓN CUMPLIDA
       ├─ 💧 RIEGO AVANZADO
       │   • Sector: Zona_Critica
       │   • Duración: 45 min
       │   • Caudal: 15.5 L/min
       ├─ ⚡ ACTIVACIÓN
       │   • Actuador: Ventilador
       │   • Tiempo: 180 min
       └─ 🚨 ALERTA: EMERGENCIA: Múltiples condiciones críticas
```

---

---

## 🐛 Solución de Problemas

### Error: "flex no reconocido" (Windows)
**Solución:** Agrega `C:\msys64\usr\bin` al PATH.

### Error: "qmake no reconocido" (Windows)
**Solución:** Agrega `C:\Qt\6.x.x\mingw_64\bin` al PATH.

### Error: "No se encuentra transpilador.exe" (Windows)
**Solución:** Verifica estructura de carpetas y compila primero.

### IDE no ejecuta programas
**Solución:** Asegúrate de que `transpilador` existe en la ruta relativa (`../transpilador/`).

### Problema: El IDE no encuentra el transpilador (Linux/Windows)
**Solución:** En `mainwindow.cpp`, ajusta `transpiladorPath` a la ruta absoluta correcta.

### Flex/Bison no encontrados (Linux)
**Solución:** `sudo apt-get install flex bison`.

### Errores de compilación de Qt (Linux)
**Solución:** Verifica `qmake6 --version` e instala `qt6-base-dev`.

📖 **Más soluciones:** [`docs/INSTALACION_WINDOWS.md#solución-de-problemas`](docs/INSTALACION_WINDOWS.md) y [`docs/INSTALACION_LINUX.md`](docs/INSTALACION_LINUX.md).

---

## 📊 Arquitectura del Sistema

```
┌─────────────────────────────────────────────────────────────┐
│                        USUARIO                              │
└────────────┬────────────────────────────┬───────────────────┘
             │                            │
             ▼                            ▼
    ┌─────────────────┐         ┌──────────────────┐
    │   IDE (Qt GUI)  │         │  Línea Comandos  │
    │  ┌───────────┐  │         │   ./transpilador │
    │  │  Editor   │  │         └──────────────────┘
    │  │  Multi-   │  │                 │
    │  │  Pestaña  │  │                 │
    │  └───────────┘  │                 │
    │  ┌───────────┐  │                 │
    │  │Validación │  │                 │
    │  │ Tiempo    │  │                 │
    │  │  Real     │  │                 │
    │  └───────────┘  │                 │
    └────────┬────────┘                 │
             │                          │
             ▼                          ▼
    ┌──────────────────────────────────────────┐
    │         TRANSPILADOR (Backend)           │
    │  ┌────────────┐  ┌─────────────────┐    │
    │  │   LEXER    │→ │     PARSER      │    │
    │  │  (Flex)    │  │    (Bison)      │    │
    │  │ Tokeniza   │  │  Construye AST  │    │
    │  └────────────┘  └─────────────────┘    │
    │                          ↓               │
    │                  ┌─────────────────┐    │
    │                  │   CODEGEN       │    │
    │                  │ Genera C++      │    │
    │                  └─────────────────┘    │
    └───────────────────────┬──────────────────┘
                            │
                            ▼
                   ┌─────────────────┐
                   │  salida.cpp     │
                   └────────┬─────────┘
                            │
                            ▼ (g++)
                   ┌─────────────────┐
                   │   SIMULADOR     │
                   │  (Ejecutable)   │
                   └────────┬─────────┘
                            │
                            ▼
                  ┌──────────────────────┐
                  │  SALIDA VISUAL       │
                  │  • Estructura árbol  │
                  │  • Emojis y colores  │
                  │  • Jerarquía clara   │
                  └──────────────────────┘
```

---

## 🔧 Desarrollo y Extensión

### Agregar Nuevas Palabras Clave
1. En `lexer.l`: Agrega token.
2. En `parser.y`: Agrega regla gramatical.
3. En `ast.h`: Agrega tipo de nodo.
4. En `codegen.h`: Genera código C++.
5. En `highlighter.cpp`: Agrega patrón de resaltado.

### Agregar Nuevos Tipos de Datos
- Actualiza `highlighter.cpp` para resaltado.
- Actualiza `codegen.h` para generación de valores aleatorios.

---

## 🧪 Testing y Validación

### Test 1: Expresión Simple
```bash
echo "INICIAR
  VAR h: Humedad
  DISPOSITIVO \"S1\" IP \"192.168.1.10\" PUERTO 8080
  VINCULAR h A \"S1\"
  CONDICION SI h < 30 ENTONCES
    ENVIAR_ALERTA \"Baja humedad\"
  FIN_CONDICION
FINALIZAR" > test1.agro

./transpilador test1.agro && g++ salida.cpp -o simulador && ./simulador
```

Usa el IDE para tests interactivos.

---

## 📈 Roadmap Futuro

### Versión 4.0
- Depurador integrado con breakpoints.
- Autocompletado inteligente y snippets.
- Integración con Git.

### Versión 5.0
- Soporte para sensores y dispositivos reales (IoT físico).
- Dashboard web de monitoreo.
- Base de datos de históricos.
- Notificaciones push y app móvil.

---

## 🤝 Contribuir

Las contribuciones son bienvenidas:

1. Fork el proyecto.
2. Crea una rama (`git checkout -b feature/NuevaFuncionalidad`).
3. Commit (`git commit -m 'Agregar nueva funcionalidad'`).
4. Push (`git push origin feature/NuevaFuncionalidad`).
5. Abre un Pull Request.

Áreas: Bugs, features, docs, UI, optimizaciones, tests.

---

## 📄 Licencia

Este proyecto está bajo la Licencia GNU. Ver archivo `LICENSE` para más detalles.

---

## 👥 Autores

- **Johan Felipe Silva Cavieles** - *Desarrollo de IDE y Parser* - [FeelingMoon](https://github.com/FeelingMoon)
- **Juan Esteban Oyola Galindo** - *Desarrollador del Lexer y Tester* - [JuanOyolaGalindo](https://github.com/JuanOyolaGalindo)

---

## 🙏 Agradecimientos

- Comunidad de MSYS2.
- Equipo de Qt.
- Documentación de Flex y Bison.
- Comunidad C++.

---

## 📧 Contacto

- **Email:** contacto@ejemplo.com
- **GitHub:** https://github.com/tuusuario/agricultura-dsl
- **Issues:** https://github.com/tuusuario/agricultura-dsl/issues

---

## 🔄 Changelog

### v3.1 - Multiplataforma (2025-11-03)
- ✨ Unificación de Windows y Linux.
- ✨ IDE mejorado con validación real-time.
- ✨ Soporte completo para expresiones complejas.
- 🐛 Correcciones de bugs.

### v2.0.0 - Windows Edition (2025-11-03)
- ✨ Port a Windows.
- ✨ Scripts .bat.
- ✨ Soporte IoT.

### v1.0.0 (2025-09-15)
- 🎉 Versión inicial para Linux.

---

**¡Feliz automatización agrícola! 🌾🚜**
