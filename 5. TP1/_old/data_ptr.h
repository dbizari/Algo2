#ifndef DATA_H
#define DATA_H

#include <stdbool.h>


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct data_ptr data_ptr_t;

/* ******************************************************************
 *                    PRIMITIVAS DE DATA_PTR
 * *****************************************************************/

// Crea la estructura data_ptr_t.
// Post: devuelve una nueva estructura vacia.
data_ptr_t* data_ptr_create(size_t size);

// Destruye la estructura.
// Pre: la estructura fue creada.
// Post: se eliminaron todos los elementos de la estructura y la estructura.
void data_ptr_destroy(data_ptr_t *aux);

// Pasa a la siguiente posicion, en caso de no haber otra se redimensiona el array.
// Pre: la estructura fue creada.
// Post: el apuntador de la estructura apunta a la posicion siguiente del array.
bool data_ptr_next(data_ptr_t *data_ptr);

// Pasa a la posicion anterior, en caso de que se este desutilizando gran parte
// del array se redimensiona el mismo para no desperdiciar memoria.
// Pre: la estructura fue creada.
// Post: el apuntador de la estructura apunta a la posicion anterior del array.
bool data_ptr_prev(data_ptr_t *data_ptr);

// Incrementa valor
// Pre: la estructura fue creada.
// Post: Se incremento en 1 el valor al que esta apunto el apuntador.
void data_ptr_incf(data_ptr_t *data_ptr);

// Decrementa valor
// Pre: la estructura fue creada.
// Post: Se decremento en 1 el valor al que esta apunto el apuntador.
void data_ptr_decf(data_ptr_t *data_ptr);

// Ver valor
// Pre: la estructura fue creada.
// Post: Devolvio valor (char) al que esta apuntando el apuntador.
char data_ptr_get(data_ptr_t *data_ptr);

// Guardar valor
// Pre: la estructura fue creada.
// Post: Guarda valor (char) en donde esta apuntando el apuntador.
void data_ptr_set(data_ptr_t *data_ptr,char data);

#endif // DATA_H
