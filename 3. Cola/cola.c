// Alumno: Daniel Bizari
// Padrón: 100445
// Correctora: Camila Dvorkin

#include "cola.h"
#include <stdlib.h>

// Definición del struct cola y nodo.

typedef struct nodo nodo_t;

struct nodo{
    void* dato;
    nodo_t* siguiente;
};

struct cola{
    nodo_t* primero;
    nodo_t* ultimo;
};

typedef void (*destructor_t)(void*);

/* *****************************************************************
 *                    PRIMITIVAS DE NODO
 * *****************************************************************/

nodo_t* nodo_crear(void* valor){
	nodo_t* aux = malloc(sizeof(nodo_t));

    if(!aux) return NULL;

	aux->dato = valor;
	aux->siguiente = NULL;
	return aux;
}

void nodo_destruir(nodo_t* nodo){
	free(nodo);
}
/* *****************************************************************
*                    PRIMITIVAS DE LA COLA
* *****************************************************************/
cola_t* cola_crear(void){
    cola_t* aux = malloc(sizeof(cola_t));

    if(!aux) return NULL;

    aux->primero = NULL;
    aux->ultimo = NULL;
    return aux;
}

void cola_destruir(cola_t *cola, destructor_t destructor){
    nodo_t* aux,*aux2;

    if(cola_esta_vacia(cola) == true){
        free(cola);
        return;
    }
    for(aux = cola->primero; aux != NULL; aux = aux2){
        aux2 = aux->siguiente;
        if(destructor != NULL)
            destructor(aux->dato);

        nodo_destruir(aux);
    }
    free(cola);
}

bool cola_esta_vacia(const cola_t *cola){
	return (cola->primero == NULL);
}

bool cola_encolar(cola_t *cola, void* valor){
	nodo_t* aux;

	if((aux = nodo_crear(valor)) == NULL) return false;
	if(cola_esta_vacia(cola) == true)
		cola->primero = aux;
	else
		cola->ultimo->siguiente = aux;

	cola->ultimo = aux;
	return true;
}

void* cola_ver_primero(const cola_t *cola){
	return cola_esta_vacia(cola) == true ? NULL : cola->primero->dato;
}

void* cola_desencolar(cola_t *cola){
	if(cola_esta_vacia(cola) == true) return NULL;
	void* dato = cola_ver_primero(cola); //Apunto al dato para luego devolverlo
	nodo_t* aux;

	aux = cola->primero; //Apunto al prmer nodo
	cola->primero = cola->primero->siguiente; //Reacomodar cola, apuntando al elemento siguiente en la cola
	nodo_destruir(aux); //Destruir nodo
	return dato;
}
