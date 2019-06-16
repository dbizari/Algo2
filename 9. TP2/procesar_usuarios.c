#define _POSIX_C_SOURCE 200809L
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "strutil.h"
#include "hash.h"
#include "lista.h"


#define CANT_ARGS  2
#define FILE_POS  1
#define SIZE_POS  2



static void eliminar(void* lista) {
	lista_destruir((lista_t*)lista, NULL);
}

int validate_arguments(int argc, char const *argv[]){
	if(argc!= CANT_ARGS){
		fprintf(stderr,"Error: cantidad Erronea de parametros\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int cantidad_hashtags(char** strv) {
	int cant = 0;
	for (size_t i = 1; strv[i]!=NULL; i++) {
		cant++;
	}
	return cant;
}

int obtener_usuarios(FILE *file, hash_t* usuarios) {
	char* linea = NULL;
	size_t tam = 0;
	ssize_t largo = 0;
	while((largo = getline(&linea, &tam, file)) > 0) {
		if (linea[largo-1] == '\n') {
			largo--;
			linea[largo] = '\0';
		}
		char** aux = split(linea, ',');
		if (!aux) {
			free(linea);
			return EXIT_FAILURE;
		}
		int cant_hs = cantidad_hashtags(aux);
		if (!hash_pertenece(usuarios, aux[0])) {
			int* hashtags = malloc(sizeof(int));
			if(!hashtags) {
				free(linea);
				free_strv(aux);
				return EXIT_FAILURE;
			}
			*hashtags = cant_hs;
			hash_guardar(usuarios, aux[0], &hashtags);
		} else {
			void* dato = hash_obtener(usuarios, aux[0]);
			*(int*)dato += cant_hs;
			hash_guardar(usuarios, aux[0], dato);
		}
		free_strv(aux);
	}
	return EXIT_SUCCESS;
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

	hash_t* usuarios = hash_crear(free);
	if (!usuarios) {
		fclose(file);
		return EXIT_FAILURE;
	}

	if (!obtener_usuarios(file, usuarios)) {
		fclose(file);
		hash_destruir(usuarios);
		return EXIT_FAILURE;
	};


hash_t* cantidades = hash_crear(eliminar);
hash_iter_t* iter_usuarios = hash_iter_crear(usuarios);
int maximo_valor = 0;
while(!hash_iter_al_final(iter_usuarios)) {
	const char* usuario = hash_iter_ver_actual(iter_usuarios);
	int cant = *(int*)hash_obtener(usuarios, usuario);
	if (cant>maximo_valor) {
		maximo_valor = cant;
	}
	if (!hash_obtener(cantidades, itoa(cant))) {
		lista_t* dato = lista_crear();
		lista_insertar_ultimo(dato, (void*)usuario);
		hash_guardar(cantidades, itoa(cant), dato);
	} else {
		lista_insertar_ultimo(hash_obtener(cantidades, itoa(cant)), (void*)usuario);
	}
}
hash_iter_destruir(iter_usuarios);
hash_destruir(usuarios);

	return EXIT_SUCCESS;
}
