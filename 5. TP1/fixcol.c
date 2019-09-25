#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ARGS 3
#define FILE_POS 1
#define SIZE_POS 2

int validate_arguments(int argc, char const *argv[],size_t * size){
	char * tmp_conversion;
	if(argc != ARGS){
		fprintf(stderr,"Error: Cantidad erronea de parametros\n");
		return EXIT_FAILURE;
	}
	*size = strtoul(argv[SIZE_POS],&tmp_conversion,0);
	if(!(*tmp_conversion == '\n' || *tmp_conversion == '\0'))
	{
		fprintf(stderr, "Error: de conversion str to size_t\n");
		return EXIT_FAILURE;
	}
	if(*size <= 0){
		fprintf(stderr, "Error: No se permite fixcol 0\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int print_fixcol(FILE * file,size_t size){
	char * str_aux = malloc(sizeof(char) * ((size / sizeof(char)) + 1));
	if(!str_aux) return EXIT_FAILURE;

	while(fgets(str_aux,(int)(size / sizeof(char)) + 1,file)){ //Porque agarra hasta n-1
		size_t aux_len = strlen(str_aux);
		if(str_aux[aux_len - 1] == '\n')
			str_aux[aux_len - 1] = '\0';
		if(str_aux[0] != '\0')
			puts(str_aux);
	}

	free(str_aux);
	return EXIT_SUCCESS;
}
int main(int argc, char const *argv[]) {
	size_t size;
	FILE * file;

	if(validate_arguments(argc,argv,&size) != EXIT_SUCCESS){
		return EXIT_FAILURE;
	}

	file = fopen(argv[FILE_POS],"r");
	if(!file){
		fprintf(stderr,"Error: archivo fuente inaccesible\n");
		return EXIT_FAILURE;
	}

	if(print_fixcol(file,size) != EXIT_SUCCESS){
		fclose(file);
		fprintf(stderr, "Error: en Fixcol\n");
		return EXIT_FAILURE;
	}

	fclose(file);
	return EXIT_SUCCESS;
}
