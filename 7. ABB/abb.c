#include "abb.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
/* *****************************************************************
 *                    DEFINICION DE STRUCTS
 * *****************************************************************/

typedef struct nodo_abb nodo_abb_t;

struct nodo_abb{
 	void* dato;
 	char* clave;
	nodo_abb_t * izq;
	nodo_abb_t * der;
 };

struct abb {
	nodo_abb_t* raiz;
	size_t cantidad;
	abb_comparar_clave_t comparar_clave;
	abb_destruir_dato_t destruir_dato;
};
/*
struct abb_iter{
    //???
};*/

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/
char * strdup(const char * str){ //El usuario se encarga de liberar la memoria
	char * str2 = malloc(sizeof(char) * (strlen(str) + 1));
	if(!str2) return NULL;

	strcpy(str2,str);
	return str2;
}

nodo_abb_t* buscar_nodo(nodo_abb_t* nodo, const char* clave,abb_comparar_clave_t cmp,nodo_abb_t* aux_padre) {
    nodo_abb_t* aux;

    if(nodo == NULL) return NULL;

    if(!cmp(nodo->clave, clave))
        return nodo;
    else if(cmp(nodo->clave, clave) > 0){ // nodo > clave Entonce debo buscar a la izq
        aux_padre = nodo;
        aux = buscar_nodo(nodo->izq,clave,cmp,aux_padre);
    }else{
        aux_padre = nodo;
        aux = buscar_nodo(nodo->der,clave,cmp,aux_padre);
    }
    return aux;
}
void print_arbol(nodo_abb_t * nodo){
    if(nodo == NULL) return;

    print_arbol(nodo->izq);
    printf("%d\n",*(int*)nodo->dato);
    print_arbol(nodo->der);
    return;
}

/* *****************************************************************
 *                    PRIMITIVAS DE NODO ABB
 * *****************************************************************/

nodo_abb_t* nodo_abb_crear(const char *clave, void *dato){
	nodo_abb_t* aux = malloc(sizeof(nodo_abb_t));
    if(!aux) return NULL;

	if((aux->clave = strdup(clave)) == NULL){
        free(aux);
        return NULL;
    }
	aux->dato = dato;
    aux->izq  = NULL;
    aux->der  = NULL;
	return aux;
}

void nodo_abb_destruir(nodo_abb_t* nodo_abb){
	free(nodo_abb->clave);
	free(nodo_abb);
    //Mas vale que izq y der sean NULL sino se va a perder memoria si se pierden las referencias
}


/* *****************************************************************
*                    PRIMITIVAS DE ABB
* *****************************************************************/
abb_t * abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t* abb = malloc(sizeof(abb_t));
	if(!abb) return NULL;

	abb->raiz = NULL;
	abb->comparar_clave = cmp;
	abb->destruir_dato = destruir_dato;
	abb->cantidad = 0;
	return abb;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	nodo_abb_t*  aux_nodo,*new;
  nodo_abb_t* aux_padre = NULL;

  aux_nodo = buscar_nodo(arbol->raiz, clave, arbol->comparar_clave,aux_padre);
	if (aux_nodo) {
		void* dato_viejo = aux_nodo->dato;
		aux_nodo->dato = dato;
		if (arbol->destruir_dato != NULL) (arbol->destruir_dato)(dato_viejo);
	} else {
		new = nodo_abb_crear(clave,dato);
    if(!new) return false;
    if(!arbol->raiz) {
      arbol->raiz = new;
    } else if ((arbol->comparar_clave)(aux_padre->clave, clave) > 0) {
      aux_padre->izq = new;
    } else {
      aux_padre->der = new;
    }
		arbol->cantidad++;
	}
	return true;
}

size_t cant_hijos(abb_t* arbol, char* clave, nodo_abb_t* aux, nodo_abb_t* aux_padre) {
  aux = buscar_nodo(arbol->raiz, clave, arbol->comparar_clave, aux_padre);
  if (aux == NULL) return NULL;
  if (!aux->der && !aux->izq) return 0;
  if (aux->der && aux->izq) return 2;
  return 1;
}

void *abb_borrar(abb_t *arbol, const char *clave) {
  nodo_abb_t* aux;
  nodo_abb_t* padre;
  void* dato;
  size_t hijos = cant_hijos(arbol, clave, aux, padre);
  if (hijos == NULL) return NULL;
  dato = aux->dato;
  if (hijos == 0) {
    if (arbol->comparar_clave(padre->clave, clave) > 0 ) {
      padre->izq = NULL;
    } else {
      padre->der = NULL;
    }
    nodo_abb_destruir(aux);
  } else if (hijos == 1) {
    nodo_abb_t* hijo;
    if (aux->izq) {
      hijo = aux->izq;
    } else {
      hijo = aux->der;
    }
    if (arbol->comparar_clave(padre->clave, clave) > 0) {
      padre->izq = hijo;
    } else {
      padre->der = hijo;
    }
  }
  return dato;
}

