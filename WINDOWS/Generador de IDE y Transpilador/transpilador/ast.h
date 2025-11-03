#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <string.h>

typedef enum {
    NODE_PROGRAMA,
    NODE_LOTES,
    NODE_LOTE,
    NODE_CULTIVOS,
    NODE_CULTIVO,
    NODE_DECLARACIONES,
    NODE_VAR,
    NODE_CONST,                  // Nueva: constante
    NODE_DISPOSITIVO,
    NODE_DISPOSITIVO_IP,
    NODE_DISPOSITIVO_SERIAL,
    NODE_SENSOR,
    NODE_ACTUADOR,
    NODE_UBICAR_DISPOSITIVO,
    NODE_UBICAR_SENSOR,
    NODE_UBICAR_ACTUADOR,
    NODE_VINCULAR,
    NODE_GRUPO,                  // Nueva: grupo de sensores
    NODE_CONDICION,
    NODE_CONDICION_ELSE,         // Nueva: con ELSE
    NODE_CONDICION_ELSEIF,       // Nueva: con ELSE IF
    NODE_RIEGO,
    NODE_RIEGO_AVANZADO,
    NODE_ACTIVAR,
    NODE_FERTILIZACION,
    NODE_MONITOREO,
    NODE_TAREA,
    NODE_REPORTE,
    NODE_ALERTA,
    NODE_ENVIAR_ALERTA,
    NODE_EXPRESION,
    NODE_EXPRESION_LOGICA,       // Nueva: expresión lógica (A Y B)
    NODE_CALCULAR,
    NODE_EXPR_BINARIA,
    NODE_EXPR_NUMERO,
    NODE_EXPR_VARIABLE,
    NODE_EXPR_FUNCION,           // Nueva: función (PROMEDIO, MIN, MAX)
    NODE_LISTA_STRINGS           // Nueva: lista de strings
} NodeType;

typedef struct ASTNode {
    NodeType type;
    char* str_value;      // Nombre principal
    char* str_value2;     // Segundo valor (tipo, IP, etc)
    char* str_value3;     // Tercer valor (puerto, etc)
    double num_value;     // Valor numérico 1
    double num_value2;    // Valor numérico 2
    struct ASTNode* children[10];
} ASTNode;

ASTNode* createNode(NodeType type) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->str_value = NULL;
    node->str_value2 = NULL;
    node->str_value3 = NULL;
    node->num_value = 0;
    node->num_value2 = 0;
    for (int i = 0; i < 10; i++) {
        node->children[i] = NULL;
    }
    return node;
}

#endif
