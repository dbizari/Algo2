#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "tag.h"
#include "hash.h"

struct tag{
	const char * nombre;
	size_t freq;
};

/* *****************************************************************
 *                    PRIMITIVAS DE TAG
 * *****************************************************************/

tag_t* tag_crear(const char* clave, const size_t freq){
    tag_t* aux = malloc(sizeof(tag_t));
    if(!aux) return NULL;

	aux->nombre = clave;
	aux->freq = freq;
	return aux;
}

const char* tag_ver_clave(const tag_t *tag){
    return tag == NULL ? NULL : tag->nombre;
}

size_t tag_ver_freq(const tag_t *tag){
    return tag == NULL ? 0 : tag->freq;
}

void tag_destruir(tag_t* tag){
    free(tag);
}
