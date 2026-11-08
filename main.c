#include <stdio.h>
#include "mini_parser.h"
#include "tabla_simbolos.h"

int main(void) {
    analiza_entrada(stdin);
    ts_imprime();

    if (errores_sintacticos > 0 || errores_semanticos > 0) {
        printf("\nAnalisis finalizado con %d error(es) sintactico(s) "
               "y %d error(es) semantico(s).\n",
               errores_sintacticos, errores_semanticos);
        return 1;
    }

    printf("\nAnalisis semantico exitoso.\n");
    return 0;
}
