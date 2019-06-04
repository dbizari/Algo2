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

void destruir_dato(void * dato){
    free(dato);
}
void prueba_heap_vacio() {

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
void prueba_un_elemento(){
    cola_t* cola = cola_crear();
    int num=10;
    char letra='a';
    long num_long;
    char palabra[10]="Test";

    //Pruebas con int
    print_test("Encolar int", cola_encolar(cola,&num) == true);
    print_test("Ver primero", cola_ver_primero(cola) == &num);
    print_test("Cola esta vacia?", cola_esta_vacia(cola) == false);
    print_test("Desencolar int", cola_desencolar(cola) == &num);
    //Pruebas con char
    print_test("Encolar char", cola_encolar(cola,&letra) == true);
    print_test("Ver primero", cola_ver_primero(cola) == &letra);
    print_test("Cola esta vacia?", cola_esta_vacia(cola) == false);
    print_test("Desencolar char", cola_desencolar(cola) == &letra);
    //Pruebas con NULL
    print_test("Encolar NULL", cola_encolar(cola,NULL) == true);
    print_test("Ver primero", cola_ver_primero(cola) == NULL);
    print_test("Cola esta vacia?", cola_esta_vacia(cola) == false);
    print_test("Desencolar NULL", cola_desencolar(cola) == NULL);
    //Pruebas con long
    print_test("Encolar long", cola_encolar(cola,&num_long) == true);
    print_test("Ver primero", cola_ver_primero(cola) == &num_long);
    print_test("Cola esta vacia?", cola_esta_vacia(cola) == false);
    print_test("Desencolar long", cola_desencolar(cola) == &num_long);
    //Pruebas con string
    print_test("Encolar string", cola_encolar(cola,palabra) == true);
    print_test("Ver primero", cola_ver_primero(cola) == palabra);
    print_test("Cola esta vacia?", cola_esta_vacia(cola) == false);
    print_test("Desencolar string", cola_desencolar(cola) == palabra);
    //Destruir cola con pila
    pila_t* pila = pila_crear();

    if(!pila){
        cola_destruir(cola,NULL);
        return;
    }
    if((pila_apilar(pila,&num)) == false){
        cola_destruir(cola,NULL);
        return;
    }
    print_test("Encolar pila", cola_encolar(cola,pila) == true);
    print_test("Ver primero", cola_ver_primero(cola) == pila);
    print_test("Cola esta vacia?", cola_esta_vacia(cola) == false);
    cola_destruir(cola,destruir_pila);
    print_test("Destruir cola con una pila",true);
    return;
}

void prueba_heap_sin_arreglo() {
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
