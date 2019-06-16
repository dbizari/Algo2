#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ARGS  	  3
#define N_POS  	  1
#define K_POS     2
#define SIZE_INIT 100
#define SIZE_INIT_TAPE 20000
#define SIZE_INIT_MEM 4000
#define SCALE_FACTOR 3

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
/*
int load_from_file(vector_t * tape,char const * str){
	FILE * file;
	bool status = true;
	char *c, aux;
	size_t pos = 0;

	if(!strcmp(str,"stdin"))
		file = stdin;
	else
		file = fopen(str,"r");

	if(!file) return EXIT_FAILURE;

	while ((aux = (char)fgetc(file)) != EOF) {
		if(strchr(ALLOWED_CHARS,aux) != NULL){
			c = malloc(sizeof(char));
			if(!c){
				status = false;
				break;
			}
			*c = aux;
			if(vector_guardar(tape,pos,(void*)c) == false){
				status = false;
				break;
			}
			pos++;
		}
	}
	if(!status){
		fclose(file);
		return EXIT_FAILURE;
	}

	c = malloc(sizeof(char));
	if(!c){
		fclose(file);
		return EXIT_FAILURE;
	}
	*c = '\0';

	if(vector_guardar(tape,pos,(void*)c) == false){
		fclose(file);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

*/
int main(int argc, char const *argv[]) {
	//vector_t * tape = vector_crear(SIZE_INIT_TAPE); //Ver si es necesario
	//if(!tape) return EXIT_FAILURE;
	size_t n,k;

	if(validate_arguments(argc,argv,&n,&k) != EXIT_SUCCESS){
		//vector_destruir(tape);
		return EXIT_FAILURE;
	}
/*
	if(config == READ_FILE){
		if(load_from_file(tape,argv[FILE_POS]) != EXIT_SUCCESS){
			fprintf(stderr,"Error: Archivo fuente inaccesible\n");
			vector_destruir(tape);
			return EXIT_FAILURE;
		}
	}
	else{
		if(load_from_file(tape,"stdin") != EXIT_SUCCESS){
			fprintf(stderr,"Error: Al leer por STDIN\n");
			vector_destruir(tape);
			return EXIT_FAILURE;
		}
	}

	if(interpret_bf(tape) != EXIT_SUCCESS){
		fprintf(stderr,"Error: Al interpretar brainf#ck\n");
		vector_destruir(tape);
		return EXIT_FAILURE;
	}*/
	
/*
	size_t i; //PRINT TAPE
	putchar('\n');
	for (i = 0; *(char *)vector_obtener(tape,i) != '\0'; i++){
		putchar(*(char *)vector_obtener(tape,i));
	}
	putchar('\n');*/

	//vector_destruir(tape);
	return EXIT_SUCCESS;
}
