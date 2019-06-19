#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

typedef struct tag tag_t;

/* *****************************************************************
 *                    PRIMITIVAS DE TAG
 * *****************************************************************/
// Constructor parametrizado
// Post: Devuelve puntero tag_t inicializado con los valores pasados por parametro
// Pre:
tag_t* tag_crear(const char* clave,const size_t freq);

// Devuelve puntero a clave
// Post: Devuelve puntero a clave
// Pre: La estructura fue creada
const char* tag_ver_clave(const tag_t *tag);

// Devuelve la frecuencia del tag
// Post: Devuelve la frecuencia del tag
// Pre: La estructura fue creada
size_t tag_ver_freq(const tag_t *tag);

// Destruye la estructura
// Post: Se destruyó la estructura
// Pre: La estructura fue creada
void tag_destruir(tag_t* tag);
