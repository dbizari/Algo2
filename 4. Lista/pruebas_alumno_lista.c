#include "lista.h"
#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX 10000
/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
void destruir_dato(void * dato){
    free(dato);
}
void destruir_pila(void * pila){
    pila_destruir((pila_t*)pila);
}
void prueba_lista_vacia(){
    lista_t* lista = lista_crear();

    print_test("Creacion de lista", lista != NULL);
    print_test("Desenlistar lista vacia", lista_borrar_primero(lista) == NULL);
    print_test("Ver primer elemento de lista vacia", lista_ver_primero(lista) == NULL);
    print_test("Ver ultimo elemento de lista vacia", lista_ver_ultimo(lista) == NULL);
    print_test("Lista esta vacia", lista_esta_vacia(lista) == true);
    print_test("Largo de lista vacia", !lista_largo(lista));
    lista_destruir(lista,NULL);
    print_test("Destruir lista vacia",true);
    return;
}

void prueba_un_elemento(){
    lista_t* lista = lista_crear();
    int num=10;
    char letra='a';
    long num_long;
    char palabra[10]="Test";

    //Pruebas con int
    print_test("Insertar int al principio", lista_insertar_primero(lista,&num) == true);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Ver primero", lista_ver_primero(lista) == &num);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == &num);
    print_test("lista esta vacia?", lista_esta_vacia(lista) == false);
    print_test("Eliminar int de la lista", lista_borrar_primero(lista) == &num);
    print_test("Insertar int a lo ultimo", lista_insertar_ultimo(lista,&num) == true);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Ver primero", lista_ver_primero(lista) == &num);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == &num);
    print_test("lista esta vacia?", lista_esta_vacia(lista) == false);
    print_test("Eliminar int de la lista", lista_borrar_primero(lista) == &num);
    //Pruebas con char
    print_test("Insertar char al principio", lista_insertar_primero(lista,&letra) == true);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Ver primero", lista_ver_primero(lista) == &letra);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == &letra);
    print_test("lista esta vacia?", lista_esta_vacia(lista) == false);
    print_test("Eliminar char de la lista", lista_borrar_primero(lista) == &letra);
    print_test("Insertar char a lo ultimo", lista_insertar_ultimo(lista,&letra) == true);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Ver primero", lista_ver_primero(lista) == &letra);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == &letra);
    print_test("lista esta vacia?", lista_esta_vacia(lista) == false);
    print_test("Eliminar char de la lista", lista_borrar_primero(lista) == &letra);
    //Pruebas con NULL
    print_test("Insertar NULL al principio", lista_insertar_primero(lista,NULL) == true);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Ver primero", lista_ver_primero(lista) == NULL);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == NULL);
    print_test("lista esta vacia?", lista_esta_vacia(lista) == false);
    print_test("Eliminar NULL de la lista", lista_borrar_primero(lista) == NULL);
    print_test("Insertar NULL a lo ultimo", lista_insertar_ultimo(lista,NULL) == true);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Ver primero", lista_ver_primero(lista) == NULL);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == NULL);
    print_test("lista esta vacia?", lista_esta_vacia(lista) == false);
    print_test("Eliminar NULL de la lista", lista_borrar_primero(lista) == NULL);
    //Pruebas con long
    print_test("Insertar long al principio", lista_insertar_primero(lista,&num_long) == true);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Ver primero", lista_ver_primero(lista) == &num_long);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == &num_long);
    print_test("lista esta vacia?", lista_esta_vacia(lista) == false);
    print_test("Eliminar long de la lista", lista_borrar_primero(lista) == &num_long);
    print_test("Insertar long a lo ultimo", lista_insertar_ultimo(lista,&num_long) == true);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Ver primero", lista_ver_primero(lista) == &num_long);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == &num_long);
    print_test("lista esta vacia?", lista_esta_vacia(lista) == false);
    print_test("Eliminar long de la lista", lista_borrar_primero(lista) == &num_long);
    //Pruebas con string
    print_test("Insertar string al principio", lista_insertar_primero(lista,palabra) == true);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Ver primero", lista_ver_primero(lista) == palabra);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == palabra);
    print_test("lista esta vacia?", lista_esta_vacia(lista) == false);
    print_test("Eliminar string de la lista", lista_borrar_primero(lista) == palabra);
    print_test("Insertar string a lo ultimo", lista_insertar_ultimo(lista,palabra) == true);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Ver primero", lista_ver_primero(lista) == palabra);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == palabra);
    print_test("lista esta vacia?", lista_esta_vacia(lista) == false);
    print_test("Eliminar string de la lista", lista_borrar_primero(lista) == palabra);
    //Destruir lista con pila
    pila_t* pila = pila_crear();

    if(!pila){
        lista_destruir(lista,NULL);
        return;
    }
    if((pila_apilar(pila,&num)) == false){
        lista_destruir(lista,NULL);
        return;
    }
    print_test("Insertar pila al principio", lista_insertar_primero(lista,pila) == true);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Ver primero", lista_ver_primero(lista) == pila);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == pila);
    print_test("lista esta vacia?", lista_esta_vacia(lista) == false);
    print_test("Eliminar pila de la lista", lista_borrar_primero(lista) == pila);
    print_test("Insertar pila a lo ultimo", lista_insertar_ultimo(lista,pila) == true);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Ver primero", lista_ver_primero(lista) == pila);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == pila);
    print_test("lista esta vacia?", lista_esta_vacia(lista) == false);

    lista_destruir(lista,destruir_pila);
    print_test("Destruir lista con una pila",true);
    return;
}

