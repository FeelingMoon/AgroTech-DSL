%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "codegen.h"

extern int yylex();
extern int yylineno;
extern FILE* yyin;
void yyerror(const char* s);

ASTNode* root = NULL;
%}

%union {
    double num;
    char* str;
    struct ASTNode* node;
}

%token INICIAR FINALIZAR CULTIVO LOTE
%token VAR CONST DISPOSITIVO IP PUERTO SERIAL
%token SENSOR ACTUADOR UBICAR_DISPOSITIVO UBICAR_SENSOR UBICAR_ACTUADOR VINCULAR
%token CONDICION FIN_CONDICION RIEGO RIEGO_AVANZADO ACTIVAR DURACION CAUDAL
%token FERTILIZACION TIPO CANTIDAD MONITOREAR CADA HORAS
%token TAREA EJECUTAR REPORTE ALERTA FIN_ALERTA ENVIAR_ALERTA
%token SI ENTONCES SINO SINO_SI EN A DOS_PUNTOS CALCULAR ASIGNAR
%token MENOR MAYOR MENOR_IGUAL MAYOR_IGUAL IGUAL
%token Y O NO
%token MAS MENOS MULTIPLICAR DIVIDIR MODULO
%token PAREN_IZQ PAREN_DER

%token <num> NUMERO
%token <str> IDENTIFICADOR STRING TIPO_DATO

%type <node> Programa Lotes Lote Cultivos Cultivo Declaraciones Declaracion
%type <node> VarDef ConstDef DispositivoDef SensorDef ActuadorDef
%type <node> Ubicacion Vinculacion Condicion
%type <node> Accion RiegoAvanzado ActivarActuador Fertilizacion Monitoreo Tarea Reporte
%type <node> Alerta EnviarAlerta Expresion ExprLogica
%type <node> Calcular ExprMat
%type <str> Comparador

/* Precedencia de operadores lógicos */
%left O
%left Y
%right NO

/* Precedencia de operadores matemáticos (de menor a mayor) */
%left MAS MENOS
%left MULTIPLICAR DIVIDIR MODULO
%left PAREN_IZQ PAREN_DER

%%

Programa:
    INICIAR Declaraciones Lotes FINALIZAR {
        root = createNode(NODE_PROGRAMA);
        root->children[0] = $2;  // Declaraciones globales
        root->children[1] = $3;  // Lotes
        printf("✓ Análisis sintáctico completado\n");
    }
    | INICIAR Lotes FINALIZAR {
        root = createNode(NODE_PROGRAMA);
        root->children[0] = $2;
        printf("✓ Análisis sintáctico completado\n");
    }
    ;

Lotes:
    Lote Lotes {
        $$ = createNode(NODE_LOTES);
        $$->children[0] = $1;
        $$->children[1] = $2;
    }
    | /* epsilon */ {
        $$ = NULL;
    }
    ;

Lote:
    LOTE STRING INICIAR Cultivos FINALIZAR {
        $$ = createNode(NODE_LOTE);
        $$->str_value = $2;
        $$->children[0] = $4;
    }
    ;

Cultivos:
    Cultivo Cultivos {
        $$ = createNode(NODE_CULTIVOS);
        $$->children[0] = $1;
        $$->children[1] = $2;
    }
    | /* epsilon */ {
        $$ = NULL;
    }
    ;

Cultivo:
    CULTIVO STRING INICIAR Declaraciones FINALIZAR {
        $$ = createNode(NODE_CULTIVO);
        $$->str_value = $2;
        $$->children[0] = $4;
    }
    ;

Declaraciones:
    Declaracion Declaraciones {
        $$ = createNode(NODE_DECLARACIONES);
        $$->children[0] = $1;
        $$->children[1] = $2;
    }
    | /* epsilon */ {
        $$ = NULL;
    }
    ;

Declaracion:
    VarDef { $$ = $1; }
    | ConstDef { $$ = $1; }
    | DispositivoDef { $$ = $1; }
    | SensorDef { $$ = $1; }
    | ActuadorDef { $$ = $1; }
    | Ubicacion { $$ = $1; }
    | Vinculacion { $$ = $1; }
    | Condicion { $$ = $1; }
    | Accion { $$ = $1; }
    | RiegoAvanzado { $$ = $1; }
    | ActivarActuador { $$ = $1; }
    | Fertilizacion { $$ = $1; }
    | Monitoreo { $$ = $1; }
    | Tarea { $$ = $1; }
    | Reporte { $$ = $1; }
    | Alerta { $$ = $1; }
    | EnviarAlerta { $$ = $1; }
    | Calcular { $$ = $1; }
    ;

