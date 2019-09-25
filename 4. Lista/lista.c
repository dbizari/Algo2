// Alumno: Daniel Bizari
// Padrón: 100445
// Correctora: Camila Dvorkin

#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

// Definición del struct lista y nodo.

typedef struct nodo nodo_t;

struct nodo{
    void* dato;
    nodo_t* siguiente;
};

struct lista{
    nodo_t* primero;
    nodo_t* ultimo;
    size_t largo;
};

struct lista_iter{
    lista_t* lista;
    nodo_t* ant;
    nodo_t* act;
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
*                    PRIMITIVAS DE LA LISTA
* *****************************************************************/
lista_t* lista_crear(void){
    lista_t* aux = malloc(sizeof(lista_t));

    if(!aux) return NULL;

    aux->primero = NULL;
    aux->ultimo = NULL;
    aux->largo = 0;
    return aux;
}

void lista_destruir(lista_t *lista, destructor_t destructor){
    nodo_t* aux,*aux2;

    if(lista_esta_vacia(lista) == true){
        free(lista);
        return;
    }
    for(aux = lista->primero; aux != NULL; aux = aux2){
        aux2 = aux->siguiente;
        if(destructor != NULL)
            destructor(aux->dato);

        nodo_destruir(aux);
        lista->largo--;
    }
    free(lista);
}

bool lista_esta_vacia(const lista_t *lista){
	return (lista->primero == NULL);
}

bool lista_insertar_primero(lista_t *lista, void *dato){
    nodo_t * aux_nuevo,* aux_prim = lista->primero;
    bool is_empty;

    if((aux_nuevo = nodo_crear(dato)) == NULL) return false;
    is_empty = lista_esta_vacia(lista) == true ? true : false;
    lista->primero = aux_nuevo;
    if(is_empty)
        lista->ultimo = aux_nuevo;
    else
        lista->primero->siguiente = aux_prim;

    lista->largo++;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
    nodo_t * aux_nuevo;

    if((aux_nuevo = nodo_crear(dato)) == NULL) return false;
    if(lista_esta_vacia(lista) == true)
        lista->primero = aux_nuevo;
    else
        lista->ultimo->siguiente = aux_nuevo;

    lista->ultimo = aux_nuevo;
    lista->largo++;
    return true;
}

void* lista_ver_primero(const lista_t *lista){
    return lista_esta_vacia(lista) == true ? NULL : lista->primero->dato;
}

void* lista_ver_ultimo(const lista_t* lista){
    return lista_esta_vacia(lista) == true ? NULL : lista->ultimo->dato;
}

size_t lista_largo(const lista_t *lista){
    return lista->largo;
}

void* lista_borrar_primero(lista_t *lista){
    if(lista_esta_vacia(lista) == true) return NULL;
	void*  dato = lista_ver_primero(lista); //Apunto al dato para luego devolverlo
	nodo_t* aux = lista->primero; //Apunto al prmer nodo

	lista->primero = lista->primero->siguiente; //Reacomodar lista
	nodo_destruir(aux); //Destruir nodo
    lista->largo--;
	return dato;
}

/* *****************************************************************
 *                 PRIMITIVAS DE ITERADOR EXTERNO
 * *****************************************************************/

lista_iter_t *lista_iter_crear(lista_t *lista){
    lista_iter_t* aux = malloc(sizeof(lista_iter_t));

    if(aux == NULL) return NULL;
    aux->lista = lista;
    aux->ant = NULL;
    aux->act = lista->primero;
    return aux;
}

bool lista_iter_avanzar(lista_iter_t *iter){
    if(iter->act == NULL) return false; //Ya llego al final de la lista;
    iter->ant = iter->act;
    iter->act = iter->act->siguiente;
    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
    return lista_iter_al_final(iter) ? NULL : iter->act->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
    return (iter->act == NULL);
}

void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
    nodo_t* aux_nuevo;

    if((aux_nuevo = nodo_crear(dato)) == NULL) return false;

    if(iter->ant == NULL){    //insertar al principio
        aux_nuevo->siguiente = iter->act;
        iter->lista->primero = aux_nuevo;
    }else{ // resto de los casos
        iter->ant->siguiente = aux_nuevo;
        iter->ant->siguiente->siguiente = iter->act;
    }
    iter->act = aux_nuevo;
    if(iter->act->siguiente == NULL) //Si es el ultimo nodo actualizar lista
        iter->lista->ultimo = aux_nuevo;

    iter->lista->largo++;
    return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
    void* dato = lista_iter_ver_actual(iter);
    nodo_t* aux;
    
    if(iter->act == NULL) return NULL;
    if(iter->ant == NULL)    //eliminar primer nodo
        iter->lista->primero = iter->act->siguiente;
    else
        iter->ant->siguiente = iter->act->siguiente;

    aux = iter->act;
    iter->act = iter->act->siguiente;
    nodo_destruir(aux);
    if(iter->act == NULL) //Si es el ultimo nodo actualizar lista
        iter->lista->ultimo = iter->ant;

    iter->lista->largo--;
    return dato;
}
/* *****************************************************************
 *                 PRIMITIVAS DE ITERADOR INTERNO
 * *****************************************************************/
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    nodo_t* aux = lista->primero;

    while(aux != NULL){
        if(visitar(aux->dato,extra) == false) break;
        aux = aux->siguiente;
    }
}
