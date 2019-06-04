#include <stdio.h>
#include "testing.h"
#include "heap.h"

int comparar_int(const void *a, const void *b) {
  if(*(int*)a == *(int*)b){
    return 0;
  } else if (*(int*)a > *(int*)b) {
    return 1;
  } else {
    return -1;
  }
}
static void prueba_heap_vacio() {

  printf("\nPRUEBAS HEAP VACIO\n");

  heap_t* heap = heap_crear(comparar_int);
  print_test("Se creo el heap", heap);
  print_test("La cantidad de elementos del heap es 0", !heap_cantidad(heap));
  print_test("El heap esta vacio", heap_esta_vacio(heap));
  print_test("Ver maximo es NULL", !heap_ver_max(heap));
  print_test("Desencolar en heap vacio devuelve NULL", !heap_desencolar(heap));

  heap_destruir(heap, NULL);
  print_test("Se destruyo el heap", true);

}

static void prueba_heap_sin_arreglo() {
  printf("\nPRUEBAS HEAP CON FUNCION HEAP CREAR\n");

  int v[3] = {5,2,8};
  heap_t* heap = heap_crear(comparar_int);

  print_test("Se creo el heap", heap);
  print_test("El heap esta vacio", heap_esta_vacio(heap));
  print_test("Se encolo el 5", heap_encolar(heap, &v[0]));
  print_test("El heap no esta vacio", !heap_esta_vacio(heap));
  print_test("La cantidad de elementos es 1", heap_cantidad(heap) == 1);
  print_test("El maximo es el unico elemento encolado", heap_ver_max(heap) == &v[0]);
  print_test("Se encolo el 2", heap_encolar(heap, &v[1]));
  print_test("La cantidad de elementos es 2", heap_cantidad(heap) == 2);
  print_test("Ver maximo da el elemento correcto", heap_ver_max(heap) == &v[0]);
  print_test("Se encolo el 8", heap_encolar(heap, &v[2]));
  print_test("La cantidad de elementos es 3", heap_cantidad(heap) == 3);
  print_test("Ver maximo devuelve el elemento correcto", heap_ver_max(heap) == &v[2]);
  print_test("Encolar el mismo elemento dos veces es posible", heap_encolar(heap, &v[1]));
  print_test("La cantidad de elementos es 4", heap_cantidad(heap) == 4);
  print_test("Desencolar devuelve el maximo", heap_desencolar(heap) == &v[2]);
  print_test("La cantidad de elementos es 3", heap_cantidad(heap) == 3);
  print_test("Ver maximo devuelve el elemento correcto", heap_ver_max(heap) == &v[0]);
  printf("MAXIMOOOOO: %d\n",*(int*)heap_ver_max(heap) );
  print_test("Desencolar devuelve el maximo", heap_desencolar(heap) == &v[0]);
  print_test("La cantidad de elementos es 2", heap_cantidad(heap) == 2);
  print_test("Ver maximo devuelve el elemento correcto", heap_ver_max(heap) == &v[1]);
  print_test("Desencolar devuelve el maximo", heap_desencolar(heap) == &v[1]);
  print_test("La cantidad de elementos es 1", heap_cantidad(heap) == 1);
  print_test("Ver maximo devuelve el elemento correcto", heap_ver_max(heap) == &v[1]);
  print_test("Desencolar devuelve el maximo", heap_desencolar(heap) == &v[1]);
  print_test("El heap esta vacio", heap_esta_vacio(heap));

  heap_destruir(heap, NULL);
  print_test("Se destruyo el heap", true);

}

void pruebas_heap_alumno(void) {
  prueba_heap_vacio();
  prueba_heap_sin_arreglo();
}
