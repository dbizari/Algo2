#define _POSIX_C_SOURCE 200809L //Para getline()
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "strutil.h"
#include "hash.h"
#include "heap.h"
#include "tag.h"
#include "pila.h"
#include "count_min_sketch.h"

#define ARGS  	  3
#define N_POS  	  1
#define K_POS     2
#define DELIM    ','

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/
int cmp_tags(const void * dato1,const void * dato2){ //Diseñado para que se comporte como un heap
    tag_t * tag1 = (tag_t*)dato1;
    tag_t * tag2 = (tag_t*)dato2;

    if(tag_ver_freq(tag1) == tag_ver_freq(tag2)){
        if(strcmp(tag_ver_clave(tag1),tag_ver_clave(tag2)) > 0){ //No estoy seguro de que el orden este bien
            return 1;
        }else{
            return -1;
        }
    }else if(tag_ver_freq(tag1) > tag_ver_freq(tag2)){
        return -1;
    }else{
        return 1;
    }
}
void _tag_destruir(void * data){
	tag_destruir((tag_t*)data);
}

/* *****************************************************************
 *
 * *****************************************************************/
int validate_arguments(int argc, char const *argv[],size_t * n,size_t * k){
	char * tmp_conversion;

	if(argc != ARGS){
		fprintf(stderr,"Error: cantidad Erronea de parametros\n");
		return EXIT_FAILURE;
	}
	*n = strtoul(argv[N_POS],&tmp_conversion,0);
	if(!(*tmp_conversion == '\n' || *tmp_conversion == '\0'))
	{
		fprintf(stderr, "Error: de conversion str to size_t\n");
		return EXIT_FAILURE;
	}
	*k = strtoul(argv[K_POS],&tmp_conversion,0);
	if(!(*tmp_conversion == '\n' || *tmp_conversion == '\0'))
	{
		fprintf(stderr, "Error: de conversion str to size_t\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

int procesar_linea(count_min_sketch_t * csm, hash_t * hash_claves){
	char * linea = NULL,* str_aux = NULL;
	size_t tam = 0;
	ssize_t largo = 0;
	int tag_len = 0;

	if((largo = getline(&linea, &tam, stdin)) == -1)
		return EXIT_SUCCESS; // Llego al fin del archivo

	for (size_t j = 0; linea[j] != '\0'; j++,tag_len++) {
		if(j == 0)
			str_aux = NULL;

		if(linea[j+1] == DELIM || linea[j+1] == '\n'){
			if(str_aux != NULL){
				str_aux = substr(str_aux,(size_t)tag_len);
				count_min_sketch_guardar(csm,str_aux);
				if(!hash_pertenece(hash_claves,str_aux)){
					if(!hash_guardar(hash_claves,str_aux,NULL)){
						free(linea);
						free(str_aux);
						return EXIT_FAILURE;
					}
				}
				free(str_aux); //Libero memoria que reservo substr
			}
			str_aux = &linea[j+2];
			tag_len = -1;
		}
	}
	free(linea);
	return EXIT_SUCCESS;
}

int imprimir_tt(size_t k,hash_t * hash_claves,count_min_sketch_t * csm){
	hash_iter_t * iter = hash_iter_crear(hash_claves);
	if(!iter) return EXIT_FAILURE;
	heap_t * heap_tt = heap_crear(cmp_tags);
	if(!heap_tt){
		hash_iter_destruir(iter);
		return EXIT_FAILURE;
	}
	pila_t * pila = pila_crear();
	if(!pila){
		hash_iter_destruir(iter);
		heap_destruir(heap_tt,NULL);
		return EXIT_FAILURE;
	}
	tag_t * tag;

	for (size_t i = 0; !hash_iter_al_final(iter); i++,hash_iter_avanzar(iter)) {
		tag = tag_crear(hash_iter_ver_actual(iter),count_min_sketch_obtener_min(csm,hash_iter_ver_actual(iter)));
		if(!tag){
			hash_iter_destruir(iter);
			heap_destruir(heap_tt,NULL);
			pila_destruir(pila);
			return EXIT_FAILURE;
		}

		if(i < k){
			heap_encolar(heap_tt,(void*)tag);
		}
		else{
			if(cmp_tags(heap_ver_max(heap_tt),(void*)tag) > 0 ){
				tag_destruir((tag_t*)heap_desencolar(heap_tt));
				heap_encolar(heap_tt,(void*)tag);
			}else{
				tag_destruir(tag);
			}
		}
	}
	while (!heap_esta_vacio(heap_tt)) {
		pila_apilar(pila,heap_desencolar(heap_tt));
	}
	while (!pila_esta_vacia(pila)) {
		tag = (tag_t*)pila_desapilar(pila);
		printf("%lu %s\n",tag_ver_freq(tag),tag_ver_clave(tag));
		tag_destruir(tag);
	}

	pila_destruir(pila);
	hash_iter_destruir(iter);
	heap_destruir(heap_tt,_tag_destruir);
	return EXIT_SUCCESS;
}

int procesar_tweets(size_t n,size_t k){
	size_t cont = 0;
	count_min_sketch_t * csm = count_min_sketch_crear(n * 100);
	if(!csm) return EXIT_FAILURE;

	while(!feof(stdin)){
		hash_t * hash_claves = hash_crear(NULL);
		if(!hash_claves){
			count_min_sketch_destruir(csm);
			return EXIT_FAILURE;
		}

		for(size_t i = 0; i < n; i++){
			if(procesar_linea(csm,hash_claves) != EXIT_SUCCESS){
				hash_destruir(hash_claves);
				count_min_sketch_destruir(csm);
				return EXIT_FAILURE;
			}
		}
        if(hash_cantidad(hash_claves) == 0){ //LLegó al fin del archivo
            hash_destruir(hash_claves);
            break;
        }
        printf("--- %lu\n",++cont );
		if(imprimir_tt(k,hash_claves,csm) != EXIT_SUCCESS){
			hash_destruir(hash_claves);
			count_min_sketch_destruir(csm);
			return EXIT_FAILURE;
		}
		hash_destruir(hash_claves);
	}
	count_min_sketch_destruir(csm);
	return EXIT_SUCCESS;
}
int main(int argc, char const *argv[]) {
	size_t n,k;

	if(validate_arguments(argc,argv,&n,&k) != EXIT_SUCCESS){
		return EXIT_FAILURE;
	}

	if(procesar_tweets(n,k) != EXIT_SUCCESS){
		fprintf(stderr,"Error: al procesar tweets\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
