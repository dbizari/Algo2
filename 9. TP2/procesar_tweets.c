#define _POSIX_C_SOURCE 200809L //Para getline()
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "strutil.h"
#include "hash.h"
#include "count_min_sketch.h"

#define ARGS  	  3
#define N_POS  	  1
#define K_POS     2
#define DELIM    ','

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

int procesar_tweets(size_t n,size_t k){
	char * linea = NULL;
	size_t tam = 0;
	ssize_t largo = 0;
	char * str_aux;

	//while(!feof(stdin)){
		count_min_sketch_t * csm = count_min_sketch_crear(n * 100);
		if(!csm) return EXIT_FAILURE;
		hash_t * hash_claves = hash_crear(NULL);
		if(!hash_claves){
			count_min_sketch_destruir(csm);
			return EXIT_FAILURE;
		}

		for(size_t i = 0; i < n; i++){
			if((largo = getline(&linea, &tam, stdin)) == -1)
				break;

			int tag_len = 0;
			for (size_t j = 0; linea[j] != '\0'; j++,tag_len++) {
				if(j == 0)
					str_aux = NULL;

				if(linea[j+1] == DELIM || linea[j+1] == '\n'){
					if(str_aux != NULL){
						/*printf("Tag:%s\tLargo:%d\n\n",(str_aux=substr(str_aux,(size_t)tag_len)),tag_len);*/
						str_aux=substr(str_aux,(size_t)tag_len);
						count_min_sketch_guardar(csm,str_aux);
						if(!hash_pertenece(hash_claves,str_aux)){
							if(!hash_guardar(hash_claves,str_aux,NULL)){
								count_min_sketch_destruir(csm);
								free(linea);
								hash_destruir(hash_claves);
								return EXIT_FAILURE;
							}
						}
						//free(str_aux);
						//printf("LLEGA\n" );
					}
					str_aux = &linea[j+2];
					tag_len = -1;
				}
			}
		}
		hash_iter_t * iter=hash_iter_crear(hash_claves);
		while (!hash_iter_al_final(iter)) {
			printf("Clave:%s\tFreq:%lu\n",hash_iter_ver_actual(iter), count_min_sketch_obtener_min(csm,hash_iter_ver_actual(iter)));
			hash_iter_avanzar(iter);
		}
		hash_iter_destruir(iter);
		count_min_sketch_destruir(csm);
	//}
	free(linea);
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
	printf("Finishhh\n" );
	return EXIT_SUCCESS;
}
