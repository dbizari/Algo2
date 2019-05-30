#include "testing.h"
#include <stdlib.h>
#include <stdio.h>

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

void pruebas_abb(void);
//void pruebas_volumen_catedra(size_t);

int main(int argc, char *argv[])
{
    if (argc > 1) {
        // Asumimos que nos están pidiendo pruebas de volumen.
        //long largo = strtol(argv[1], NULL, 10);
       // pruebas_volumen_catedra((size_t) largo);

        return failure_count() > 0;
    }

    printf("\n~~~ PRUEBAS ~~~\n");
    pruebas_abb();

    return failure_count() > 0;
}