/* Nueva: Declaración de variables */
VarDef:
    VAR IDENTIFICADOR DOS_PUNTOS TIPO_DATO {
        $$ = createNode(NODE_VAR);
        $$->str_value = $2;   // nombre de la variable (humedad_fresas)
        $$->str_value2 = $4;  // tipo con mayúscula (Humedad, Temperatura, Numero)
    }
    | VAR IDENTIFICADOR DOS_PUNTOS IDENTIFICADOR {
        $$ = createNode(NODE_VAR);
        $$->str_value = $2;   // nombre de la variable
        $$->str_value2 = $4;  // tipo en minúscula (para compatibilidad)
    }
    ;

/* Nueva: Declaración de constantes */
ConstDef:
    CONST IDENTIFICADOR ASIGNAR NUMERO {
        $$ = createNode(NODE_CONST);
        $$->str_value = $2;   // nombre de la constante
        $$->num_value = $4;   // valor numérico
    }
    | CONST IDENTIFICADOR ASIGNAR IDENTIFICADOR {
        $$ = createNode(NODE_CONST);
        $$->str_value = $2;   // nombre de la constante
        $$->str_value2 = $4;  // referencia a otra constante
    }
    ;

/* Nueva: Declaración de dispositivos físicos */
DispositivoDef:
    DISPOSITIVO STRING IP STRING PUERTO NUMERO {
        $$ = createNode(NODE_DISPOSITIVO_IP);
        $$->str_value = $2;   // ID del dispositivo ("Sensor_001")
        $$->str_value2 = $4;  // Dirección IP ("192.168.1.100")
        $$->num_value = $6;   // Puerto (8080)
    }
    | DISPOSITIVO STRING SERIAL STRING {
        $$ = createNode(NODE_DISPOSITIVO_SERIAL);
        $$->str_value = $2;   // ID del dispositivo
        $$->str_value2 = $4;  // Puerto serial ("/dev/ttyUSB0")
    }
    | DISPOSITIVO STRING {
        $$ = createNode(NODE_DISPOSITIVO);
        $$->str_value = $2;   // ID simple del dispositivo
    }
    ;

/* Mantener compatibilidad con sintaxis antigua */
SensorDef:
    SENSOR TIPO_DATO STRING {
        $$ = createNode(NODE_SENSOR);
        $$->str_value = $2;  // Tipo con mayúscula (Humedad)
        $$->str_value2 = $3;
    }
    | SENSOR IDENTIFICADOR STRING {
        $$ = createNode(NODE_SENSOR);
        $$->str_value = $2;  // tipo en minúscula (humedad) - compatibilidad
        $$->str_value2 = $3;
    }
    ;

ActuadorDef:
    ACTUADOR TIPO_DATO STRING {
        $$ = createNode(NODE_ACTUADOR);
        $$->str_value = $2;  // Tipo con mayúscula
        $$->str_value2 = $3;
    }
    | ACTUADOR IDENTIFICADOR STRING {
        $$ = createNode(NODE_ACTUADOR);
        $$->str_value = $2;  // tipo minúscula - compatibilidad
        $$->str_value2 = $3;
    }
    ;

Ubicacion:
    UBICAR_DISPOSITIVO STRING EN STRING {
        $$ = createNode(NODE_UBICAR_DISPOSITIVO);
        $$->str_value = $2;
        $$->str_value2 = $4;
    }
    | UBICAR_SENSOR STRING EN STRING {
        $$ = createNode(NODE_UBICAR_SENSOR);
        $$->str_value = $2;
        $$->str_value2 = $4;
    }
    | UBICAR_ACTUADOR STRING EN STRING {
        $$ = createNode(NODE_UBICAR_ACTUADOR);
        $$->str_value = $2;
        $$->str_value2 = $4;
    }
    ;

Vinculacion:
    VINCULAR IDENTIFICADOR A STRING {
        $$ = createNode(NODE_VINCULAR);
        $$->str_value = $2;   // nombre de variable (humedad_fresas)
        $$->str_value2 = $4;  // ID del dispositivo ("Sensor_001")
    }
    ;

