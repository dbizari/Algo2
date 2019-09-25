#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "data_ptr.h"
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

/*int load_from_stdin(vector_t * tape){
	bool   status = true;
	size_t inputlen = 0, templen = 0,pos = 0;
	char   tempbuf[SIZE_INIT];
	char * c;
	char * input = calloc(SIZE_INIT,sizeof(char));
	if(!input) return EXIT_FAILURE;

	inputlen = SIZE_INIT;
	do{
		fgets(tempbuf, SIZE_INIT, stdin);
	    templen = strlen(tempbuf);
		if(inputlen <= (templen + 1)){
			input = realloc(input, inputlen + 1);
			if(!input) return EXIT_FAILURE;
			inputlen += templen;
		}
	    strcat(input, tempbuf);
	}while(templen == SIZE_INIT-1 && tempbuf[SIZE_INIT-2] != '\n');

	for (size_t i = 0; input[i] != '\0'; i++) {
		if(strchr(ALLOWED_CHARS,input[i]) != NULL){
			c = malloc(sizeof(char));
			if(!c){
				status = false;
				break;
			}
			*c = input[i];
			if(vector_guardar(tape,pos,(void*)c) == false){
				status = false;
				break;
			}
			pos++;
		}
	}
	if(!status){
		free(input);
		fprintf(stderr, "%s\n","Error en carga de datos" );
		return EXIT_FAILURE;
	}
	c = malloc(sizeof(char));
	if(!c){
		free(input);
		fprintf(stderr, "%s\n","Error en carga de datos" );
		return EXIT_FAILURE;
	}
	*c = '\0';
	if(vector_guardar(tape,pos,(void*)c) == false){
		free(input);
		fprintf(stderr, "%s\n","Error en carga de datos" );
		return EXIT_FAILURE;
	}

	free(input);
	return EXIT_SUCCESS;
}*/

int interpret_bf(vector_t * tape){
	char current_char;
	bool status = true;
    size_t i,*aux_pos;
    size_t loop;
	data_ptr_t * data_ptr = data_ptr_create(SIZE_INIT_TAPE);
	if(!data_ptr) return EXIT_FAILURE;
	pila_t * stack_open_loop = pila_crear();
	if(!stack_open_loop) return EXIT_FAILURE;
	pila_t * stack_close_loop = pila_crear();
	if(!stack_close_loop) return EXIT_FAILURE;

    for (i = 0; (current_char = *(char *)vector_obtener(tape,i)) != '\0'; i++){
		//printf("%c\t%lu\n",current_char,i );
        if (current_char == '>') {
			data_ptr_next(data_ptr);
        } else if (current_char == '<') {
            data_ptr_prev(data_ptr);
        } else if (current_char == '+') {
            data_ptr_incf(data_ptr);
        } else if (current_char == '-') {
            data_ptr_decf(data_ptr);
        } else if (current_char == '.' ) {
            putchar(data_ptr_get(data_ptr));
        } else if (current_char == ',') {
            data_ptr_set(data_ptr,(char)getchar());
        } else if (current_char == '[') {
			if(data_ptr_get(data_ptr) == 0){ //TIENE QUE PEGAR SALTO
				if(pila_esta_vacia(stack_close_loop)){ //SI NO HAY POSICION EN STACK QUE RECORRA UNO POR UNO HASTA LLEGAR AL ]
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
				}else{ //SAQUE POSICION (FOR LE SUMA 1) Y LUEGO DESAPILO Y LIBERO MEMORIA
					//JUMP
					i = *(size_t*)pila_ver_tope(stack_close_loop);
					free(pila_desapilar(stack_close_loop));
				}
			}else{ //NO TIENE QUE PEGAR SALTO, SOLO PONGO EN STACK CLOSE LA POSICION ACTUAL
				aux_pos = malloc(sizeof(size_t));
				if(!aux_pos){
					status = false;
					break;
				}
				*aux_pos = i;
				if(!pila_apilar(stack_open_loop,(void*)aux_pos)){ //apilo la posicion en donde deberia comenzar luego
					status = false;
					break;
				}
			}
			continue;
		} else if (current_char == ']') {
			if(data_ptr_get(data_ptr) != 0){      //PEGA SALTO
				//save position
				aux_pos = malloc(sizeof(size_t));
				if(!aux_pos){
					status = false;
					break;
				}
				*aux_pos = i;
				if(!pila_apilar(stack_close_loop,(void*)aux_pos)){ //ESOY APILANDO UNA BOCHA
					status = false;
					break;
				}
				/*if(pila_esta_vacia(stack_close_loop)){ // PILA ESTA VACIA ENTONCES APILO
					aux_pos = malloc(sizeof(size_t));
					if(!aux_pos){
						status = false;
						break;
					}
					*aux_pos = i;
					if(!pila_apilar(stack_close_loop,(void*)aux_pos)){
						status = false;
						break;
					}
				}else if(*(size_t*)pila_ver_tope(stack_close_loop) != i){ // SI NO ES VACIA Y NO ESTA APILADO ENTONCES LO APILO//NO SE ESTA DESAPILANDO PORQUE CUANDO HAGO JUMP VA A LA POSICION SIGUIENTE A []
					aux_pos = malloc(sizeof(size_t));
					if(!aux_pos){
						status = false;
						break;
					}
					*aux_pos = i;
					if(!pila_apilar(stack_close_loop,(void*)aux_pos)){ //ESOY APILANDO UNA BOCHA
						status = false;
						break;
					}
				}*/
				//Jump PEGO SALTO EN LOS DOS CASOS, LO DE ARRIBA ES SOLO PARA VER CUANDO GUARDAR O NO EN STACK,
				// VEO STACK Y POSICIONO (-1 ASI VA AL CORCHETE) Y LIBERO LA POSICION DE STACK
				i = *(size_t*)pila_ver_tope(stack_open_loop) - 1; //Luego el ciclo for le aumenta 1 y se posiciona en [
				//free(pila_desapilar(stack_open_loop));
			}else{ // NO PEGA SALTO, ENTONCES DESAPILI
				//free(pila_desapilar(stack_open_loop)); //DESAPILO Y LIBERO LA MEMORIA
				//free(pila_desapilar(stack_close_loop)); //CRE0 QUE LO TENGO QUE SACAR A MENOS QUE DEMUESTRE LO CONTRARIO
			}
			free(pila_desapilar(stack_open_loop)); //SIEMPRE DESAPILO, TOTAL VUELVO A APILAR EN EL OTRO CORCHETE
			continue;
        }
	}
	data_ptr_destroy(data_ptr);
	while(!pila_esta_vacia(stack_close_loop)){
		free(pila_desapilar(stack_close_loop));
	}
	pila_destruir(stack_close_loop);
	while(!pila_esta_vacia(stack_open_loop)){
		free(pila_desapilar(stack_open_loop));
	}
	pila_destruir(stack_open_loop);
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
