#include "abb.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#define TAM_INICIAL 109
#define NUM_REDIMENSION 2
#define NUM_VERIFICACION 4
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

nodo_abb_t* buscar_nodo(nodo_abb_t* nodo, const char* clave,abb_comparar_clave_t cmp,nodo_abb_t ** aux_padre) {
    nodo_abb_t* aux;

    if(nodo == NULL) return NULL;

    if(!cmp(nodo->clave, clave))
        return nodo;
    else if(cmp(nodo->clave, clave) > 0){ // nodo > clave Entonce debo buscar a la izq
        *aux_padre = nodo;
        aux = buscar_nodo(nodo->izq,clave,cmp,aux_padre);
    }else{
        *aux_padre = nodo;
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
    nodo_abb_t**  aux_padre = NULL;

    aux_nodo = buscar_nodo(arbol->raiz, clave, arbol->comparar_clave,aux_padre);
	if (aux_nodo) {
		void* dato_viejo = aux_nodo->dato;
		aux_nodo->dato = dato;
		if (arbol->destruir_dato != NULL) (arbol->destruir_dato)(dato_viejo);
	} else {
		new = nodo_abb_crear(clave,dato);
        if(!new) return false;

        if(!arbol->raiz)
            arbol->raiz = new;
        else if((arbol->comparar_clave)(aux_nodo->clave, clave) > 0)
            (*aux_padre)->izq = new;
        else
            (*aux_padre)->der = new;

		arbol->cantidad++;
	}
	return true;
}
/*
void* abb_borrar(abb_t *arbol, const char *clave) {
	void*         dato;
	nodo_hash_t*  aux;
	char * aux_str = strdup(clave);
	size_t pos = f_hash(aux_str) % hash->tam;
	lista_iter_t* iter = lista_iter_crear(hash->tabla[pos]);
	if(!iter) return NULL;
	free(aux_str);

	aux = buscar_nodo(iter, clave);
	if (aux) {
		aux = lista_iter_ver_actual(iter);
		dato = aux->dato;
		nodo_hash_destruir(aux);
		hash->cantidad--;
		lista_iter_borrar(iter);
		lista_iter_destruir(iter);
		if(hash->cantidad < (hash->tam / NUM_VERIFICACION) && hash->tam > TAM_INICIAL*NUM_VERIFICACION) {
			if(!redimensionar_hash(hash,(hash->tam)/NUM_REDIMENSION)) {
				return NULL;
			}
		}
		return dato;
	}
	lista_iter_destruir(iter);
	return NULL;
}*/

void * abb_obtener(const abb_t *arbol, const char *clave){
	nodo_abb_t ** aux_padre = NULL;

	return buscar_nodo(arbol->raiz, clave, arbol->comparar_clave,aux_padre);
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
    nodo_abb_t ** aux_padre = NULL;

	return (buscar_nodo(arbol->raiz, clave, arbol->comparar_clave,aux_padre) != NULL);
}

size_t abb_cantidad(const abb_t *arbol){
	return arbol->cantidad;
}
/*
void abb_destruir(abb_t *arbol){
	//HAY QUE LIBERAR TODOS LOS NODOS Y SUS RESPECTIVOS DATOS
	free(abb);
	return;
}*/

/* *****************************************************************
 *                 PRIMITIVAS DE ITERADOR HASH
 * *****************************************************************

  //funcion auxiliar
  lista_iter_t* _buscar_no_vacio(hash_iter_t* iter, size_t pos) {
  	lista_iter_t* aux = NULL;
  	for (; pos < iter->hash->tam; pos++) {
  		if (!lista_esta_vacia(iter->hash->tabla[pos]) || pos == (iter->hash->tam -1)) {
      		iter->pos = pos;
      		aux = lista_iter_crear(iter->hash->tabla[pos]);
      		break;
  		}
  	}
  	if (!aux) return NULL;
  	return aux;
  }

   // Crea iterador
   hash_iter_t * hash_iter_crear(const hash_t *hash){
  	hash_iter_t* iter = malloc(sizeof(hash_iter_t));

      if(iter == NULL) return NULL;
      iter->hash = hash;

     	if (hash->cantidad == 0) {
     		iter->pos = hash->tam -1;
     		iter->lista_iter = lista_iter_crear(hash->tabla[hash->tam-1]);

     	} else {
     		iter->pos = 0;
     		size_t pos = 0;
     		iter->lista_iter = _buscar_no_vacio(iter, pos);

     	}

     	if (iter->lista_iter == NULL) {
     		free(iter);
     		return NULL;
     	}

      return iter;
   }

   // Avanza iterador
   bool hash_iter_avanzar(hash_iter_t *iter) {
   	if(hash_iter_al_final(iter)) return false;

   	lista_iter_avanzar(iter->lista_iter);

   	if (lista_iter_al_final(iter->lista_iter) && !hash_iter_al_final(iter)) {
   		lista_iter_destruir(iter->lista_iter);
   		size_t pos = iter->pos +1;
   		iter->lista_iter = _buscar_no_vacio(iter, pos);
   		if (iter->lista_iter == NULL) return false;
   	}

   	return true;
   }

   // Devuelve clave actual, esa clave no se puede modificar ni liberar.
   const char *hash_iter_ver_actual(const hash_iter_t *iter) {
   	if (hash_iter_al_final(iter)) return NULL;

   	nodo_hash_t* aux = lista_iter_ver_actual(iter->lista_iter);
   	return aux->clave;
   }

   // Comprueba si terminó la iteración
   bool hash_iter_al_final(const hash_iter_t *iter) {
   	if(iter->pos == (iter->hash->tam - 1) && lista_iter_al_final(iter->lista_iter)) return true;
   	return false;
   }

   // Destruye iterador
   void hash_iter_destruir(hash_iter_t* iter) {
   	lista_iter_destruir(iter->lista_iter);
   	free(iter);
}*/
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
