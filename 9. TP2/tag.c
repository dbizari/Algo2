#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "tag.h"
#include "hash.h"

struct tag{
	char * nombre;
	size_t freq;
};

/* *****************************************************************
 *                    PRIMITIVAS DE TAG
 * *****************************************************************/

tag_t* tag_crear(const char* clave, const size_t freq){
    char * str_aux;
	tag_t* aux = malloc(sizeof(tag_t));
    if(!aux) return NULL;

    str_aux = strdup(clave);
    if(!str_aux) return NULL;
	aux->nombre = str_aux;
	aux->freq = freq;
	return aux;
}

char* tag_ver_clave(const tag_t *tag){
    return tag == NULL ? NULL : tag->nombre;
}

size_t tag_ver_freq(const tag_t *tag){
    return tag == NULL ? 0 : tag->freq;
}

void tag_destruir(tag_t* tag){
	free(tag->nombre);
    free(tag);
}
