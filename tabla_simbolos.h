#ifndef TABLA_SIMBOLOS_H
#define TABLA_SIMBOLOS_H

#include <string.h>

#define MAX_SIMBOLOS 100

/* TODO 1 */
typedef enum { T_ENTERO, T_REAL } TipoDato;

/* TODO 2 */
typedef struct {
    char nombre[64];
    TipoDato tipo;
    int linea_decl;
} Simbolo;

/* Variable global de errores semánticos (definida en tabla_simbolos.c) */
extern int errores_semanticos;

/* Prototipos de funciones */
void reporta_error(int linea, const char *nombre, const char *msg);
void ts_inicializa(void);
int  ts_busca(const char *nombre);
void ts_declara(const char *nombre, TipoDato tipo, int linea);
void ts_usa(const char *nombre, int linea);
void ts_imprime(void);
int  ts_hay_errores(void);

#endif /* TABLA_SIMBOLOS_H */