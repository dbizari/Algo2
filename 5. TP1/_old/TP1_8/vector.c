#include "vector.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

void vector_destruir(vector_t* vector){
    for (size_t i = 0; i < vector->cantidad; i++) {
        free(vector->datos[i]);
    }
    free(vector->datos);
    free(vector);
}

void* vector_obtener(vector_t* vector, size_t pos){
    if(vector == NULL) return NULL;
    if(pos > (vector->tam - 1) || vector->tam == 0) return NULL;

    return vector->datos[pos];
}

bool vector_guardar(vector_t* vector, size_t pos, void* valor){
    if(vector == NULL) return false;
    if(pos > (vector->tam - 1) || vector->tam == 0) return false;
    if(vector->cantidad == (vector->tam - 1)){
        if(!vector_redimensionar(vector,vector->tam * 2))
            return false;
    }
    vector->cantidad++;
    vector->datos[pos] = valor;
    return true;
}

size_t vector_largo(vector_t* vector){
    if(vector == NULL) return 0;

    return vector->tam;
}

vector_t* vector_crear(size_t tam) {
    vector_t* vector = malloc(sizeof(vector_t));

    if (vector == NULL) {
        return NULL;
    }
    vector->datos = malloc(tam * sizeof(void *));

    if (tam > 0 && vector->datos == NULL) {
        free(vector);
        return NULL;
    }
    vector->tam = tam;
    vector->cantidad = 0;
    return vector;
}

bool vector_redimensionar(vector_t* vector, size_t tam_nuevo) {
    void ** datos_nuevo = realloc(vector->datos, tam_nuevo * sizeof(void *));

    if (tam_nuevo > 0 && datos_nuevo == NULL) {
        return false;
    }

    vector->datos = datos_nuevo;
    vector->tam = tam_nuevo;
    return true;
}
