#include "cola.h"
#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>

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
void prueba_cola_vacia(){
    cola_t* cola = cola_crear();

    print_test("Creacion de Cola", cola != NULL);
    print_test("Desencolar cola vacia", cola_desencolar(cola) == NULL);
    print_test("Ver primer elemento de cola vacia", cola_ver_primero(cola) == NULL);
    print_test("Cola esta vacia", cola_esta_vacia(cola) == true);
    cola_destruir(cola,destruir_dato);
    print_test("Destruir cola vacia",true);
    return;
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

void prueba_varios_elementos(){
    cola_t* cola = cola_crear();
    int num=10;
    char letra='a';
    long num_long;
    char palabra[10]="Test";
    float random[15]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    bool status;
    //Apilar varios datos de distinto tipo
    print_test("Encolar int", cola_encolar(cola,&num) == true);
    print_test("Encolar char", cola_encolar(cola,&letra) == true);
    print_test("Encolar NULL", cola_encolar(cola,NULL) == true);
    print_test("Encolar long", cola_encolar(cola,&num_long) == true);
    print_test("Encolar string", cola_encolar(cola,palabra) == true);
    print_test("Cola esta vacia?", cola_esta_vacia(cola) == false);
    print_test("Desencolar int", cola_desencolar(cola) == &num);
    print_test("Desencolar char", cola_desencolar(cola) == &letra);
    print_test("Desencolar NULL", cola_desencolar(cola) == NULL);
    print_test("Desencolar long", cola_desencolar(cola) == &num_long);
    print_test("Desencolar string", cola_desencolar(cola) == palabra);
    print_test("Cola esta vacia?", cola_esta_vacia(cola) == true);

    status = true;
    for(int i = 0; i < 15; i++){
        if((cola_encolar(cola,&random[i])) == false){
            status = false;
            break;
        }
    }

    print_test("Encolar 15 floats de un vector", status == true);
    print_test("Ver primero", cola_ver_primero(cola) == &random[0]);

    status = true;
    for(int i = 0; i < 8; i++){
        if(cola_desencolar(cola) != &random[i]){
            status=false;
            break;
        }
    }
    print_test("Desencolar 7 elementos corroborando orden", status == true);
    print_test("Ver primero", cola_ver_primero(cola) == &random[8]);

    cola_destruir(cola,NULL);
    print_test("Destruir cola con 7 elementos",true);
    return;
}

void prueba_volumen(){
    cola_t* cola = cola_crear();
    int vec[MAX];
    int * vec_pointers[MAX];
    bool status=true;
    int * aux;

    for(int i = 0; i < MAX; i++){
        vec[i]=i+1;
        if(cola_encolar(cola,&vec[i]) == false){
            status=false;
            break;
        }
    }

    print_test("Encolar 10000 int",status);
    print_test("Cola con elementos esta vacia?", cola_esta_vacia(cola) == false);

    aux =(int *)cola_ver_primero(cola);
    print_test("Corrobar que primer elemento sea 1",*aux==1);

    status=true;
    for(int i = 0; i < MAX; i++){
        aux =(int *)cola_desencolar(cola);
        if(*aux != vec[i]){
            status=false;
            break;
        }
    }
    print_test("Desencolar 10000 int y verificar que los elementos de la cola esten en el orden correspondiente",status);
    print_test("Desencolar cola (luego de haberla Desencolado por completo)", cola_desencolar(cola) == NULL);
    print_test("Ver primer elemento de cola vacia (luego de haberla Desencolado por completo)", cola_ver_primero(cola) == NULL);
    print_test("Cola esta vacia", cola_esta_vacia(cola) == true);

    for(int i = 0; i < MAX; i++){
        if((vec_pointers[i] = malloc(sizeof(int))) == NULL){
            cola_destruir(cola,NULL);
            return;
        }
        *vec_pointers[i] = i * 2;
    }
    status = true;
    for(int i = 0; i < MAX; i++){
        if((i % 2) == 0){
            if(cola_encolar(cola,NULL) == false){
                status=false;
                break;
            }
        }else{
            if(cola_encolar(cola,vec_pointers[i]) == false){
                status=false;
                break;
            }
        }
    }
    print_test("Encolar NULL e int de forma intercalada",status);
    print_test("Corrobar que primer elemento sea NULL",cola_ver_primero(cola)==NULL);

    for(int i = 0; i < 1000; i++){
        aux =(int *)cola_desencolar(cola);
        if((i % 2) == 0){
            if(aux != NULL){
                status=false;
                break;
            }
        }else{
            if(aux != vec_pointers[i]){
                status=false;
                break;
            }
        }
        free(vec_pointers[i]);
    }

    print_test("Desencolar y verificar que los elementos de la cola esten en el orden correspondiente",status);

    cola_destruir(cola,destruir_dato);
    for(int i = 1000; i < MAX; i++) //Libero memoria de los elementos que no se cargaron en la cola
        if((i % 2) == 0)
            free(vec_pointers[i]);

    print_test("Destruir cola con 9000 elementos",true);
    return;
}
void pruebas_cola_alumno() {

    prueba_cola_vacia();
    prueba_un_elemento();
    prueba_varios_elementos();
    prueba_volumen();
}
