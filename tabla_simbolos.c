#include <stdio.h>
#include <string.h>
#include "tabla_simbolos.h"

/* TODO 3 */
static Simbolo tabla[MAX_SIMBOLOS];
static int cantidad = 0;
int errores_semanticos = 0;

void reporta_error(int linea, const char *nombre, const char *msg)
{
    fprintf(stderr, "Error semantico (linea %d): variable '%s' %s\n",
            linea, nombre, msg);
    errores_semanticos++;
}

void ts_inicializa(void)
{
    cantidad = 0;
    errores_semanticos = 0;
}

/* TODO 4 */
int ts_busca(const char *nombre)
{
    for (int i = 0; i < cantidad; i++) {
        if (strcmp(tabla[i].nombre, nombre) == 0)
            return i;
    }
    return -1;
}

/* TODO 5 y TODO 6 */
void ts_declara(const char *nombre, TipoDato tipo, int linea)
{
    /* Protección: tabla llena */
    if (cantidad >= MAX_SIMBOLOS) {
        reporta_error(linea, nombre, "tabla llena");
        return;
    }

    /* TODO 5: detectar redeclaración */
    if (ts_busca(nombre) >= 0) {
        reporta_error(linea, nombre, "ya declarada");
        return;
    }

    /* TODO 6: registrar la nueva entrada */
    strncpy(tabla[cantidad].nombre, nombre, 63);
    tabla[cantidad].nombre[63] = '\0';   /* asegurar terminador */
    tabla[cantidad].tipo       = tipo;
    tabla[cantidad].linea_decl = linea;
    cantidad++;
}

/* TODO 7 */
void ts_usa(const char *nombre, int linea)
{
    if (ts_busca(nombre) < 0)
        reporta_error(linea, nombre, "no declarada");
}

void ts_imprime(void)
{
    printf("--- Tabla de simbolos (%d entradas) ---\n", cantidad);
    for (int i = 0; i < cantidad; i++) {
        const char *t = (tabla[i].tipo == T_ENTERO) ? "int" : "float";
        printf("[%d] %-16s %-5s declarada en linea %d\n",
               i, tabla[i].nombre, t, tabla[i].linea_decl);
    }
}

int ts_hay_errores(void)
{
    return errores_semanticos > 0;
}