void prueba_varios_elementos(){
    lista_t* lista = lista_crear();
    int num=10;
    char letra='a';
    long num_long;
    char palabra[10]="Test";
    float random[15]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    bool status;
    //Agregar al principio varios datos de distinto tipo
    print_test("Ver largo", lista_largo(lista) == 0);
    print_test("Agregar al principio int", lista_insertar_primero(lista,&num) == true);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Agregar al principio char", lista_insertar_primero(lista,&letra) == true);
    print_test("Ver largo", lista_largo(lista) == 2);
    print_test("Agregar al principio NULL", lista_insertar_primero(lista,NULL) == true);
    print_test("Ver largo", lista_largo(lista) == 3);
    print_test("Agregar al principio long", lista_insertar_primero(lista,&num_long) == true);
    print_test("Ver largo", lista_largo(lista) == 4);
    print_test("Agregar al principio string", lista_insertar_primero(lista,palabra) == true);
    print_test("Ver largo", lista_largo(lista) == 5);
    print_test("lista esta vacia?", lista_esta_vacia(lista) == false);
    print_test("Borrar primero: string", lista_borrar_primero(lista) == palabra);
    print_test("Ver largo", lista_largo(lista) == 4);
    print_test("Borrar primero: long", lista_borrar_primero(lista) == &num_long);
    print_test("Ver largo", lista_largo(lista) == 3);
    print_test("Borrar primero: NULL", lista_borrar_primero(lista) == NULL);
    print_test("Ver largo", lista_largo(lista) == 2);
    print_test("Borrar primero: char", lista_borrar_primero(lista) == &letra);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Borrar primero: int", lista_borrar_primero(lista) == &num);
    print_test("Ver largo", lista_largo(lista) == 0);
    print_test("lista esta vacia?", lista_esta_vacia(lista) == true);
    //Agregar al final varios datos de distinto tipo
    print_test("Ver largo", lista_largo(lista) == 0);
    print_test("Agregar al final int", lista_insertar_ultimo(lista,&num) == true);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Agregar al final char", lista_insertar_ultimo(lista,&letra) == true);
    print_test("Ver largo", lista_largo(lista) == 2);
    print_test("Agregar al final NULL", lista_insertar_ultimo(lista,NULL) == true);
    print_test("Ver largo", lista_largo(lista) == 3);
    print_test("Agregar al final long", lista_insertar_ultimo(lista,&num_long) == true);
    print_test("Ver largo", lista_largo(lista) == 4);
    print_test("Agregar al final string", lista_insertar_ultimo(lista,palabra) == true);
    print_test("Ver largo", lista_largo(lista) == 5);
    print_test("lista esta vacia?", lista_esta_vacia(lista) == false);
    print_test("Borrar primero: int", lista_borrar_primero(lista) == &num);
    print_test("Ver largo", lista_largo(lista) == 4);
    print_test("Borrar primero: char", lista_borrar_primero(lista) == &letra);
    print_test("Ver largo", lista_largo(lista) == 3);
    print_test("Borrar primero: NULL", lista_borrar_primero(lista) == NULL);
    print_test("Ver largo", lista_largo(lista) == 2);
    print_test("Borrar primero: long", lista_borrar_primero(lista) == &num_long);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Borrar primero: string", lista_borrar_primero(lista) == palabra);
    print_test("Ver largo", lista_largo(lista) == 0);
    print_test("lista esta vacia?", lista_esta_vacia(lista) == true);
    // Prueba agregar un vector al final
    status = true;
    for(int i = 0; i < 15; i++){
        if((lista_insertar_ultimo(lista,&random[i])) == false){
            status = false;
            break;
        }
        if(lista_largo(lista) != (i+1)){
            status = false;
            break;
        }
    }
    print_test("Agregar al final 15 floats de un vector", status == true);
    print_test("Ver primero", lista_ver_primero(lista) == &random[0]);
    status = true;
    for(int i = 0; i < 15; i++){
        if(lista_borrar_primero(lista) != &random[i]){
            status=false;
            break;
        }
        if(lista_largo(lista) != (14 - i)){
            status = false;
            break;
        }
    }
    print_test("Borrar elementos corroborando orden", status == true);
    // Prueba agregar un vector al principio
    status = true;
    for(int i = 0; i < 15; i++){
        if((lista_insertar_primero(lista,&random[i])) == false){
            status = false;
            break;
        }
        if(lista_largo(lista) != (i+1)){
            status = false;
            break;
        }
    }
    print_test("Agregar al principio 15 floats de un vector", status == true);
    print_test("Ver primero", lista_ver_primero(lista) == &random[14]);
    status = true;
    for(int i = 0; i < 7; i++){
        if(lista_borrar_primero(lista) != &random[14 - i]){
            status=false;
            break;
        }
        if(lista_largo(lista) != (14 - i)){
            status = false;
            break;
        }
    }
    print_test("Ver primero", lista_ver_primero(lista) == &random[7]);

    lista_destruir(lista,NULL);
    print_test("Destruir lista con 7 elementos",true);
    return;
}

