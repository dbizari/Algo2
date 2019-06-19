#define _POSIX_C_SOURCE 200809L
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "strutil.h"
#include "hash.h"
#include "lista.h"
#include "heap.h"

#define DELIM ','
#define CANT_ARGS  2
#define FILE_POS  1

int comparar (const void *a, const void *b) {
	return strcmp((char*)a, (char*)b);
}


char** ordenar_por_cantidad(hash_t* usuarios, size_t max) {
	size_t cant = hash_cantidad(usuarios) + 2;
	lista_t** arreglo = malloc((max+1)*sizeof(lista_t*));
	char** res = malloc((cant)*sizeof(char*));
	res[cant-1] = NULL;
	size_t i;
	for (i = 0; i < max+1; i++) {
		arreglo[i] = lista_crear();
		if (!arreglo[i]) {
			for (size_t j = 0; j<i; j++) {
				lista_destruir(arreglo[j], NULL);
			}
			return NULL;
		}
	}
	hash_iter_t* iter_usuarios = hash_iter_crear(usuarios);
	while(!hash_iter_al_final(iter_usuarios)) {
		const char* usuario = hash_iter_ver_actual(iter_usuarios);
		hash_t* dato = hash_obtener(usuarios, usuario);
		size_t aux = hash_cantidad(dato);
		lista_insertar_ultimo(arreglo[aux], (void*)usuario);
		hash_iter_avanzar(iter_usuarios);
	}
	hash_iter_destruir(iter_usuarios);
	size_t pos = 0;
	size_t pos_inicial = 0;
	for (i = 0; i < max+1; i++) {
		if (lista_esta_vacia(arreglo[i])) continue;
		lista_iter_t* iter_aux = lista_iter_crear(arreglo[i]);
		while(!lista_iter_al_final(iter_aux)) {
			res[pos] = (char*)lista_iter_ver_actual(iter_aux);
			pos++;
			lista_iter_avanzar(iter_aux);
		}
		lista_iter_destruir(iter_aux);
		if (lista_largo(arreglo[i]) > 1) {
			size_t largo = pos - pos_inicial;
			heap_sort((void**)(res + pos_inicial), largo, comparar);
		}
		pos_inicial = pos;
	}
	for (i = 0; i < max+1; i++) {
		lista_destruir(arreglo[i], NULL);
	}
	free(arreglo);
	return res;
}


static void eliminar(void* hash) {
	hash_destruir((hash_t*)hash);
}

int validate_arguments(int argc, char const *argv[]){
	if(argc!= CANT_ARGS){
		fprintf(stderr,"Error: cantidad Erronea de parametros\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


hash_t* obtener_usuarios(FILE *file, size_t* maximo_valor) {
	hash_t* usuarios = hash_crear(eliminar);
	if (!usuarios) return NULL;
	char* linea = NULL;
	size_t tam = 0;
	ssize_t largo = 0;
	while((largo = getline(&linea, &tam, file)) > 0) {
		if (linea[largo-1] == '\n') {
			linea[largo-1] = '\0';
		}
		char** aux = split(linea, DELIM);
		if (!aux) {
			free(linea);
			hash_destruir(usuarios);
			return NULL;
		}
		if (!hash_pertenece(usuarios, aux[0])) {
			hash_t* dato = hash_crear(NULL);
			if(!dato) {
				free(linea);
				free_strv(aux);
				hash_destruir(usuarios);
				return NULL;
			}
			hash_guardar(usuarios, aux[0], (void*)dato);
		}
		hash_t* dato = (hash_t*)hash_obtener(usuarios, aux[0]);
		for (size_t i = 1; aux[i]!=NULL;i++) {
			if (!hash_pertenece(dato, aux[i])) {
				hash_guardar(dato, aux[i], NULL);
			}
		}
		if (hash_cantidad(dato) > *maximo_valor) *maximo_valor = hash_cantidad(dato);
		free_strv(aux);
	}
	free(linea);
	return usuarios;
}

void imprimir(hash_t* usuarios, char** arreglo) {
	size_t aux = 0;
	for (size_t i = 0; i < hash_cantidad(usuarios); i++) {
		size_t cant = hash_cantidad((hash_t*)hash_obtener(usuarios, arreglo[i]));
		if (aux!=cant) {
			if (i!=0) printf("\n");
			printf("%ld: ", cant);
			aux = cant;
		} else {
			printf(", ");
		}
		printf("%s", arreglo[i]);
	}
	printf("\n");
}

int main(int argc, char const *argv[]) {

	if(validate_arguments(argc,argv) != EXIT_SUCCESS){
		return EXIT_FAILURE;
	}

	FILE* file = fopen(argv[FILE_POS], "r");
	if (!file) {
		fprintf(stderr,"Error: Archivo fuente inaccesible\n");
		return EXIT_FAILURE;
	}


	size_t max = 0;
	hash_t* usuarios = obtener_usuarios(file, &max);
	char** arreglo = ordenar_por_cantidad(usuarios, max);
	imprimir(usuarios, arreglo);

	hash_destruir(usuarios);
	fclose(file);
	free(arreglo);
	return EXIT_SUCCESS;
}
