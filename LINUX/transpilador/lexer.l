%{
#include "parser.tab.h"
#include <string.h>
%}

%option noyywrap
%option yylineno

%x COMMENT

%%

"//".*              { /* Comentario de una línea estilo Java */ }
"/*"                { BEGIN(COMMENT); /* Inicio de comentario multi-línea */ }
<COMMENT>"*/"       { BEGIN(INITIAL); /* Fin de comentario multi-línea */ }
<COMMENT>\n         { /* Salto de línea dentro del comentario */ }
<COMMENT>.          { /* Cualquier carácter dentro del comentario */ }

"INICIAR"           { return INICIAR; }
"FINALIZAR"         { return FINALIZAR; }
"CULTIVO"           { return CULTIVO; }
"LOTE"              { return LOTE; }

"VAR"               { return VAR; }
"CONST"             { return CONST; }
"DISPOSITIVO"       { return DISPOSITIVO; }
"SENSOR"            { return SENSOR; }
"ACTUADOR"          { return ACTUADOR; }

"IP"                { return IP; }
"PUERTO"            { return PUERTO; }
"SERIAL"            { return SERIAL; }

"UBICAR_DISPOSITIVO" { return UBICAR_DISPOSITIVO; }
"UBICAR_SENSOR"     { return UBICAR_SENSOR; }
"UBICAR_ACTUADOR"   { return UBICAR_ACTUADOR; }
"VINCULAR"          { return VINCULAR; }

"CONDICION"         { return CONDICION; }
"FIN_CONDICION"     { return FIN_CONDICION; }
"RIEGO"             { return RIEGO; }
"RIEGO_AVANZADO"    { return RIEGO_AVANZADO; }
"ACTIVAR"           { return ACTIVAR; }
"DURACION"          { return DURACION; }
"CAUDAL"            { return CAUDAL; }
"FERTILIZACION"     { return FERTILIZACION; }
"TIPO"              { return TIPO; }
"CANTIDAD"          { return CANTIDAD; }
"MONITOREAR"        { return MONITOREAR; }
"CADA"              { return CADA; }
"HORAS"             { return HORAS; }
"TAREA"             { return TAREA; }
"EJECUTAR"          { return EJECUTAR; }
"REPORTE"           { return REPORTE; }
"ALERTA"            { return ALERTA; }
"FIN_ALERTA"        { return FIN_ALERTA; }
"ENVIAR_ALERTA"     { return ENVIAR_ALERTA; }
"SI"                { return SI; }
"ENTONCES"          { return ENTONCES; }
"SINO"              { return SINO; }
"SINO_SI"           { return SINO_SI; }
"EN"                { return EN; }
"A"                 { return A; }
"CALCULAR"          { return CALCULAR; }

"Y"                 { return Y; }
"O"                 { return O; }
"NO"                { return NO; }

":"                 { return DOS_PUNTOS; }
"="                 { return ASIGNAR; }
"<"                 { return MENOR; }
">"                 { return MAYOR; }
"<="                { return MENOR_IGUAL; }
">="                { return MAYOR_IGUAL; }
"=="                { return IGUAL; }
"+"                 { return MAS; }
"-"                 { return MENOS; }
"*"                 { return MULTIPLICAR; }
"/"                 { return DIVIDIR; }
"%"                 { return MODULO; }
"("                 { return PAREN_IZQ; }
")"                 { return PAREN_DER; }

-?[0-9]+(\.[0-9]+)?   { yylval.num = atof(yytext); return NUMERO; }

"Humedad"           { yylval.str = strdup(yytext); return TIPO_DATO; }
"Temperatura"       { yylval.str = strdup(yytext); return TIPO_DATO; }
"Ph"                { yylval.str = strdup(yytext); return TIPO_DATO; }
"Luz"               { yylval.str = strdup(yytext); return TIPO_DATO; }
"Numero"            { yylval.str = strdup(yytext); return TIPO_DATO; }
"Co2"               { yylval.str = strdup(yytext); return TIPO_DATO; }
"Presion"           { yylval.str = strdup(yytext); return TIPO_DATO; }
"Viento"            { yylval.str = strdup(yytext); return TIPO_DATO; }

[a-z][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return IDENTIFICADOR; }

\"[^\"]*\"          { 
                      /* Remover las comillas del principio y final */
                      int len = strlen(yytext);
                      char *temp = (char*)malloc(len - 1);  // -2 por las comillas, +1 por el null terminator
                      strncpy(temp, yytext + 1, len - 2);
                      temp[len - 2] = '\0';
                      yylval.str = temp;
                      return STRING; 
                    }

[ \t]+              { /* ignorar espacios */ }
\n                  { /* yylineno se incrementa automáticamente */ }

.                   { printf("Carácter no reconocido: %s en línea %d\n", yytext, yylineno); }

%%
