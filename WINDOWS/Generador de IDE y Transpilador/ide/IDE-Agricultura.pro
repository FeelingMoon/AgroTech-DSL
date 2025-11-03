QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Definir nombre del ejecutable
TARGET = IDE-Agricultura
TEMPLATE = app

# ====================================
# CONFIGURACION PARA WINDOWS
# ====================================
win32 {
    # Icono de la aplicacion (opcional)
    # RC_ICONS = resources/app_icon.ico
    
    # Configuracion de release para distribucion
    CONFIG(release, debug|release) {
        # Optimizaciones
        QMAKE_CXXFLAGS_RELEASE += -O2
        
        # No mostrar consola en release
        CONFIG += windows
    }
    
    # Configuracion de debug
    CONFIG(debug, debug|release) {
        # Mostrar consola para debug
        CONFIG += console
    }
}

# Archivos del proyecto
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    codeeditor.cpp \
    highlighter.cpp

HEADERS += \
    mainwindow.h \
    codeeditor.h \
    highlighter.h

# Configuracion de compilacion
QMAKE_CXXFLAGS += -Wall -Wextra

# Directorios de salida
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build
UI_DIR = build

# ====================================
# CONFIGURACION DE PATHS
# ====================================

# Ruta al transpilador (relativa al ejecutable del IDE)
# En Windows, el IDE buscara el transpilador en ../transpilador/
# Estructura recomendada:
#   Agricultura-DSL/
#   ├── IDE/
#   │   └── bin/
#   │       └── IDE-Agricultura.exe
#   └── transpilador/
#       └── transpilador.exe

# Informacion de la aplicacion
VERSION = 2.0.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