Condicion:
    CONDICION SI ExprLogica ENTONCES Declaraciones FIN_CONDICION {
        $$ = createNode(NODE_CONDICION);
        $$->children[0] = $3;  // Expresión lógica
        $$->children[1] = $5;  // Bloque ENTONCES
    }
    | CONDICION SI ExprLogica ENTONCES Declaraciones SINO Declaraciones FIN_CONDICION {
        $$ = createNode(NODE_CONDICION_ELSE);
        $$->children[0] = $3;  // Expresión lógica
        $$->children[1] = $5;  // Bloque ENTONCES
        $$->children[2] = $7;  // Bloque SINO
    }
    | CONDICION SI ExprLogica ENTONCES Declaraciones SINO_SI ExprLogica ENTONCES Declaraciones FIN_CONDICION {
        $$ = createNode(NODE_CONDICION_ELSEIF);
        $$->children[0] = $3;  // Primera expresión
        $$->children[1] = $5;  // Primer bloque
        $$->children[2] = $7;  // Segunda expresión (SINO_SI)
        $$->children[3] = $9;  // Segundo bloque
    }
    | CONDICION SI ExprLogica ENTONCES Declaraciones SINO_SI ExprLogica ENTONCES Declaraciones SINO Declaraciones FIN_CONDICION {
        $$ = createNode(NODE_CONDICION_ELSEIF);
        $$->children[0] = $3;  // Primera expresión
        $$->children[1] = $5;  // Primer bloque
        $$->children[2] = $7;  // Segunda expresión (SINO_SI)
        $$->children[3] = $9;  // Segundo bloque (SINO_SI)
        $$->children[4] = $11; // Bloque SINO final
    }
    ;

Accion:
    RIEGO STRING DURACION NUMERO {
        $$ = createNode(NODE_RIEGO);
        $$->str_value = $2;
        $$->num_value = $4;
    }
    | RIEGO STRING DURACION IDENTIFICADOR {
        $$ = createNode(NODE_RIEGO);
        $$->str_value = $2;
        $$->str_value2 = $4;  // Nombre de la constante
    }
    ;

RiegoAvanzado:
    RIEGO_AVANZADO STRING CAUDAL NUMERO DURACION NUMERO {
        $$ = createNode(NODE_RIEGO_AVANZADO);
        $$->str_value = $2;
        $$->num_value = $4;
        $$->num_value2 = $6;
    }
    | RIEGO_AVANZADO STRING CAUDAL IDENTIFICADOR DURACION IDENTIFICADOR {
        $$ = createNode(NODE_RIEGO_AVANZADO);
        $$->str_value = $2;
        $$->str_value2 = $4;  // Constante caudal
        $$->str_value3 = $6;  // Constante duración
    }
    | RIEGO_AVANZADO STRING CAUDAL NUMERO DURACION IDENTIFICADOR {
        $$ = createNode(NODE_RIEGO_AVANZADO);
        $$->str_value = $2;
        $$->num_value = $4;
        $$->str_value2 = $6;  // Constante duración
    }
    | RIEGO_AVANZADO STRING CAUDAL IDENTIFICADOR DURACION NUMERO {
        $$ = createNode(NODE_RIEGO_AVANZADO);
        $$->str_value = $2;
        $$->str_value2 = $4;  // Constante caudal
        $$->num_value2 = $6;
    }
    ;

/* Nueva: Activar actuador por su ID de dispositivo */
ActivarActuador:
    ACTIVAR STRING DURACION NUMERO {
        $$ = createNode(NODE_ACTIVAR);
        $$->str_value = $2;   // ID del actuador
        $$->num_value = $4;   // Duración
    }
    | ACTIVAR STRING DURACION IDENTIFICADOR {
        $$ = createNode(NODE_ACTIVAR);
        $$->str_value = $2;   // ID del actuador
        $$->str_value2 = $4;  // Nombre de la constante
    }
    ;

Fertilizacion:
    FERTILIZACION TIPO STRING CANTIDAD NUMERO {
        $$ = createNode(NODE_FERTILIZACION);
        $$->str_value = $3;
        $$->num_value = $5;
    }
    | FERTILIZACION TIPO STRING CANTIDAD IDENTIFICADOR {
        $$ = createNode(NODE_FERTILIZACION);
        $$->str_value = $3;
        $$->str_value2 = $5;  // Nombre de la constante
    }
    ;

Monitoreo:
    MONITOREAR IDENTIFICADOR CADA NUMERO HORAS {
        $$ = createNode(NODE_MONITOREO);
        $$->str_value = $2;
        $$->num_value = $4;
    }
    ;

Tarea:
    TAREA EJECUTAR STRING {
        $$ = createNode(NODE_TAREA);
        $$->str_value = $3;
    }
    ;

Reporte:
    REPORTE STRING {
        $$ = createNode(NODE_REPORTE);
        $$->str_value = $2;
    }
    ;

Alerta:
    ALERTA SI Expresion ENTONCES EnviarAlerta FIN_ALERTA {
        $$ = createNode(NODE_ALERTA);
        $$->children[0] = $3;
        $$->children[1] = $5;
    }
    ;

EnviarAlerta:
    ENVIAR_ALERTA STRING {
        $$ = createNode(NODE_ENVIAR_ALERTA);
        $$->str_value = $2;
    }
    ;

