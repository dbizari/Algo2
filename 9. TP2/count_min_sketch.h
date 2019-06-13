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
bool count_min_sketch_guardar(count_min_sketch_t *count_min_sketch, const char *clave);

/* Borra un elemento de count_min_sketch y devuelve el dato asociado. Devuelve
 * NULL si el dato no estaba.
 * Pre: La estructura count_min_sketch fue inicializada
 * Post: El elemento fue borrado de la estructura y se lo devolvió,
 * en el caso de que estuviera guardado.
 */
void *count_min_sketch_borrar(count_min_sketch_t *count_min_sketch, const char *clave); // Evaluar si es necesario

/* Obtiene el valor minimo de un elemento del count_min_sketch, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura count_min_sketch fue inicializada
 */
void *count_min_sketch_obtener_min(const count_min_sketch_t *count_min_sketch, const char *clave);

/* Determina si clave pertenece o no al count_min_sketch.
 * Pre: La estructura count_min_sketch fue inicializada
 */
 bool count_min_sketch_pertenece(const count_min_sketch_t *count_min_sketch, const char *clave); //Evaluar si es necesario

/* Devuelve la cantidad de elementos del count_min_sketch.
 * Pre: La estructura hash fue inicializada
 */
size_t count_min_sketch_cantidad(const hash_t *count_min_sketch);

/* Destruye la estructura liberando la memoria pedida.
 * Pre: La estructura count_min_sketch fue inicializada
 * Post: La estructura count_min_sketch fue destruida
 */
void count_min_sketch_destruir(count_min_sketch_t *count_min_sketch);

#endif // COUNT_MIN_SKETCH_H
