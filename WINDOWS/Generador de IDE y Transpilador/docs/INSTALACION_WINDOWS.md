# 🪟 Guía de Instalación - DSL Agricultura para Windows

## 📋 Tabla de Contenidos
1. [Requisitos Previos](#requisitos-previos)
2. [Instalación de MSYS2](#instalación-de-msys2)
3. [Instalación de Qt](#instalación-de-qt)
4. [Solución de Problemas](#solución-de-problemas)

---

## 🔧 Requisitos Previos

### Hardware Mínimo
- **RAM**: 4 GB (8 GB recomendado)
- **Espacio en Disco**: 5 GB libres
- **Procesador**: Dual-core o superior

### Software
- **Windows 10** o superior (64 bits)
- Conexión a Internet para descargar herramientas

---

## 📥 Instalación de MSYS2

MSYS2 proporciona las herramientas de compilación necesarias (Flex, Bison, GCC).

### Paso 1: Descargar MSYS2
1. Visita: https://www.msys2.org/
2. Descarga el instalador: `msys2-x86_64-xxxxxxxx.exe`
3. Ejecuta el instalador
4. Instala en la ruta por defecto: `C:\msys64`

### Paso 2: Configurar MSYS2
1. Al finalizar la instalación, se abrirá una terminal MSYS2
2. Ejecuta estos comandos para actualizar el sistema:

```bash
pacman -Syu
```

3. Si se cierra la terminal, ábrela de nuevo desde:
   - `C:\msys64\msys2.exe`

4. Ejecuta nuevamente:
```bash
pacman -Su
```

### Paso 3: Instalar Herramientas de Compilación

```bash
pacman -S mingw-w64-x86_64-gcc
pacman -S flex
pacman -S bison
pacman -S make
```

### Paso 4: Agregar MSYS2 al PATH de Windows

1. **Abre Configuración del Sistema:**
   - Presiona `Win + X`
   - Selecciona "Sistema"
   - Click en "Configuración avanzada del sistema"
   - Click en "Variables de entorno"

2. **Editar PATH:**
   - En "Variables del sistema", busca `Path`
   - Click en "Editar"
   - Click en "Nuevo"
   - Agrega: `C:\msys64\mingw64\bin`
   - Agrega: `C:\msys64\usr\bin`
   - Click "Aceptar" en todos los diálogos

3. **Verificar:**
   - Abre un **nuevo** símbolo del sistema (CMD)
   - Ejecuta:
   ```cmd
   gcc --version
   flex --version
   bison --version
   ```
   - Deberías ver las versiones instaladas

---

## 🎨 Instalación de Qt

Qt es necesario para compilar el IDE con interfaz gráfica.

### Paso 1: Descargar Qt

1. Visita: https://www.qt.io/download-open-source
2. Descarga el instalador online: `qt-online-installer-windows-x64-x.x.x.exe`

### Paso 2: Instalar Qt

1. Ejecuta el instalador
2. Crea una cuenta Qt (gratuita) si no tienes
3. En "Select Components", instala:
   - ✅ **Qt 6.x for Desktop**
     - MinGW 11.x.x 64-bit
     - Qt Creator (opcional pero recomendado)
   - ✅ **Developer and Designer Tools**
     - MinGW 11.x.x 64-bit

4. Ruta de instalación sugerida: `C:\Qt`

### Paso 3: Agregar Qt al PATH

1. Abre Variables de entorno (igual que en Paso 4 de MSYS2)
2. Agrega al PATH:
   - `C:\Qt\6.x.x\mingw_64\bin`
   - `C:\Qt\Tools\mingw1120_64\bin`

3. Verifica en un **nuevo** CMD:
   ```cmd
   qmake --version
   ```

---

## 📞 Soporte

Si encuentras problemas:

1. **Revisa los logs** en el panel de procesos del IDE
2. **Verifica las versiones**:
   ```cmd
   gcc --version     # Debe ser 11.x o superior
   qmake --version   # Debe ser Qt 6.x
   flex --version    # Debe ser 2.6.x
   bison --version   # Debe ser 3.x
   ```
3. **Consulta documentación oficial**:
   - MSYS2: https://www.msys2.org/docs/
   - Qt: https://doc.qt.io/

---

## ✨ ¡Listo!

Tu entorno de desarrollo DSL Agricultura está configurado en Windows.

**Siguiente paso:** Comienza a programar en tu lenguaje DSL y deja que el IDE se encargue del resto.

---

*Última actualización: 2025*
*Versión: 2.0 - Windows Edition*
