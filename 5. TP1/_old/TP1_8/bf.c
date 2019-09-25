#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "vector.h"
#include "pila.h"

#define MAX_ARGS  2
#define FILE_POS  1
#define SIZE_POS  2
#define SIZE_INIT 100
#define SIZE_INIT_TAPE 10000000
#define ALLOWED_CHARS "<>+-.,[]"

typedef enum{READ_FILE,READ_STDIN} config_t;

int validate_arguments(int argc, char const *argv[],config_t * config){
	if(argc > MAX_ARGS){
		fprintf(stderr,"Error: cantidad Erronea de parametros\n");
		return EXIT_FAILURE;
	}else if(argc == MAX_ARGS)
		*config = READ_FILE;
	else
		*config = READ_STDIN;

	return EXIT_SUCCESS;
}

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

int interpret_bf(vector_t * tape){
	char current_char;
	bool status = true;
    size_t i,*aux_pos;
    size_t loop;
	pila_t * stack_loop = pila_crear();
	if(!stack_loop) return EXIT_FAILURE;
	char * array_char = calloc(SIZE_INIT_TAPE * 4,sizeof(char));
	if(!array_char) return EXIT_FAILURE;
	char * ptr = array_char;

    for (i = 0; (current_char = *(char *)vector_obtener(tape,i)) != '\0'; i++){
		//printf("%c\t%lu\n",current_char,i );
        if (current_char == '>') {
			++ptr;
        } else if (current_char == '<') {
            --ptr;
        } else if (current_char == '+') {
            ++(*ptr);
        } else if (current_char == '-') {
            --(*ptr);
        } else if (current_char == '.' ) {
            putchar(*ptr);
        } else if (current_char == ',') {
            *ptr=(char)getchar();
        } else if (current_char == '[') {
			if(*ptr == 0){
				loop = 1;
				while (loop > 0){
					current_char = *(char *)vector_obtener(tape,++i);
					if (current_char == '[') {
						loop++;
					}
					else if (current_char == ']') {
						loop--;
					}
				}
			}else{
				aux_pos = malloc(sizeof(size_t));
				if(!aux_pos){
					status = false;
					break;
				}
				*aux_pos = i;
				if(!pila_apilar(stack_loop,(void*)aux_pos)){
					status = false;
					break;
				}
			}
		} else if (current_char == ']') {
			if(*ptr != 0){
				//PEGA SALTO
				i = *(size_t*)pila_ver_tope(stack_loop);
			}else{
				// NO PEGA SALTO
				free(pila_desapilar(stack_loop));
			}
        }
	}
	while(!pila_esta_vacia(stack_loop)){
		free(pila_desapilar(stack_loop));
	}
	pila_destruir(stack_loop);
	free(array_char);
	if(!status)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int main(int argc, char const *argv[]) {

	config_t config;
	vector_t * tape = vector_crear(SIZE_INIT_TAPE);

	if(!tape) return EXIT_FAILURE;
	if(validate_arguments(argc,argv,&config) != EXIT_SUCCESS){
		vector_destruir(tape);
		return EXIT_FAILURE;
	}

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
	}
/*
	size_t i; //PRINT TAPE
	putchar('\n');
	for (i = 0; *(char *)vector_obtener(tape,i) != '\0'; i++){
		putchar(*(char *)vector_obtener(tape,i));
	}
	putchar('\n');*/

	vector_destruir(tape);
	return EXIT_SUCCESS;
}