void prueba_volumen(){
    lista_t* lista = lista_crear();
    int vec[MAX];
    int * vec_pointers[MAX];
    bool status=true;
    int * aux;

    for(int i = 0; i < MAX; i++){
        vec[i]=i+1;
        if(lista_insertar_ultimo(lista,&vec[i]) == false){
            status=false;
            break;
        }
    }

    print_test("Agregar 10000 int a lo ultimo",status);
    print_test("lista con elementos esta vacia?", lista_esta_vacia(lista) == false);
    print_test("Corroborar largo de la lista",lista_largo(lista) == 10000);
    print_test("Corrobar que primer elemento sea 1",*(int *)lista_ver_primero(lista) == 1);

    status=true;
    for(int i = 0; i < MAX; i++){
        if(*(int *)lista_borrar_primero(lista) != vec[i]){
            status = false;
            break;
        }
        if(lista_largo(lista) != (MAX-1-i)){ //Verificar largo de la lista
            status = false;
            break;
        }
    }
    print_test("Eliminar 10000 int y verificar que los elementos de la lista esten en el orden correspondiente",status);
    print_test("Eliminar primero (luego de haberla vaciado)", lista_borrar_primero(lista) == NULL);
    print_test("Ver primer elemento de lista vacia", lista_ver_primero(lista) == NULL);
    print_test("lista esta vacia", lista_esta_vacia(lista) == true);
    print_test("Corroborar largo de la lista", !lista_largo(lista));

    for(int i = 0; i < MAX; i++){
        if((vec_pointers[i] = malloc(sizeof(int))) == NULL){
            lista_destruir(lista,NULL);
            return;
        }
        *vec_pointers[i] = i * 2;
    }
    status = true;
    for(int i = 0; i < MAX; i++){
        if((i % 2) == 0){
            if(lista_insertar_primero(lista,NULL) == false){
                status=false;
                break;
            }
        }else{
            if(lista_insertar_primero(lista,vec_pointers[i]) == false){
                status=false;
                break;
            }
        }
    }
    print_test("Enlistar NULL e int de forma intercalada",status);
    print_test("Corrobar que primer elemento sea NULL",lista_ver_primero(lista)==vec_pointers[MAX-1]);
    print_test("Corroborar largo de la lista",lista_largo(lista) == 10000);

    for(int i = 0; i < 1000; i++){
        aux =(int*)lista_borrar_primero(lista);

        if((i % 2) != 0){
            if(aux != NULL){
                status=false;
                break;
            }
        }else{
            if(aux != vec_pointers[MAX-1-i]){
                status=false;
                break;
            }
        }
        if(lista_largo(lista) != (MAX-1-i)){ //Verificar largo de la lista
            status = false;
            break;
        }
        free(vec_pointers[MAX-1-i]);
    }

    print_test("Eliminar y verificar que los elementos de la lista esten en el orden correspondiente",status);

    lista_destruir(lista,destruir_dato);
    for(int i = 1000; i < MAX; i++) //Libero memoria de los elementos que no se cargaron en la lista
        if((i % 2) != 0)
            free(vec_pointers[MAX-1-i]);

    print_test("Destruir lista con 9000 elementos",true);
    return;
}

