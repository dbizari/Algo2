#include "abb.h"
#include "pila.h"
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

struct abb_iter {
  const abb_t* abb;
  pila_t* pila_aux;
};

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/
char * strdup(const char * str){ //El usuario se encarga de liberar la memoria
	char * str2 = malloc(sizeof(char) * (strlen(str) + 1));
	if(!str2) return NULL;

	strcpy(str2,str);
	return str2;
}

nodo_abb_t* buscar_nodo(const abb_t* arbol, const char* clave, nodo_abb_t ** aux_padre) {
    nodo_abb_t * aux_nodo = arbol->raiz;

    while(aux_nodo != NULL){

        if(!(arbol->comparar_clave)(aux_nodo->clave, clave)) {
            return aux_nodo;
        } else if((arbol->comparar_clave)(aux_nodo->clave, clave) > 0) { // aux_nodo > clave Entonce debo buscar a la izq
            *aux_padre = aux_nodo;
            aux_nodo = aux_nodo->izq;
        }else{
            *aux_padre = aux_nodo;
            aux_nodo = aux_nodo->der;
        }
    }
    return NULL;
}

void print_arbol(nodo_abb_t * nodo){
    if(nodo == NULL) return;

    print_arbol(nodo->izq);
    printf("%d\n",*(int*)nodo->dato);
    print_arbol(nodo->der);
    return;
}
void cambiar_referencia(abb_t* arbol, const char* clave, nodo_abb_t *padre, nodo_abb_t* hijo) {
  if (arbol->comparar_clave(padre->clave, clave) > 0) {
    padre->izq = hijo;
  } else {
    padre->der = hijo;
  }
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

void nodo_abb_destruir(nodo_abb_t* nodo_abb,abb_destruir_dato_t destruir_dato){
	free(nodo_abb->clave);
    if(destruir_dato != NULL){
        destruir_dato(nodo_abb->dato);
    }
	free(nodo_abb);
    return;
    //Mas vale que izq y der sean NULL sino se va a perder memoria si se pierden las referencias
}

void destruir_nodos(nodo_abb_t * nodo,abb_destruir_dato_t destruir_dato){
    if(nodo == NULL) return;

    destruir_nodos(nodo->izq,destruir_dato);
    destruir_nodos(nodo->der,destruir_dato);
    nodo_abb_destruir(nodo,destruir_dato);
    return;
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
	nodo_abb_t*  aux_nodo, *new, *aux_padre = NULL;

    aux_nodo = buscar_nodo(arbol,clave,&aux_padre);

	if (aux_nodo) {
		void* dato_viejo = aux_nodo->dato;
		aux_nodo->dato = dato;
		if (arbol->destruir_dato != NULL) (arbol->destruir_dato)(dato_viejo);
	} else {
		new = nodo_abb_crear(clave,dato);
        if(!new) return false;
        if(!arbol->raiz) {
            arbol->raiz = new;
        } else {
          cambiar_referencia(arbol, clave, aux_padre, new);
        }
		arbol->cantidad++;
  }

	return true;
}

size_t cant_hijos(nodo_abb_t* aux) {
  if (!aux->der && !aux->izq) return 0;
  if (aux->der && aux->izq) return 2;
  return 1;
}

nodo_abb_t* buscar_reemplazante(nodo_abb_t* act) {
  nodo_abb_t *remp = NULL;
  nodo_abb_t* aux;
  aux = act->der;
  while(aux) {
    remp = aux;
    aux = aux->izq;
  }
  return remp;

}

void _borrar_hoja(abb_t* arbol, nodo_abb_t* nodo, nodo_abb_t* padre, const char *clave) {
  if (padre) {
    cambiar_referencia(arbol, clave, padre, NULL);
  } else {
    arbol->raiz = NULL;
  }
  nodo_abb_destruir(nodo, NULL);
}

void _borrar_caso_1(abb_t* arbol, nodo_abb_t* nodo, nodo_abb_t* padre, const char* clave) {
  nodo_abb_t* hijo = nodo->izq ? nodo->izq : nodo->der;
  if (padre) {
    cambiar_referencia(arbol, clave, padre, hijo);
  } else {
    arbol->raiz = hijo;
  }
  nodo_abb_destruir(nodo, NULL);
}

bool _borrar_caso_2(abb_t* arbol, nodo_abb_t* nodo, nodo_abb_t* padre) {
  nodo_abb_t* remp = buscar_reemplazante(nodo);
  char* clave_remp = strdup(remp->clave);
  if (!clave_remp) return false;
  void* dato_remp = abb_borrar(arbol, remp->clave);
  free(nodo->clave);
  nodo->clave = clave_remp;
  nodo->dato = dato_remp;
  return true;
}

void* abb_borrar(abb_t* arbol, const char* clave){
  nodo_abb_t* aux_nodo, *padre = NULL;
  void* dato;
  size_t hijos = 0;
  aux_nodo = buscar_nodo(arbol, clave, &padre);
  if (!aux_nodo) return NULL;
  hijos = cant_hijos(aux_nodo);
  dato = aux_nodo->dato;
  if (hijos == 0) {
    _borrar_hoja(arbol, aux_nodo, padre, clave);
  } else if (hijos == 1) {
    _borrar_caso_1(arbol, aux_nodo, padre, clave);
  } else {
    if (!_borrar_caso_2(arbol, aux_nodo, padre)) return NULL;
  }
  if (hijos == 0 || hijos == 1)arbol->cantidad--;
  return dato;
}

void * abb_obtener(const abb_t *arbol, const char *clave){
	nodo_abb_t * aux_padre = NULL,*aux;
    if((aux = buscar_nodo(arbol,clave,&aux_padre)) != NULL)
	   return aux->dato;
    else
        return NULL;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
    nodo_abb_t * aux_padre  = NULL;

	return (buscar_nodo(arbol,clave,&aux_padre) != NULL);
}

size_t abb_cantidad(abb_t *arbol){
	return arbol->cantidad;
}

void abb_destruir(abb_t *arbol){
	destruir_nodos(arbol->raiz,arbol->destruir_dato);
	free(arbol);
	return;
}

 /******************************************************************
  *                 PRIMITIVAS DE ITERADOR INTERNO
  ******************************************************************/

bool _abb_in_order(nodo_abb_t* nodo, bool visitar(const char* clave, void* dato, void* extra), void* extra) {
  if (!nodo) return true;
  if (!_abb_in_order(nodo->izq, visitar, extra)) return false;
  if (!visitar(nodo->clave, nodo->dato, extra)) return false;
  return _abb_in_order(nodo->der, visitar, extra);
}

void abb_in_order(abb_t *arbol, bool visitar(const char* clave, void* dato, void* extra), void *extra) {
  _abb_in_order(arbol->raiz, visitar, extra);

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
  if (nodo) {
    pila_apilar(iter->pila_aux, nodo);
    _apilar_izq(iter, nodo->izq);
  }

}
// fin de funciones auxiliares

 abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {
  abb_iter_t* iter = malloc(sizeof(abb_iter_t));
  if (!iter) return NULL;

  pila_t* pila = pila_crear();
  if (!pila) return NULL;

  iter->pila_aux = pila;
  iter->abb = arbol;

  apilar_izq(iter, arbol->raiz);
  return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter) {
  if (pila_esta_vacia(iter->pila_aux)) return false;
  nodo_abb_t* aux = pila_desapilar(iter->pila_aux);
  apilar_izq(iter, aux->der);
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
