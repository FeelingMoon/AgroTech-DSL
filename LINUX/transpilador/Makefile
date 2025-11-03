# Makefile para Transpilador DSL Agricultura V2.0 (IoT)

CC = g++
CFLAGS = -std=c++11 -Wall
FLEX = flex
BISON = bison

# Archivos fuente
LEXER = lexer.l
PARSER = parser.y

# Archivos generados
LEX_OUTPUT = lex.yy.c
PARSER_OUTPUT = parser.tab.c
PARSER_HEADER = parser.tab.h

# Ejecutable
TARGET = transpilador

# Archivos objeto
OBJECTS = $(LEX_OUTPUT) $(PARSER_OUTPUT)

# Regla principal
all: $(TARGET)

# Compilar el transpilador
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) -lfl
	@echo "✓ Transpilador compilado exitosamente"
	@echo "  Uso: ./$(TARGET) archivo.agro"

# Generar lexer
$(LEX_OUTPUT): $(LEXER)
	$(FLEX) $(LEXER)
	@echo "✓ Lexer generado"

# Generar parser
$(PARSER_OUTPUT) $(PARSER_HEADER): $(PARSER)
	$(BISON) -d $(PARSER)
	@echo "✓ Parser generado"

# Probar con el ejemplo IoT
test: $(TARGET)
	@echo ""
	@echo "╔═══════════════════════════════════════╗"
	@echo "║  Probando con ejemplo_iot.agro        ║"
	@echo "╚═══════════════════════════════════════╝"
	@echo ""
	./$(TARGET) ejemplo_iot.agro
	@echo ""
	@echo "╔═══════════════════════════════════════╗"
	@echo "║  Compilando C++ generado              ║"
	@echo "╚═══════════════════════════════════════╝"
	@echo ""
	$(CC) salida.cpp -o simulador
	@echo ""
	@echo "✓ Todo compilado. Ejecuta: ./simulador"

# Ejecutar simulador
run: test
	@echo ""
	@echo "╔═══════════════════════════════════════╗"
	@echo "║  Ejecutando Simulación                ║"
	@echo "╚═══════════════════════════════════════╝"
	@echo ""
	./simulador

# Limpiar archivos generados
clean:
	rm -f $(LEX_OUTPUT) $(PARSER_OUTPUT) $(PARSER_HEADER)
	rm -f $(TARGET) simulador salida.cpp
	rm -f *.o *~
	@echo "✓ Archivos limpiados"

# Limpiar todo incluyendo outputs de compilación
distclean: clean
	rm -f *.output
	@echo "✓ Limpieza completa"

# Información del proyecto
info:
	@echo "╔════════════════════════════════════════════════╗"
	@echo "║  DSL Agricultura - Transpilador IoT V2.0       ║"
	@echo "╚════════════════════════════════════════════════╝"
	@echo ""
	@echo "Archivos principales:"
	@echo "  - lexer.l      : Analizador léxico"
	@echo "  - parser.y     : Analizador sintáctico"
	@echo "  - ast.h        : Definiciones del AST"
	@echo "  - codegen.h    : Generador de código C++"
	@echo ""
	@echo "Comandos disponibles:"
	@echo "  make           : Compilar transpilador"
	@echo "  make test      : Probar con ejemplo_iot.agro"
	@echo "  make run       : Ejecutar simulación completa"
	@echo "  make clean     : Limpiar archivos generados"
	@echo "  make info      : Mostrar esta información"
	@echo ""

# Instalar dependencias (Ubuntu/Debian)
install-deps:
	@echo "Instalando dependencias..."
	sudo apt-get update
	sudo apt-get install -y flex bison g++ make
	@echo "✓ Dependencias instaladas"

.PHONY: all test run clean distclean info install-deps