void* abb_obtener(const abb_t *arbol, const char *clave){
	nodo_abb_t* aux_padre = NULL;
  nodo_abb_t* aux = buscar_nodo(arbol->raiz, clave, arbol->comparar_clave,aux_padre);
  if (!aux) return NULL;
	return aux->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
  nodo_abb_t* aux_padre = NULL;
	return (buscar_nodo(arbol->raiz, clave, arbol->comparar_clave,aux_padre) != NULL) ? true : false;
}

size_t abb_cantidad(const abb_t *arbol){
	return arbol->cantidad;
}


void _abb_destruir(nodo_abb_t* nodo, abb_destruir_dato_t destruir_dato) {
  if (!nodo) return;
  _abb_destruir(nodo->izq, destruir_dato);
  if (destruir_dato) {
    destruir_dato(nodo->dato);
  }
  _abb_destruir(nodo->der, destruir_dato);
}

void abb_destruir(abb_t *arbol){
	_abb_destruir(arbol->raiz, arbol->destruir_dato);
	free(abb);
	return;
}

 /******************************************************************
  *                 PRIMITIVAS DE ITERADOR INTERNO
  ******************************************************************/

void _abb_in_order(nodo_abb_t* nodo, bool visitar(const char* clave, void* dato, void* extra), void* extra, bool estado) {
  if (!nodo) return;
  _abb_in_order(nodo->izq, visitar, extra, estado);
  estado = visitar(nodo->clave, nodo->dato, extra);
  if (!estado) return;
  _abb_in_order(nodo->der, visitar, extra, estado);
}
void abb_in_order(abb_t *arbol, bool visitar(const char* clave, void* dato, void* extra), void *extra) {
  bool estado = true;
  _abb_in_order(arbol->raiz, visitar, extra, estado);

}


 /******************************************************************
  *                 PRIMITIVAS DE ITERADOR EXTERNO 
  ******************************************************************/

//funciones auxiliares
void _apilar_izq(abb_iter_t* iter, nodo_abb_t* nodo) {
  if (!nodo) return;
  pila_apilar(iter->pila_aux, nodo);
  _apilar_izq(iter, nodo->izq);
}

void apilar_izq(abb_iter_t* iter, nodo_abb_t* nodo) {
  if (!nodo) {
    nodo = iter->abb->raiz;
    pila_apilar(iter->pila_aux, nodo);
  }
  _apilar_izq(iter, nodo->izq);

}
// fin de funciones auxiliares
typedef struct abb_iter abb_iter_t;

struct abb_iter {
  abb_t* abb;
  pila_t* pila_aux;
}


 abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {
  abb_iter_t* iter = malloc(sizeof(abb_iter_t));
  if (!iter) return NULL;

  pila_t* pila = crear_pila();
  if (!pila) return NULL;

  iter->pila_aux = pila;
  iter->abb = arbol;

  apilar_izq(iter, NULL);

 }

bool abb_iter_in_avanzar(abb_iter_t *iter) {
  if (pila_esta_vacia(iter->pila_aux)) return false;
  nodo_abb_t* aux = pila_desapilar(iter->pila_aux);
  if (aux->der) {
    pila_apilar(iter->pila_aux, aux->der);
    apilar_izq(iter, aux->der);
  }
  return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter) {
  nodo_abb_t* aux = pila_ver_tope(iter->pila_aux);
  if (!aux) return NULL;
  return aux->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter) {
  return pila_esta_vacia(iter->pila_aux);
}

void abb_iter_in_destruir(abb_iter_t* iter) {
  pila_destruir(iter->pila_aux);
  free(iter);
}

int main(int argc, char const *argv[]) {
    abb_t * arbol = abb_crear(strcmp,NULL);
    int dato=3;
    int dato2=33;
    int dato3=4;
    int dato4=5;
    int dato5=6;

    abb_guardar(arbol,"cat",(void*)&dato);
    abb_guardar(arbol,"muricio",(void*)&dato2);
    abb_guardar(arbol,"jumanji",(void*)&dato3);
    abb_guardar(arbol,"manijen",(void*)&dato4);
    abb_guardar(arbol,"aprobar",(void*)&dato5);
    dato++;
    dato2++;
    dato3++;
    dato4++;
    dato5++;
    print_arbol(arbol->raiz);
    printf("compila xd\n" );
    return 0;
}
