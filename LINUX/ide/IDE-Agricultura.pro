QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Definir nombre del ejecutable
TARGET = IDE-Agricultura
TEMPLATE = app

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

# Configuración de compilación
QMAKE_CXXFLAGS += -Wall -Wextra

# Directorio de salida
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build
UI_DIR = build

# Default rules for deployment
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
