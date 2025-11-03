#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast.h"
#include <stdio.h>
#include <string.h>

FILE* output;
int indentLevel = 0;

// Declaraciones adelantadas
void generateNode(ASTNode* node);
void generateDeclaraciones(ASTNode* node);
void generateExprLogica(ASTNode* node, int depth);
void printIndent(int level);

void initCodegen(const char* filename) {
    output = fopen(filename, "w");
    if (!output) {
        fprintf(stderr, "Error: No se pudo crear el archivo de salida\n");
        exit(1);
    }
}

void closeCodegen() {
    if (output) {
        fclose(output);
    }
}

void generateHeader() {
    fprintf(output, "#include <iostream>\n");
    fprintf(output, "#include <string>\n");
    fprintf(output, "#include <map>\n");
    fprintf(output, "#include <random>\n");
    fprintf(output, "#include <iomanip>\n");
    fprintf(output, "#include <sstream>\n");
    fprintf(output, "using namespace std;\n\n");
}

void generateSimuladorClass() {
    fprintf(output, "class SimuladorAgricola {\n");
    fprintf(output, "private:\n");
    fprintf(output, "    map<string, double> variables;\n");
    fprintf(output, "    map<string, string> tiposVariables;\n");
    fprintf(output, "    map<string, double> constantes;\n");
    fprintf(output, "    map<string, string> dispositivos;\n");
    fprintf(output, "    map<string, string> dispositivosIP;\n");
    fprintf(output, "    map<string, int> dispositivosPuerto;\n");
    fprintf(output, "    map<string, string> dispositivosSerial;\n");
    fprintf(output, "    map<string, string> vinculaciones;\n");
    fprintf(output, "    map<string, string> ubicaciones;\n");
    fprintf(output, "    random_device rd;\n");
    fprintf(output, "    mt19937 gen;\n");
    fprintf(output, "    int currentIndentLevel = 0;\n\n");
    
    fprintf(output, "    double generarValorAleatorio(double min, double max) {\n");
    fprintf(output, "        uniform_real_distribution<> dis(min, max);\n");
    fprintf(output, "        return dis(gen);\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "    double leerDispositivo(string dispositivoID) {\n");
    fprintf(output, "        if (dispositivosIP.find(dispositivoID) != dispositivosIP.end()) {\n");
    fprintf(output, "            string ip = dispositivosIP[dispositivoID];\n");
    fprintf(output, "            int puerto = dispositivosPuerto[dispositivoID];\n");
    fprintf(output, "            cout << getIndent() << \"       [→ \" << ip << \":\" << puerto << \"]\" << endl;\n");
    fprintf(output, "        } else if (dispositivosSerial.find(dispositivoID) != dispositivosSerial.end()) {\n");
    fprintf(output, "            string puerto = dispositivosSerial[dispositivoID];\n");
    fprintf(output, "            cout << getIndent() << \"       [→ \" << puerto << \"]\" << endl;\n");
    fprintf(output, "        }\n");
    fprintf(output, "        \n");
    fprintf(output, "        string tipo = dispositivos[dispositivoID];\n");
    fprintf(output, "        double valor;\n");
    fprintf(output, "        if (tipo == \"humedad\") {\n");
    fprintf(output, "            valor = generarValorAleatorio(0.0, 100.0);\n");
    fprintf(output, "        } else if (tipo == \"temperatura\") {\n");
    fprintf(output, "            valor = generarValorAleatorio(0.0, 100.0);\n");
    fprintf(output, "        } else if (tipo == \"ph\") {\n");
    fprintf(output, "            valor = generarValorAleatorio(0.0, 100.0);\n");
    fprintf(output, "        } else if (tipo == \"luz\") {\n");
    fprintf(output, "            valor = generarValorAleatorio(0.0, 100.0);\n");
    fprintf(output, "        } else if (tipo == \"co2\") {\n");
    fprintf(output, "            valor = generarValorAleatorio(0.0, 100.0);\n");
    fprintf(output, "        } else if (tipo == \"numero\") {\n");
    fprintf(output, "            valor = generarValorAleatorio(0.0, 100.0);\n");
    fprintf(output, "        } else if (tipo == \"viento\") {\n");
    fprintf(output, "            valor = generarValorAleatorio(0.0, 100.0);\n");
    fprintf(output, "        } else {\n");
    fprintf(output, "            valor = generarValorAleatorio(0.0, 100.0);\n");
    fprintf(output, "        }\n");
    fprintf(output, "        return valor;\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "public:\n");
    fprintf(output, "    SimuladorAgricola() : gen(rd()) {}\n\n");
    
    fprintf(output, "    string getIndent() {\n");
    fprintf(output, "        string indent = \"      \";\n");
    fprintf(output, "        for(int i = 0; i < currentIndentLevel; i++) {\n");
    fprintf(output, "            indent += \"  \";\n");
    fprintf(output, "        }\n");
    fprintf(output, "        return indent;\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "    void crearVariable(string nombre, string tipo) {\n");
    fprintf(output, "        variables[nombre] = 0.0;\n");
    fprintf(output, "        string tipoLower = tipo;\n");
    fprintf(output, "        for (auto& c : tipoLower) c = tolower(c);\n");
    fprintf(output, "        tiposVariables[nombre] = tipoLower;\n");
    fprintf(output, "        cout << \"      ├─ 📊 Variable creada: \" << nombre << \" (tipo: \" << tipo << \")\" << endl;\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "    void crearConstante(string nombre, double valor) {\n");
    fprintf(output, "        constantes[nombre] = valor;\n");
    fprintf(output, "        cout << \"      ├─ 📌 CONST: \" << nombre << \" = \" << fixed << setprecision(1) << valor << endl;\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "    void registrarDispositivo(string id, string tipo) {\n");
    fprintf(output, "        dispositivos[id] = tipo;\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "    void registrarDispositivoIP(string id, string ip, int puerto) {\n");
    fprintf(output, "        dispositivosIP[id] = ip;\n");
    fprintf(output, "        dispositivosPuerto[id] = puerto;\n");
    fprintf(output, "        cout << \"      ├─ 🌐 Dispositivo registrado: \" << id << endl;\n");
    fprintf(output, "        cout << \"      │  └─ IP: \" << ip << \":\" << puerto << endl;\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "    void registrarDispositivoSerial(string id, string puerto) {\n");
    fprintf(output, "        dispositivosSerial[id] = puerto;\n");
    fprintf(output, "        cout << \"      ├─ 🔌 Dispositivo registrado: \" << id << endl;\n");
    fprintf(output, "        cout << \"      │  └─ Puerto Serial: \" << puerto << endl;\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "    void vincular(string variable, string dispositivoID) {\n");
    fprintf(output, "        vinculaciones[variable] = dispositivoID;\n");
    fprintf(output, "        cout << \"      ├─ 🔗 Vinculación: '\" << variable << \"' ↔ '\" << dispositivoID << \"'\" << endl;\n");
    fprintf(output, "        \n");
    fprintf(output, "        double valorInicial = leerDispositivo(dispositivoID);\n");
    fprintf(output, "        variables[variable] = valorInicial;\n");
    fprintf(output, "        \n");
    fprintf(output, "        cout << \"      │  └─ Valor inicial: \" << fixed << setprecision(1) << valorInicial;\n");
    fprintf(output, "        if (tiposVariables[variable] == \"humedad\") cout << \"%%\";\n");
    fprintf(output, "        if (tiposVariables[variable] == \"temperatura\") cout << \"°C\";\n");
    fprintf(output, "        if (tiposVariables[variable] == \"ph\") cout << \" pH\";\n");
    fprintf(output, "        cout << endl;\n");
    fprintf(output, "    }\n\n");
    
    // Función mejorada para evaluar condiciones simples - PROPUESTA #2
    fprintf(output, "    bool evaluarCondicionSimple(string variable, string op, double valor, int depth = 0) {\n");
    fprintf(output, "        if (vinculaciones.find(variable) != vinculaciones.end()) {\n");
    fprintf(output, "            string dispositivoID = vinculaciones[variable];\n");
    fprintf(output, "            variables[variable] = leerDispositivo(dispositivoID);\n");
    fprintf(output, "        }\n");
    fprintf(output, "        \n");
    fprintf(output, "        double actual = variables[variable];\n");
    fprintf(output, "        \n");
    fprintf(output, "        // Mostrar condición\n");
    fprintf(output, "        cout << getIndent();\n");
    fprintf(output, "        for(int i = 0; i < depth; i++) cout << \"   \";\n");
    fprintf(output, "        cout << \"   📊 \" << variable << \" \" << op << \" \" << fixed << setprecision(0) << valor << endl;\n");
    fprintf(output, "        \n");
    fprintf(output, "        // Mostrar valor\n");
    fprintf(output, "        cout << getIndent();\n");
    fprintf(output, "        for(int i = 0; i < depth; i++) cout << \"   \";\n");
    fprintf(output, "        cout << \"      → \" << fixed << setprecision(1) << actual;\n");
    fprintf(output, "        if (tiposVariables[variable] == \"humedad\") cout << \"%%\";\n");
    fprintf(output, "        if (tiposVariables[variable] == \"temperatura\") cout << \"°C\";\n");
    fprintf(output, "        if (tiposVariables[variable] == \"ph\") cout << \" pH\";\n");
    fprintf(output, "        cout << \" \";\n");
    fprintf(output, "        \n");
    fprintf(output, "        bool resultado = false;\n");
    fprintf(output, "        if (op == \"<\") resultado = actual < valor;\n");
    fprintf(output, "        else if (op == \">\") resultado = actual > valor;\n");
    fprintf(output, "        else if (op == \"<=\") resultado = actual <= valor;\n");
    fprintf(output, "        else if (op == \">=\") resultado = actual >= valor;\n");
    fprintf(output, "        else if (op == \"==\") resultado = actual == valor;\n");
    fprintf(output, "        \n");
    fprintf(output, "        if (resultado) {\n");
    fprintf(output, "            cout << \"✓\" << endl;\n");
    fprintf(output, "        } else {\n");
    fprintf(output, "            cout << \"✗\" << endl;\n");
    fprintf(output, "        }\n");
    fprintf(output, "        return resultado;\n");
    fprintf(output, "    }\n\n");
    
    // Funciones de visualización mejoradas - PROPUESTA #2
    fprintf(output, "    void mostrarInicioEvaluacion(string tipoCondicion = \"\") {\n");
    fprintf(output, "        cout << getIndent() << \"├─ ⚙️  EVALUANDO CONDICIÓN\" << tipoCondicion << endl;\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "    void mostrarResultadoCondicion(bool resultado) {\n");
    fprintf(output, "        cout << getIndent() << \"│\" << endl;\n");
    fprintf(output, "        if (resultado) {\n");
    fprintf(output, "            cout << getIndent() << \"└─ ✓ CONDICIÓN CUMPLIDA\" << endl;\n");
    fprintf(output, "        } else {\n");
    fprintf(output, "            cout << getIndent() << \"└─ ✗ Condición NO cumplida\" << endl;\n");
    fprintf(output, "        }\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "    void mostrarOperadorLogico(string operador, int depth = 0) {\n");
    fprintf(output, "        cout << getIndent();\n");
    fprintf(output, "        for(int i = 0; i < depth; i++) cout << \"   \";\n");
    fprintf(output, "        cout << \"   🔗 \" << operador << endl;\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "    void incrementarIndent() { currentIndentLevel++; }\n");
    fprintf(output, "    void decrementarIndent() { if(currentIndentLevel > 0) currentIndentLevel--; }\n\n");
    
    fprintf(output, "    bool evaluarCondicion(string variable, string op, double valor) {\n");
    fprintf(output, "        return evaluarCondicionSimple(variable, op, valor, 0);\n");
    fprintf(output, "    }\n\n");
    
    // Funciones de acciones mejoradas - PROPUESTA #2
    fprintf(output, "    void ejecutarRiego(string sector, double duracion) {\n");
    fprintf(output, "        cout << getIndent() << \"   ├─ 💧 RIEGO\" << endl;\n");
    fprintf(output, "        cout << getIndent() << \"   │   • Sector: \" << sector << endl;\n");
    fprintf(output, "        cout << getIndent() << \"   │   • Duración: \" << fixed << setprecision(0) << duracion << \" min\" << endl;\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "    void ejecutarRiegoAvanzado(string sector, double caudal, double duracion) {\n");
    fprintf(output, "        cout << getIndent() << \"   ├─ 💧 RIEGO AVANZADO\" << endl;\n");
    fprintf(output, "        cout << getIndent() << \"   │   • Sector: \" << sector << endl;\n");
    fprintf(output, "        cout << getIndent() << \"   │   • Duración: \" << fixed << setprecision(0) << duracion << \" min\" << endl;\n");
    fprintf(output, "        cout << getIndent() << \"   │   • Caudal: \" << fixed << setprecision(1) << caudal << \" L/min\" << endl;\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "    void activarActuador(string actuadorID, double duracion) {\n");
    fprintf(output, "        cout << getIndent() << \"   ├─ ⚡ ACTIVACIÓN\" << endl;\n");
    fprintf(output, "        cout << getIndent() << \"   │   • Actuador: \" << actuadorID << endl;\n");
    fprintf(output, "        cout << getIndent() << \"   │   • Tiempo: \" << fixed << setprecision(0) << duracion << \" min\" << endl;\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "    void ejecutarFertilizacion(string tipo, double cantidad) {\n");
    fprintf(output, "        cout << getIndent() << \"   ├─ 🌱 FERTILIZACIÓN\" << endl;\n");
    fprintf(output, "        cout << getIndent() << \"   │   • Tipo: \" << tipo << endl;\n");
    fprintf(output, "        cout << getIndent() << \"   │   • Cantidad: \" << fixed << setprecision(1) << cantidad << \" kg\" << endl;\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "    void monitorear(string variable, int frecuencia) {\n");
    fprintf(output, "        cout << getIndent() << \"├─ 📡 Monitoreo configurado: \" << variable << endl;\n");
    fprintf(output, "        cout << getIndent() << \"│  └─ Frecuencia: cada \" << frecuencia << \" horas\" << endl;\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "    void generarReporte(string titulo) {\n");
    fprintf(output, "        cout << getIndent() << \"├─ 📑 REPORTE: \" << titulo << endl;\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "    void enviarAlerta(string mensaje) {\n");
    fprintf(output, "        cout << getIndent() << \"   └─ 🚨 ALERTA: \" << mensaje << endl;\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "    void calcular(string variable, double valor) {\n");
    fprintf(output, "        variables[variable] = valor;\n");
    fprintf(output, "        cout << getIndent() << \"├─ 🔢 Cálculo: \" << variable << \" = \" << fixed << setprecision(2) << valor << endl;\n");
    fprintf(output, "    }\n\n");
    
    fprintf(output, "    double obtenerValor(string nombre) {\n");
    fprintf(output, "        if (constantes.find(nombre) != constantes.end()) {\n");
    fprintf(output, "            return constantes[nombre];\n");
    fprintf(output, "        }\n");
    fprintf(output, "        if (variables.find(nombre) != variables.end()) {\n");
    fprintf(output, "            return variables[nombre];\n");
    fprintf(output, "        }\n");
    fprintf(output, "        return 0.0;\n");
    fprintf(output, "    }\n");
    
    fprintf(output, "};\n\n");
}

double evaluarExprMat(ASTNode* node, FILE* output) {
    if (!node) return 0.0;
    
    switch (node->type) {
        case NODE_EXPR_NUMERO:
            fprintf(output, "%.2f", node->num_value);
            return node->num_value;
            
        case NODE_EXPR_VARIABLE:
            fprintf(output, "sistema.obtenerValor(\"%s\")", node->str_value);
            return 0.0;
            
        case NODE_EXPR_BINARIA: {
            fprintf(output, "(");
            evaluarExprMat(node->children[0], output);
            fprintf(output, " %s ", node->str_value);
            evaluarExprMat(node->children[1], output);
            fprintf(output, ")");
            return 0.0;
        }
        
        default:
            return 0.0;
    }
}

void generatePrograma(ASTNode* node) {
    fprintf(output, "int main() {\n");
    fprintf(output, "    SimuladorAgricola sistema;\n\n");
    fprintf(output, "    cout << \"╔══════════════════════════════════════════════╗\" << endl;\n");
    fprintf(output, "    cout << \"║  SISTEMA DE AGRICULTURA AUTOMATIZADA V3.0   ║\" << endl;\n");
    fprintf(output, "    cout << \"╚══════════════════════════════════════════════╝\" << endl;\n");
    fprintf(output, "    cout << endl;\n\n");
    
    if (node->children[0]) {
        generateNode(node->children[0]);
    }
    
    if (node->children[1]) {
        generateNode(node->children[1]);
    }
    
    fprintf(output, "\n    cout << endl;\n");
    fprintf(output, "    cout << \"✓ Programa ejecutado exitosamente\" << endl;\n");
    fprintf(output, "    cout << \"━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\" << endl;\n");
    fprintf(output, "    cout << \"✅ Programa ejecutado correctamente\" << endl;\n");
    fprintf(output, "    return 0;\n");
    fprintf(output, "}\n");
}

void generateLotes(ASTNode* node) {
    for (int i = 0; i < 10 && node->children[i]; i++) {
        generateNode(node->children[i]);
    }
}

void generateLote(ASTNode* node) {
    fprintf(output, "    cout << \"📦 LOTE: %s\" << endl;\n", node->str_value);
    
    if (node->children[0]) {
        generateNode(node->children[0]);
    }
}

void generateCultivos(ASTNode* node) {
    for (int i = 0; i < 10 && node->children[i]; i++) {
        generateNode(node->children[i]);
    }
}

void generateCultivo(ASTNode* node) {
    fprintf(output, "    cout << \"  └─ 🌱 CULTIVO: %s\" << endl;\n", node->str_value);
    
    if (node->children[0]) {
        generateNode(node->children[0]);
    }
}

void generateDeclaraciones(ASTNode* node) {
    for (int i = 0; i < 10 && node->children[i]; i++) {
        generateNode(node->children[i]);
    }
}

void generateVar(ASTNode* node) {
    fprintf(output, "    sistema.crearVariable(\"%s\", \"%s\");\n", 
            node->str_value, node->str_value2);
}

void generateConstDef(ASTNode* node) {
    if (node->str_value2) {
        fprintf(output, "    sistema.crearConstante(\"%s\", sistema.obtenerValor(\"%s\"));\n", 
                node->str_value, node->str_value2);
    } else {
        fprintf(output, "    sistema.crearConstante(\"%s\", %.1f);\n", 
                node->str_value, node->num_value);
    }
}

void generateDispositivoIP(ASTNode* node) {
    fprintf(output, "    sistema.registrarDispositivoIP(\"%s\", \"%s\", %d);\n",
            node->str_value, node->str_value2, (int)node->num_value);
}

void generateDispositivoSerial(ASTNode* node) {
    fprintf(output, "    sistema.registrarDispositivoSerial(\"%s\", \"%s\");\n",
            node->str_value, node->str_value2);
}

void generateDispositivo(ASTNode* node) {
    if (node->num_value > 0) {
        generateDispositivoIP(node);
    } else {
        generateDispositivoSerial(node);
    }
}

void generateSensor(ASTNode* node) {
    fprintf(output, "    sistema.registrarDispositivo(\"%s\", \"%s\");\n",
            node->str_value2, node->str_value);
}

void generateActuador(ASTNode* node) {
    fprintf(output, "    // Actuador: %s de tipo %s\n", node->str_value2, node->str_value);
}

void generateUbicarDispositivo(ASTNode* node) {
    fprintf(output, "    // Ubicando dispositivo %s en %s\n", node->str_value, node->str_value2);
}

void generateUbicarSensor(ASTNode* node) {
    fprintf(output, "    // Ubicando sensor %s en %s\n", node->str_value, node->str_value2);
}

void generateUbicarActuador(ASTNode* node) {
    fprintf(output, "    // Ubicando actuador %s en %s\n", node->str_value, node->str_value2);
}

void generateVincular(ASTNode* node) {
    fprintf(output, "    sistema.vincular(\"%s\", \"%s\");\n",
            node->str_value, node->str_value2);
}

// Generación mejorada de expresiones lógicas con jerarquía visual - OPCIÓN B
void generateExprLogica(ASTNode* node, int depth) {
    if (!node) return;
    
    if (node->type == NODE_EXPRESION) {
        if (node->str_value3) {
            fprintf(output, "sistema.evaluarCondicionSimple(\"%s\", \"%s\", sistema.obtenerValor(\"%s\"), %d)",
                    node->str_value, node->str_value2, node->str_value3, depth);
        } else {
            fprintf(output, "sistema.evaluarCondicionSimple(\"%s\", \"%s\", %.1f, %d)",
                    node->str_value, node->str_value2, node->num_value, depth);
        }
    } else if (node->type == NODE_EXPRESION_LOGICA) {
        if (strcmp(node->str_value, "Y") == 0) {
            fprintf(output, "[&](){\n");
            fprintf(output, "                sistema.mostrarOperadorLogico(\"Y (AND)\", %d);\n", depth);
            fprintf(output, "                bool r1 = ");
            generateExprLogica(node->children[0], depth + 1);
            fprintf(output, ";\n                bool r2 = ");
            generateExprLogica(node->children[1], depth + 1);
            fprintf(output, ";\n                return r1 && r2;\n            }()");
        } else if (strcmp(node->str_value, "O") == 0) {
            fprintf(output, "[&](){\n");
            fprintf(output, "                sistema.mostrarOperadorLogico(\"O (OR)\", %d);\n", depth);
            fprintf(output, "                bool r1 = ");
            generateExprLogica(node->children[0], depth + 1);
            fprintf(output, ";\n                bool r2 = ");
            generateExprLogica(node->children[1], depth + 1);
            fprintf(output, ";\n                return r1 || r2;\n            }()");
        } else if (strcmp(node->str_value, "NO") == 0) {
            fprintf(output, "[&](){\n");
            fprintf(output, "                sistema.mostrarOperadorLogico(\"NO (NOT)\", %d);\n", depth);
            fprintf(output, "                bool r = ");
            generateExprLogica(node->children[0], depth + 1);
            fprintf(output, ";\n                return !r;\n            }()");
        }
    }
}

// Generación mejorada de condiciones
void generateCondicion(ASTNode* node) {
    if (node->type == NODE_CONDICION) {
        fprintf(output, "    {\n");
        fprintf(output, "        sistema.mostrarInicioEvaluacion();\n");
        fprintf(output, "        sistema.incrementarIndent();\n");
        fprintf(output, "        bool _cond = ");
        generateExprLogica(node->children[0], 0);
        fprintf(output, ";\n");
        fprintf(output, "        sistema.decrementarIndent();\n");
        fprintf(output, "        sistema.mostrarResultadoCondicion(_cond);\n");
        fprintf(output, "        if (_cond) {\n");
        fprintf(output, "            sistema.incrementarIndent();\n");
        if (node->children[1]) {
            generateNode(node->children[1]);
        }
        fprintf(output, "            sistema.decrementarIndent();\n");
        fprintf(output, "        }\n");
        fprintf(output, "    }\n");
        
    } else if (node->type == NODE_CONDICION_ELSE) {
        fprintf(output, "    {\n");
        fprintf(output, "        sistema.mostrarInicioEvaluacion();\n");
        fprintf(output, "        sistema.incrementarIndent();\n");
        fprintf(output, "        bool _cond = ");
        generateExprLogica(node->children[0], 0);
        fprintf(output, ";\n");
        fprintf(output, "        sistema.decrementarIndent();\n");
        fprintf(output, "        sistema.mostrarResultadoCondicion(_cond);\n");
        fprintf(output, "        if (_cond) {\n");
        fprintf(output, "            sistema.incrementarIndent();\n");
        if (node->children[1]) {
            generateNode(node->children[1]);
        }
        fprintf(output, "            sistema.decrementarIndent();\n");
        fprintf(output, "        } else {\n");
        fprintf(output, "            sistema.mostrarInicioEvaluacion(\" BLOQUE SINO\");\n");
        fprintf(output, "            sistema.incrementarIndent();\n");
        if (node->children[2]) {
            generateNode(node->children[2]);
        }
        fprintf(output, "            sistema.decrementarIndent();\n");
        fprintf(output, "        }\n");
        fprintf(output, "    }\n");
        
    } else if (node->type == NODE_CONDICION_ELSEIF) {
        fprintf(output, "    {\n");
        fprintf(output, "        sistema.mostrarInicioEvaluacion();\n");
        fprintf(output, "        sistema.incrementarIndent();\n");
        fprintf(output, "        bool _cond1 = ");
        generateExprLogica(node->children[0], 0);
        fprintf(output, ";\n");
        fprintf(output, "        sistema.decrementarIndent();\n");
        fprintf(output, "        sistema.mostrarResultadoCondicion(_cond1);\n");
        fprintf(output, "        if (_cond1) {\n");
        fprintf(output, "            sistema.incrementarIndent();\n");
        if (node->children[1]) {
            generateNode(node->children[1]);
        }
        fprintf(output, "            sistema.decrementarIndent();\n");
        fprintf(output, "        } else {\n");
        fprintf(output, "            sistema.mostrarInicioEvaluacion(\" SINO_SI\");\n");
        fprintf(output, "            sistema.incrementarIndent();\n");
        fprintf(output, "            bool _cond2 = ");
        generateExprLogica(node->children[2], 0);
        fprintf(output, ";\n");
        fprintf(output, "            sistema.decrementarIndent();\n");
        fprintf(output, "            sistema.mostrarResultadoCondicion(_cond2);\n");
        fprintf(output, "            if (_cond2) {\n");
        fprintf(output, "                sistema.incrementarIndent();\n");
        if (node->children[3]) {
            generateNode(node->children[3]);
        }
        fprintf(output, "                sistema.decrementarIndent();\n");
        fprintf(output, "            }\n");
        if (node->children[4]) {
            fprintf(output, "            else {\n");
            fprintf(output, "                sistema.mostrarInicioEvaluacion(\" BLOQUE SINO\");\n");
            fprintf(output, "                sistema.incrementarIndent();\n");
            generateNode(node->children[4]);
            fprintf(output, "                sistema.decrementarIndent();\n");
            fprintf(output, "            }\n");
        }
        fprintf(output, "        }\n");
        fprintf(output, "    }\n");
    }
}

void generateRiego(ASTNode* node) {
    if (node->str_value2) {
        fprintf(output, "            sistema.ejecutarRiego(\"%s\", sistema.obtenerValor(\"%s\"));\n",
                node->str_value, node->str_value2);
    } else {
        fprintf(output, "            sistema.ejecutarRiego(\"%s\", %.0f);\n",
                node->str_value, node->num_value);
    }
}

void generateRiegoAvanzado(ASTNode* node) {
    fprintf(output, "            sistema.ejecutarRiegoAvanzado(\"%s\", ", node->str_value);
    
    if (node->str_value2 && node->num_value == 0) {
        fprintf(output, "sistema.obtenerValor(\"%s\"), ", node->str_value2);
    } else {
        fprintf(output, "%.1f, ", node->num_value);
    }
    
    if (node->str_value3) {
        fprintf(output, "sistema.obtenerValor(\"%s\")", node->str_value3);
    } else {
        fprintf(output, "%.0f", node->num_value2);
    }
    
    fprintf(output, ");\n");
}

void generateActivar(ASTNode* node) {
    if (node->str_value2) {
        fprintf(output, "            sistema.activarActuador(\"%s\", sistema.obtenerValor(\"%s\"));\n",
                node->str_value, node->str_value2);
    } else {
        fprintf(output, "            sistema.activarActuador(\"%s\", %.0f);\n",
                node->str_value, node->num_value);
    }
}

void generateFertilizacion(ASTNode* node) {
    if (node->str_value2) {
        fprintf(output, "            sistema.ejecutarFertilizacion(\"%s\", sistema.obtenerValor(\"%s\"));\n",
                node->str_value, node->str_value2);
    } else {
        fprintf(output, "            sistema.ejecutarFertilizacion(\"%s\", %.1f);\n",
                node->str_value, node->num_value);
    }
}

void generateMonitoreo(ASTNode* node) {
    fprintf(output, "    sistema.monitorear(\"%s\", %d);\n",
            node->str_value, (int)node->num_value);
}

void generateTarea(ASTNode* node) {
    fprintf(output, "    // Tarea: %s\n", node->str_value);
}

void generateReporte(ASTNode* node) {
    fprintf(output, "    sistema.generarReporte(\"%s\");\n", node->str_value);
}

void generateAlerta(ASTNode* node) {
    fprintf(output, "    sistema.enviarAlerta(\"%s\");\n", node->str_value);
}

void generateEnviarAlerta(ASTNode* node) {
    fprintf(output, "            sistema.enviarAlerta(\"%s\");\n", node->str_value);
}

void generateCalcular(ASTNode* node) {
    fprintf(output, "    sistema.calcular(\"%s\", ", node->str_value);
    evaluarExprMat(node->children[0], output);
    fprintf(output, ");\n");
}

void generateNode(ASTNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case NODE_PROGRAMA: generatePrograma(node); break;
        case NODE_LOTES: generateLotes(node); break;
        case NODE_LOTE: generateLote(node); break;
        case NODE_CULTIVOS: generateCultivos(node); break;
        case NODE_CULTIVO: generateCultivo(node); break;
        case NODE_DECLARACIONES: generateDeclaraciones(node); break;
        case NODE_VAR: generateVar(node); break;
        case NODE_CONST: generateConstDef(node); break;
        case NODE_DISPOSITIVO_IP: generateDispositivoIP(node); break;
        case NODE_DISPOSITIVO_SERIAL: generateDispositivoSerial(node); break;
        case NODE_DISPOSITIVO: generateDispositivo(node); break;
        case NODE_SENSOR: generateSensor(node); break;
        case NODE_ACTUADOR: generateActuador(node); break;
        case NODE_UBICAR_DISPOSITIVO: generateUbicarDispositivo(node); break;
        case NODE_UBICAR_SENSOR: generateUbicarSensor(node); break;
        case NODE_UBICAR_ACTUADOR: generateUbicarActuador(node); break;
        case NODE_VINCULAR: generateVincular(node); break;
        case NODE_CONDICION: generateCondicion(node); break;
        case NODE_CONDICION_ELSE: generateCondicion(node); break;
        case NODE_CONDICION_ELSEIF: generateCondicion(node); break;
        case NODE_RIEGO: generateRiego(node); break;
        case NODE_RIEGO_AVANZADO: generateRiegoAvanzado(node); break;
        case NODE_ACTIVAR: generateActivar(node); break;
        case NODE_FERTILIZACION: generateFertilizacion(node); break;
        case NODE_MONITOREO: generateMonitoreo(node); break;
        case NODE_TAREA: generateTarea(node); break;
        case NODE_REPORTE: generateReporte(node); break;
        case NODE_ALERTA: generateAlerta(node); break;
        case NODE_ENVIAR_ALERTA: generateEnviarAlerta(node); break;
        case NODE_CALCULAR: generateCalcular(node); break;
        case NODE_EXPR_BINARIA: break;
        case NODE_EXPR_NUMERO: break;
        case NODE_EXPR_VARIABLE: break;
        case NODE_EXPRESION_LOGICA: break;
        default: break;
    }
}

void generateCode(ASTNode* root) {
    generateHeader();
    generateSimuladorClass();
    generateNode(root);
}

#endif
