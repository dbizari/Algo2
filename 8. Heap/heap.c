#include "heap.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define SIZE_INIT 128
#define SCALE_FACTOR 3

/* *****************************************************************
 *                    DEFINICION DE STRUCT
 * *****************************************************************/
struct heap{
	void ** datos;
	size_t  cantidad;
	size_t  capacidad;
	cmp_func_t cmp;
};

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/
void swap(void ** dato1, void** dato2){
	void * aux = *dato1;
	*dato1 = *dato2;
	*dato2 = aux;
}

void upheap(heap_t * heap,size_t pos){
	if(pos == 0) return;
	size_t padre = (pos - 1) / 2;
	if(heap->cmp(heap->datos[padre],heap->datos[pos]) > 0){
		swap(&heap->datos[padre],&heap->datos[pos]);
		upheap(heap,padre);
	}
}

void downheap(heap_t * heap,size_t pos){
	if(pos >= heap->cantidad) return;
	size_t min = pos;
	size_t izq = 2 * pos + 1;
	size_t der = 2 * pos + 1;

	if(izq < heap->cantidad && heap->cmp(heap->datos[izq],heap->datos[min]) < 0)
		min = izq;
	if(der < heap->cantidad && heap->cmp(heap->datos[der],heap->datos[min]) < 0)
		min = der;
	if(min != pos){
		swap(&heap->datos[min],&heap->datos[pos]);
		downheap(heap,min);
	}
}
/* *****************************************************************
 *                    PRIMITIVAS DE HEAP
 * *****************************************************************/

/* Crea un heap. Recibe como único parámetro la función de comparación a
 * utilizar. Devuelve un puntero al heap, el cual debe ser destruido con
 * heap_destruir().
 */
heap_t *heap_crear(cmp_func_t cmp){
	if(!cmp) return NULL;
	heap_t *heap = malloc(sizeof(heap_t));
	if(!heap) return NULL;

	heap->datos = malloc(sizeof(void *) * SIZE_INIT);
	if(!heap->datos){
		free(heap);
		return NULL;
	}
	heap->cantidad = 0;
	heap->capacidad = SIZE_INIT;
	return heap;
}

/*
 * Constructor alternativo del heap. Además de la función de comparación,
 * recibe un arreglo de valores con que inicializar el heap. Complejidad
 * O(n).
 *
 * Excepto por la complejidad, es equivalente a crear un heap vacío y encolar
 * los valores de uno en uno
*/
heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp); //HEAPIFY!!!

/* Elimina el heap, llamando a la función dada para cada elemento del mismo.
 * El puntero a la función puede ser NULL, en cuyo caso no se llamará.
 * Post: se llamó a la función indicada con cada elemento del heap. El heap
 * dejó de ser válido. */
void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	if(destruir_elemento != NULL){
		for (size_t i = 0; i < heap->cantidad; i++) {
			destruir_elemento(heap->datos[i]);
		}
	}
	free(heap->datos);
	free(heap);
}


/* Devuelve la cantidad de elementos que hay en el heap. */
size_t heap_cantidad(const heap_t *heap){
	return heap->cantidad;
}

/* Devuelve true si la cantidad de elementos que hay en el heap es 0, false en
 * caso contrario. */
bool heap_esta_vacio(const heap_t *heap){
	return (heap->cantidad == 0);
}

bool heap_redimensionar(heap_t *heap, size_t cantidad){
	if((heap->datos =(void**)realloc(heap->datos,sizeof(void*) * cantidad)) == NULL)
	return false;

	heap->capacidad = cantidad;
	return true;
}

/* Agrega un elemento al heap. El elemento no puede ser NULL.
 * Devuelve true si fue una operación exitosa, o false en caso de error.
 * Pre: el heap fue creado.
 * Post: se agregó un nuevo elemento al heap.
 */
bool heap_encolar(heap_t *heap, void *elem){
	if(elem == NULL) return NULL;
	if(heap->cantidad == (heap->capacidad -1)){
		if(heap_redimensionar(heap, heap->capacidad * SCALE_FACTOR) == false)
            return false;
	}
	heap->datos[heap->cantidad] = elem;
	upheap(heap,heap->cantidad);
	heap->cantidad++;
	return true;
}

/* Devuelve el elemento con máxima prioridad. Si el heap esta vacío, devuelve
 * NULL.
 * Pre: el heap fue creado.
 */
void *heap_ver_max(const heap_t *heap){
	return heap_esta_vacio(heap) == true ? NULL : heap->datos[0];
}

/* Elimina el elemento con máxima prioridad, y lo devuelve.
 * Si el heap esta vacío, devuelve NULL.
 * Pre: el heap fue creado.
 * Post: el elemento desencolado ya no se encuentra en el heap.
 */
void *heap_desencolar(heap_t *heap){
	if(heap_esta_vacio(heap)) return NULL;
	void * dato = heap->datos[0];

	swap(&heap->datos[0],&heap->datos[--heap->cantidad]);
	downheap(heap,0);
	heap->datos[heap->cantidad] = NULL;
	if(heap->cantidad == (heap->capacidad / 4)){
		if(heap_redimensionar(heap, heap->capacidad / SCALE_FACTOR) == false)
            return false;
	}
	return dato;
}