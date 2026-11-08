#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "mini_parser.h"
#include "tabla_simbolos.h"

int errores_sintacticos = 0;

static int identificador_valido(const char *texto) {
    if (!(isalpha((unsigned char)texto[0]) || texto[0] == '_'))
        return 0;
    for (int i = 1; texto[i] != '\0'; i++)
        if (!(isalnum((unsigned char)texto[i]) || texto[i] == '_'))
            return 0;
    return 1;
}

static char *salta_espacios(char *p) {
    while (*p != '\0' && isspace((unsigned char)*p))
        p++;
    return p;
}

static int linea_vacia_o_comentario(char *linea) {
    char *p = salta_espacios(linea);
    return *p == '\0' || *p == '\n' ||
           (p[0] == '/' && p[1] == '/');
}

static void error_sintactico(int linea) {
    errores_sintacticos++;
    fprintf(stderr,
            "Error sintactico (linea %d): sentencia no reconocida\n",
            linea);
}

static int reconoce_declaracion(char *texto, int linea) {
    char palabra[8], nombre[64], punto_coma, extra;
    int campos = sscanf(texto, " %7s %63[A-Za-z0-9_] %c %c",
                        palabra, nombre, &punto_coma, &extra);
    if (strcmp(palabra, "int") != 0 && strcmp(palabra, "float") != 0)
        return 0;

    if (campos != 3 || punto_coma != ';' ||
        !identificador_valido(nombre)) {
        error_sintactico(linea);
        return 1;
    }

    TipoDato tipo = strcmp(palabra, "int") == 0 ? T_ENTERO : T_REAL;

    /* TODO 8: acción semántica de declaración */
    ts_declara(nombre, tipo, linea);

    return 1;
}

static int reconoce_asignacion(char *texto, int linea) {
    char nombre[64], punto_coma, extra;
    long valor;
    int campos = sscanf(texto, " %63[A-Za-z0-9_] = %ld %c %c",
                        nombre, &valor, &punto_coma, &extra);
    if (campos < 1 || strchr(texto, '=') == NULL)
        return 0;

    if (campos != 3 || punto_coma != ';' ||
        !identificador_valido(nombre)) {
        error_sintactico(linea);
        return 1;
    }

    /* TODO 9: acción semántica de uso en asignación */
    ts_usa(nombre, linea);

    return 1;
}

static int reconoce_print(char *texto, int linea) {
    char nombre[64], punto_coma, extra;
    int campos = sscanf(texto, " print ( %63[A-Za-z0-9_] ) %c %c",
                        nombre, &punto_coma, &extra);
    if (strncmp(salta_espacios(texto), "print", 5) != 0)
        return 0;

    if (campos != 2 || punto_coma != ';' ||
        !identificador_valido(nombre)) {
        error_sintactico(linea);
        return 1;
    }

    /* TODO 9 (segunda llamada): acción semántica de uso en print */
    ts_usa(nombre, linea);

    return 1;
}

int analiza_entrada(FILE *entrada) {
    char texto[256];
    int linea = 0;

    while (fgets(texto, sizeof(texto), entrada) != NULL) {
        linea++;
        if (linea_vacia_o_comentario(texto))
            continue;
        if (reconoce_declaracion(texto, linea))
            continue;
        if (reconoce_print(texto, linea))
            continue;
        if (reconoce_asignacion(texto, linea))
            continue;
        error_sintactico(linea);
    }
    return errores_sintacticos == 0;
}