#ifndef COUNT_MIN_SKETCH_H
#define COUNT_MIN_SKETCH_H

#include <stdbool.h>
#include <stddef.h>

struct count_min_sketch;

typedef struct count_min_sketch count_min_sketch_t;

/* Crea el count_min_sketch
 */
count_min_sketch_t *count_min_sketch_crear(size_t tam);

/* Incrementa en 1 el dato asociado a la clave. De no poder guardarlo devuelve false.
 * Pre: La estructura count_min_sketch fue inicializada
 * Post: Se incremento en uno el valor asociada a la clave.
 */
void count_min_sketch_guardar(count_min_sketch_t *count_min_sketch, const char *clave);

/* Obtiene el valor minimo de un elemento del count_min_sketch, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura count_min_sketch fue inicializada
 */
size_t count_min_sketch_obtener_min(const count_min_sketch_t *count_min_sketch, const char *clave);

/* Destruye la estructura liberando la memoria pedida.
 * Pre: La estructura count_min_sketch fue inicializada
 * Post: La estructura count_min_sketch fue destruida
 */
void count_min_sketch_destruir(count_min_sketch_t *count_min_sketch);

#endif // COUNT_MIN_SKETCH_H
