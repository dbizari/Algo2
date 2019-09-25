#include "tp0.h"
/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/
void swap (int *x, int *y) {
    int aux;

    aux = *x;
    *x  = *y;
    *y  = aux;
}


int maximo(int vector[], int n) {
    if(n == 0) return -1;

    int max_pos = 0;

    for(int i = 0, max = vector[i]; i < n; i++){
        if(vector[i] > max){
            max     = vector[i];
            max_pos = i;
        }
    }

    return max_pos;
}

int comparar(int vector1[], int n1, int vector2[], int n2) {
    int i;

    for(i = 0; i < n1 && i < n2; i++){
        if(vector1[i] == vector2[i])
            continue;
        else
            return vector1[i] > vector2[i] ? 1:-1;

    }
    if(n1 == n2)
        return 0;
    else
        return i == n1 ? -1:1;
}

void seleccion(int vector[], int n) {
    for(int i = n - 1; i >= 0;i--){
          swap(&vector[i],&vector[maximo(vector,i+1)]);
    }
}