void prueba_iterador_lista_vacia(){
    lista_t*     lista = lista_crear();
    lista_iter_t* iter = lista_iter_crear(lista);

    print_test("Creacion de Iterador", iter != NULL);
    print_test("Avanzar Iterador en lista vacia", !lista_iter_avanzar(iter));
    print_test("Ver actual en lista vacia", lista_iter_ver_actual(iter) == NULL);
    print_test("Iterador esta al final?", lista_iter_al_final(iter));
    print_test("Lista esta vacia", lista_esta_vacia(lista) == true);
    print_test("Largo de lista vacia", !lista_largo(lista));
    lista_iter_destruir(iter);
    lista_destruir(lista,NULL);
    print_test("Destruir lista e iterador vacio",true);
}

void prueba_iterador_un_elemento(){
    int num=10;
    lista_t* lista = lista_crear();
    lista_iter_t* iter = lista_iter_crear(lista);
    pila_t* pila = pila_crear();

    if(!pila && !lista && !iter){
        return;
    }
    if((pila_apilar(pila,&num)) == false){
        lista_destruir(lista,NULL);
        return;
    }
    print_test("Ver largo", lista_largo(lista) == 0);
    print_test("Insertar con iterador", lista_iter_insertar(iter,pila) == true);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Ver actual con iterador", (pila_t*)lista_iter_ver_actual(iter) == pila);
    print_test("lista esta vacia?", lista_esta_vacia(lista) == false);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == pila);
    print_test("Insertar pila a lo ultimo", (pila_t*)lista_iter_borrar(iter) == pila);
    print_test("Ver largo", lista_largo(lista) == 0);
    print_test("Ver actual", lista_iter_ver_actual(iter) == NULL);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == NULL);
    print_test("lista esta vacia?", lista_esta_vacia(lista) == true);

    print_test("Insertar con iterador", lista_iter_insertar(iter,pila) == true);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Avanzar iterador", lista_iter_avanzar(iter) == true);
    print_test("Ver actual con iterador", (pila_t*)lista_iter_ver_actual(iter) == NULL);
    print_test("Avanzar iterador", lista_iter_avanzar(iter) == false);
    print_test("Ver actual con iterador", (pila_t*)lista_iter_ver_actual(iter) == NULL);

    lista_iter_destruir(iter);
    lista_destruir(lista,destruir_pila);
    print_test("Destruir lista con una pila",true);
    return;
}

void prueba_iterador_varios_elementos(){
    lista_t* lista = lista_crear();
    lista_iter_t* iter = lista_iter_crear(lista);
    int num=10;
    char letra='a';
    long num_long;
    char palabra[10]="Test";
    //float random[15]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    //bool status;

    if(!lista && !iter){
        return;
    }
    //Insercion en distintas posiciones
    print_test("Ver largo", lista_largo(lista) == 0);
    print_test("Agregar int con iterador", lista_iter_insertar(iter,&num) == true);
    print_test("Ver actual", lista_iter_ver_actual(iter) == &num);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == &num);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Agregar char con inter", lista_iter_insertar(iter,&letra) == true);
    print_test("Ver actual", lista_iter_ver_actual(iter) == &letra);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == &num);
    print_test("Ver largo", lista_largo(lista) == 2);
    print_test("Agregar NULL", lista_iter_insertar(iter,NULL) == true);
    print_test("Ver actual", lista_iter_ver_actual(iter) == NULL);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == &num);
    print_test("Avanzar iterador", lista_iter_avanzar(iter) == true);
    print_test("Ver largo", lista_largo(lista) == 3);
    print_test("Agregar long", lista_iter_insertar(iter,&num_long) == true);
    print_test("Final de iterador", lista_iter_al_final(iter) == false);
    print_test("Ver actual", lista_iter_ver_actual(iter) == &num_long);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == &num);
    print_test("Ver primero", lista_ver_primero(lista) == NULL);
    print_test("Avanzar iterador", lista_iter_avanzar(iter) == true);
    print_test("Ver largo", lista_largo(lista) == 4);
    print_test("Avanzar iterador", lista_iter_avanzar(iter) == true);
    print_test("Avanzar iterador", lista_iter_avanzar(iter) == true);
    print_test("Agregar string", lista_iter_insertar(iter,palabra) == true);
    print_test("Ver largo", lista_largo(lista) == 5);
    print_test("Ver actual", lista_iter_ver_actual(iter) == palabra);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == palabra);
    print_test("Ver primero", lista_ver_primero(lista) == NULL);
    print_test("Avanzar iterador", lista_iter_avanzar(iter) == true);
    print_test("Ver actual", lista_iter_ver_actual(iter) == NULL);
    print_test("Avanzar iterador", lista_iter_avanzar(iter) == false);
    print_test("Final de iterador", lista_iter_al_final(iter) == true);
    lista_iter_destruir(iter);

    // Borrado en distintas posiciones
    iter = lista_iter_crear(lista);

    print_test("Eliminar primero con iter", lista_iter_borrar(iter) == NULL);
    print_test("Ver largo", lista_largo(lista) == 4);
    print_test("Ver actual", lista_iter_ver_actual(iter) == &num_long);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == palabra);
    print_test("Ver primero", lista_ver_primero(lista) == &num_long);
    print_test("Final de iterador", lista_iter_al_final(iter) == false);
    for (size_t i = 0; i < 3; i++) {
        lista_iter_avanzar(iter);
    }
    print_test("Borrar con iter", lista_iter_borrar(iter) == palabra);
    print_test("Ver largo", lista_largo(lista) == 3);
    print_test("Ver primero", lista_ver_primero(lista) == &num_long);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == &num);
    print_test("Agregar string", lista_iter_insertar(iter,palabra) == true);
    print_test("Agregar string", lista_iter_insertar(iter,palabra) == true);
    lista_iter_destruir(iter);

    iter = lista_iter_crear(lista);
    lista_iter_avanzar(iter);
    print_test("Borrar con iter", lista_iter_borrar(iter) == &letra);
    print_test("Ver largo", lista_largo(lista) == 4);
    print_test("Borrar con iter", lista_iter_borrar(iter) == &num);
    print_test("Borrar con iter", lista_iter_borrar(iter) == palabra);
    print_test("Borrar con iter", lista_iter_borrar(iter) == palabra);
    print_test("Ver largo", lista_largo(lista) == 1);
    print_test("Ver primero", lista_ver_primero(lista) == &num_long);
    print_test("Ver ultimo", lista_ver_ultimo(lista) == &num_long);

    lista_iter_destruir(iter);
    lista_destruir(lista,NULL);
    print_test("Destruir lista e iterador",true);
    return;
}

