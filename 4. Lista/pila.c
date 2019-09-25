#include "pila.h"
#include <stdlib.h>

#define SIZE_INIT    10 //Tamaño inicial de la pila
#define SCALE_FACTOR 2 //Factor de escala para el redimensionamiento de la pila
#define ALFA         4 //Constante para evaluar achicamiento de la pila

/* Definición del struct pila proporcionado por la cátedra.
 */
 struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/
pila_t* pila_crear(void){
    pila_t* aux;

    if((aux =(pila_t *)malloc(sizeof(pila_t))) == NULL) return NULL;
    if((aux->datos =(void **)malloc(sizeof(void*) * SIZE_INIT)) == NULL) return NULL;
    aux->capacidad=SIZE_INIT;
    aux->cantidad=0;
    return aux;
}

void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
    return pila->cantidad == 0;
}

bool pila_redimensionar(pila_t *pila, size_t cantidad){
    if((pila->datos =(void**)realloc(pila->datos,sizeof(void*) * cantidad)) == NULL)
        return false;

    pila->capacidad = cantidad;
    return true;
}

bool pila_apilar(pila_t *pila, void* valor){
    if(pila->cantidad == pila->capacidad)
        if(pila_redimensionar(pila, pila->capacidad * SCALE_FACTOR) == false)
            return false;

    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;
    return true;
}

void* pila_ver_tope(const pila_t *pila){
    return pila->cantidad == 0? NULL : pila->datos[pila->cantidad - 1];
}

void* pila_desapilar(pila_t *pila){
    if(pila->cantidad == 0) return NULL;
    if(pila->cantidad * ALFA <= pila->capacidad)
        if(pila_redimensionar(pila, pila->capacidad / SCALE_FACTOR) == false)
            return NULL;

    void* aux;

    aux = pila->datos[pila->cantidad - 1];
    pila->datos[pila->cantidad - 1] = NULL;
    pila->cantidad = pila->cantidad - 1;
    return aux;
}
