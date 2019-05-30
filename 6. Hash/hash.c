#include "hash.h"
#include "lista.h"
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

struct hash {
	lista_t** tabla;
	size_t cantidad;
	size_t tam;
	hash_destruir_dato_t destruir_dato;
};

typedef struct nodo_hash {
	void* dato;
	char* clave;
}nodo_hash_t;

struct hash_iter{
    const hash_t* hash;
    size_t pos;
    lista_iter_t* lista_iter;
};

//Funcion de Hash JBD2
size_t f_hash(const char *str)
{
	size_t hash = 5381;
    int c;

    while ((c = *str++)) //Compilador pedia poner doble parentesis
        hash = ((hash << 5) + hash) + (size_t)c; /* hash * 33 + c */

    return hash;
}
/* *****************************************************************
 *                    PRIMITIVAS DE NODO HASH
 * *****************************************************************/

nodo_hash_t* nodo_hash_crear(const char *clave, void *dato){
	nodo_hash_t* aux = malloc(sizeof(nodo_hash_t));
    if(!aux) return NULL;

	aux->clave = malloc(sizeof(char) * (strlen(clave) + 1));
	if(!aux->clave) {
		free(aux);
		return NULL;
	}
	strcpy(aux->clave,clave);
	aux->dato = dato;
	return aux;
}

void nodo_hash_destruir(nodo_hash_t* nodo_hash){
	free(nodo_hash->clave);
	free(nodo_hash);
}
/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/
char * strdup(const char * str){ //El usuario se encarga de liberar la memoria
	char * str2 = malloc(sizeof(char) * (strlen(str) + 1));
	if(!str2) return 0;

	strcpy(str2,str);
	return str2;
}

lista_t** crear_tabla(size_t tam){
	lista_t** aux;

	aux = malloc(tam * sizeof(lista_t *));
	if(!aux) return NULL;

	size_t i;
	for (i = 0; i < tam; i++) {
		aux[i] = lista_crear();
		if (!aux[i]) {
			for(size_t j = 0; j<i; j++) {
				lista_destruir(aux[j], NULL);
			}
			free(aux);
			return NULL;
		}
	}

	return aux;
}

void destruir_tabla(hash_t* hash) {
	for(size_t i = 0; i < hash->tam; i++){
		lista_destruir(hash->tabla[i],NULL);
	}
	free(hash->tabla);
}

nodo_hash_t* buscar_nodo(lista_iter_t* iter, const char* clave) {
	while (!lista_iter_al_final(iter)) {
		nodo_hash_t* aux = lista_iter_ver_actual(iter);
		if (!strcmp(aux->clave, clave)) {
			return aux;
		}
		lista_iter_avanzar(iter);
	}
	return NULL;
}

/* *****************************************************************
*                    PRIMITIVAS DE HASH
* *****************************************************************/
hash_t * hash_crear(hash_destruir_dato_t destruir_dato){
	hash_t* hash = malloc(sizeof(hash_t));
	if(!hash) return NULL;

	hash->tabla = crear_tabla(TAM_INICIAL);
	if(!hash->tabla){
		free(hash);
		return NULL;
	}
	hash->tam = TAM_INICIAL;
	hash->destruir_dato = destruir_dato;
	hash->cantidad = 0;
	return hash;
}

bool redimensionar_hash(hash_t * hash,size_t new_size){
	bool status = true;
	lista_iter_t* iter;
	nodo_hash_t*  aux;
	hash_t* new = malloc(sizeof(hash_t));
	if(!new) return false;

	new->tabla = crear_tabla(new_size);
	if(!new->tabla){
		free(new);
		return false;
	}
	new->tam = new_size;
	new->cantidad = 0;
	for(size_t i = 0; i < hash->tam; i++){
		iter = lista_iter_crear(hash->tabla[i]);
		while(!lista_iter_al_final(iter)){
			aux = lista_iter_ver_actual(iter);
			size_t pos = f_hash(aux->clave) % new->tam;
			if (!lista_insertar_ultimo(new->tabla[pos], aux)) {
				status=false;
				break;
			}
			new->cantidad++;
			lista_iter_avanzar(iter);
		}
		lista_iter_destruir(iter);
		if(!status) {
			destruir_tabla(new);
			break;
		}
	}

	if(status){
		destruir_tabla(hash);
		hash->tabla = new->tabla;
		hash->tam = new->tam;
		hash->cantidad = new->cantidad;
	}
	free(new);
	return status;
}
bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
	nodo_hash_t*  aux;
	char * aux_str = strdup(clave);
	size_t pos = f_hash(aux_str) % hash->tam;
	lista_iter_t* iter = lista_iter_crear(hash->tabla[pos]);
	if(!iter) return false;
	free(aux_str);

	aux = buscar_nodo(iter, clave);
	if (aux) {
		void* dato_viejo = aux->dato;
		aux->dato = dato;
		if (hash->destruir_dato != NULL) (hash->destruir_dato)(dato_viejo);
	} else {
		aux = nodo_hash_crear(clave,dato);
		if(!aux){
			lista_iter_destruir(iter);
			return false;
		}
		lista_iter_insertar(iter,aux);
		hash->cantidad++;
		if(hash->cantidad > (hash->tam * NUM_REDIMENSION)) {
			if(!redimensionar_hash(hash,NUM_REDIMENSION*hash->tam)){
				lista_iter_destruir(iter);
				return false;
			}
		}
	}
	lista_iter_destruir(iter);
	return true;
}

void* hash_borrar(hash_t *hash, const char *clave) {
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
}

void * hash_obtener(const hash_t *hash, const char *clave){
	nodo_hash_t * aux;
	char * aux_str = strdup(clave);
	size_t pos = f_hash(aux_str) % hash->tam;
	lista_iter_t * iter = lista_iter_crear(hash->tabla[pos]);
	if(!iter) return NULL;
	free(aux_str);

	aux = buscar_nodo(iter, clave);
	if (aux) {
		aux = lista_iter_ver_actual(iter);
		void* dato = aux->dato;
		lista_iter_destruir(iter);
		return dato;
	}
	lista_iter_destruir(iter);
	return NULL;
}

bool hash_pertenece(const hash_t *hash, const char *clave){
	char * aux_str = strdup(clave);
	size_t pos = f_hash(aux_str) % hash->tam;
	lista_iter_t* iter = lista_iter_crear(hash->tabla[pos]);
	if(!iter) return NULL;
	free(aux_str);

	if (buscar_nodo(iter, clave)) {
		lista_iter_destruir(iter);
		return true;
	}
	lista_iter_destruir(iter);
	return false;
}

size_t hash_cantidad(const hash_t *hash){
	return hash->cantidad;
}

void hash_destruir(hash_t *hash){
	lista_iter_t* iter;
	nodo_hash_t* aux;

	for(size_t i = 0; i < hash->tam; i++){
		iter = lista_iter_crear(hash->tabla[i]);
		while(!lista_iter_al_final(iter)){
			aux = lista_iter_ver_actual(iter);
			if((hash->destruir_dato) != NULL) {
				(hash->destruir_dato)(aux->dato);
			}

			nodo_hash_destruir(aux);
			lista_iter_borrar(iter);
		}
		lista_iter_destruir(iter);
		lista_destruir(hash->tabla[i],NULL);
	}
	free(hash->tabla);
	free(hash);
	return;
}
/* *****************************************************************
 *                 PRIMITIVAS DE ITERADOR HASH
 * *****************************************************************/

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
   }