void prueba_iterador_volumen(){
    lista_t* lista = lista_crear();
    lista_iter_t* iter = lista_iter_crear(lista);
    int vec[MAX];
    bool status=true;

    for(int i = 0; i < MAX; i++){
        vec[i]=i+1;
        if(lista_iter_insertar(iter,&vec[i]) == false){
            status=false;
            break;
        }
    }

    print_test("Agregar 10000 int a lo ultimo",status);
    print_test("lista con elementos esta vacia?", lista_esta_vacia(lista) == false);
    print_test("Corroborar largo de la lista",lista_largo(lista) == 10000);
    print_test("Corrobar que primer elemento sea 10000",*(int *)lista_iter_ver_actual(iter) == 10000);

    status=true;
    for(int i = 0; i < MAX; i++){
        if(*(int *)lista_iter_borrar(iter) != vec[MAX-1-i]){
            status = false;
            break;
        }
        if(lista_largo(lista) != (MAX-1-i)){ //Verificar largo de la lista
            status = false;
            break;
        }
    }
    print_test("Eliminar 10000 int y verificar que los elementos de la lista esten en el orden correspondiente",status);
    print_test("Eliminar primero (luego de haberla vaciado)", lista_iter_borrar(iter) == NULL);
    print_test("Ver primer elemento de lista vacia", lista_iter_ver_actual(iter) == NULL);
    print_test("lista esta vacia", lista_esta_vacia(lista) == true);
    print_test("Corroborar largo de la lista", !lista_largo(lista));

    lista_iter_destruir(iter);
    lista_destruir(lista,NULL);
}

bool imprimir(void *elemento, void *extra)
{
    int *contador = extra;
    printf("%d. %s\n", ++(*contador), (char*) elemento);

    return true; // seguir iterando
}

void test() {
    lista_t *super = lista_crear();

    lista_insertar_ultimo(super, "leche");
    lista_insertar_ultimo(super, "huevos");
    lista_insertar_ultimo(super, "pan");
    lista_insertar_ultimo(super, "mermelada");

    int num_items = 0;
    lista_iterar(super, imprimir, &num_items);
    printf("Tengo que comprar %d ítems\n", num_items);

    lista_destruir(super,NULL);
}
void pruebas_lista_alumno() {
    //Pruebas lista
    prueba_lista_vacia();
    prueba_un_elemento();
    prueba_varios_elementos();
    prueba_volumen();
    //Pruebas Iterador externo
    prueba_iterador_lista_vacia();
    prueba_iterador_un_elemento();
    prueba_iterador_varios_elementos();
    prueba_iterador_volumen();
    //Pruebas Iterador interno
    test();
}