Expresion:
    IDENTIFICADOR Comparador NUMERO {
        $$ = createNode(NODE_EXPRESION);
        $$->str_value = $1;
        $$->str_value2 = $2;
        $$->num_value = $3;
    }
    | IDENTIFICADOR Comparador IDENTIFICADOR {
        $$ = createNode(NODE_EXPRESION);
        $$->str_value = $1;
        $$->str_value2 = $2;
        $$->str_value3 = $3;
    }
    | IDENTIFICADOR Comparador STRING {
        $$ = createNode(NODE_EXPRESION);
        $$->str_value = $1;
        $$->str_value2 = $2;
        $$->str_value3 = $3;
    }
    ;

/* Nueva: Expresiones lógicas con operadores Y, O, NO */
ExprLogica:
    Expresion {
        $$ = $1;  // Expresión simple (humedad < 40)
    }
    | ExprLogica Y ExprLogica {
        $$ = createNode(NODE_EXPRESION_LOGICA);
        $$->str_value = strdup("Y");
        $$->children[0] = $1;
        $$->children[1] = $3;
    }
    | ExprLogica O ExprLogica {
        $$ = createNode(NODE_EXPRESION_LOGICA);
        $$->str_value = strdup("O");
        $$->children[0] = $1;
        $$->children[1] = $3;
    }
    | NO ExprLogica {
        $$ = createNode(NODE_EXPRESION_LOGICA);
        $$->str_value = strdup("NO");
        $$->children[0] = $2;
    }
    | PAREN_IZQ ExprLogica PAREN_DER {
        $$ = $2;  // Los paréntesis solo agrupan
    }
    ;

Comparador:
    MENOR { $$ = strdup("<"); }
    | MAYOR { $$ = strdup(">"); }
    | MENOR_IGUAL { $$ = strdup("<="); }
    | MAYOR_IGUAL { $$ = strdup(">="); }
    | IGUAL { $$ = strdup("=="); }
    ;

/* Nueva: Regla para CALCULAR */
Calcular:
    CALCULAR IDENTIFICADOR ASIGNAR ExprMat {
        $$ = createNode(NODE_CALCULAR);
        $$->str_value = $2;      // Nombre de la variable
        $$->children[0] = $4;     // Expresión matemática
    }
    ;

/* Nueva: Expresiones matemáticas con precedencia */
ExprMat:
    ExprMat MAS ExprMat {
        $$ = createNode(NODE_EXPR_BINARIA);
        $$->str_value = strdup("+");
        $$->children[0] = $1;
        $$->children[1] = $3;
    }
    | ExprMat MENOS ExprMat {
        $$ = createNode(NODE_EXPR_BINARIA);
        $$->str_value = strdup("-");
        $$->children[0] = $1;
        $$->children[1] = $3;
    }
    | ExprMat MULTIPLICAR ExprMat {
        $$ = createNode(NODE_EXPR_BINARIA);
        $$->str_value = strdup("*");
        $$->children[0] = $1;
        $$->children[1] = $3;
    }
    | ExprMat DIVIDIR ExprMat {
        $$ = createNode(NODE_EXPR_BINARIA);
        $$->str_value = strdup("/");
        $$->children[0] = $1;
        $$->children[1] = $3;
    }
    | ExprMat MODULO ExprMat {
        $$ = createNode(NODE_EXPR_BINARIA);
        $$->str_value = strdup("%");
        $$->children[0] = $1;
        $$->children[1] = $3;
    }
    | PAREN_IZQ ExprMat PAREN_DER {
        $$ = $2;  // Los paréntesis solo agrupan, no crean nodo
    }
    | NUMERO {
        $$ = createNode(NODE_EXPR_NUMERO);
        $$->num_value = $1;
    }
    | IDENTIFICADOR {
        $$ = createNode(NODE_EXPR_VARIABLE);
        $$->str_value = $1;
    }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Error en línea %d: %s\n", yylineno, s);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Uso: %s <archivo.agro>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        printf("Error: No se puede abrir el archivo %s\n", argv[1]);
        return 1;
    }

    printf("🌱 Iniciando transpilador DSL -> C++\n");
    printf("📄 Leyendo archivo: %s\n\n", argv[1]);

    if (yyparse() == 0 && root != NULL) {
        printf("\n🔄 Generando código C++...\n");
        initCodegen("salida.cpp");
        generateCode(root);
        closeCodegen();
        printf("✓ Código generado en: salida.cpp\n");
        printf("\n📝 Para compilar y ejecutar:\n");
        printf("   g++ salida.cpp -o simulador -std=c++11\n");
        printf("   ./simulador\n");
    } else {
        printf("❌ Error durante el análisis\n");
    }

    fclose(yyin);
    return 0;
}
