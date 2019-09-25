#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>

#define MAX 10000
/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
void prueba_pila_vacia(){
    pila_t* pila = pila_crear();

    print_test("Creacion de Pila", pila != NULL);
    print_test("Desapilar pila vacia", pila_desapilar(pila) == NULL);
    print_test("Ver ultimo elemento de pila vacia", pila_ver_tope(pila) == NULL);
    print_test("Pila esta vacia", pila_esta_vacia(pila) == true);
    pila_destruir(pila);
    print_test("Destruir pila vacia",true);
    return;
}

void prueba_un_elemento(){
    pila_t* pila = pila_crear();
    int num=10;
    char letra='a';
    long num_long;
    char palabra[10]="Test";

    //Pruebas con int
    print_test("Apilar int", pila_apilar(pila,&num) == true);
    print_test("Ver tope", pila_ver_tope(pila) == &num);
    print_test("Pila esta vacia?", pila_esta_vacia(pila) == false);
    print_test("Desapilar int", pila_desapilar(pila) == &num);
    //Pruebas con char
    print_test("Apilar char", pila_apilar(pila,&letra) == true);
    print_test("Ver tope", pila_ver_tope(pila) == &letra);
    print_test("Pila esta vacia?", pila_esta_vacia(pila) == false);
    print_test("Desapilar char", pila_desapilar(pila) == &letra);
    //Pruebas con NULL
    print_test("Apilar NULL", pila_apilar(pila,NULL) == true);
    print_test("Ver tope", pila_ver_tope(pila) == NULL);
    print_test("Pila esta vacia?", pila_esta_vacia(pila) == false);
    print_test("Desapilar NULL", pila_desapilar(pila) == NULL);
    //Pruebas con long
    print_test("Apilar long", pila_apilar(pila,&num_long) == true);
    print_test("Ver tope", pila_ver_tope(pila) == &num_long);
    print_test("Pila esta vacia?", pila_esta_vacia(pila) == false);
    print_test("Desapilar long", pila_desapilar(pila) == &num_long);
    //Pruebas con string
    print_test("Apilar string", pila_apilar(pila,palabra) == true);
    print_test("Ver tope", pila_ver_tope(pila) == palabra);
    print_test("Pila esta vacia?", pila_esta_vacia(pila) == false);
    print_test("Desapilar string", pila_desapilar(pila) == palabra);
    //Destruir pila con un elemento apilado
    pila_apilar(pila,palabra);
    pila_destruir(pila);
    print_test("Destruir pila con un elemento",true);
    return;
}

void prueba_varios_elementos(){
    pila_t* pila = pila_crear();
    int num=10;
    char letra='a';
    long num_long;
    char palabra[10]="Test";
    float random[15]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    bool status;
    //Apilar varios datos de distinto tipo
    print_test("Apilar int", pila_apilar(pila,&num) == true);
    print_test("Apilar char", pila_apilar(pila,&letra) == true);
    print_test("Apilar NULL", pila_apilar(pila,NULL) == true);
    print_test("Apilar long", pila_apilar(pila,&num_long) == true);
    print_test("Apilar string", pila_apilar(pila,palabra) == true);
    print_test("Pila esta vacia?", pila_esta_vacia(pila) == false);
    print_test("Desapilar string", pila_desapilar(pila) == palabra);
    print_test("Desapilar long", pila_desapilar(pila) == &num_long);
    print_test("Desapilar NULL", pila_desapilar(pila) == NULL);
    print_test("Desapilar char", pila_desapilar(pila) == &letra);
    print_test("Desapilar int", pila_desapilar(pila) == &num);
    print_test("Pila esta vacia?", pila_esta_vacia(pila) == true);

    status = true;
    for(int i = 0; i < 15; i++){
        if((pila_apilar(pila,&random[i])) == false){
            status = false;
            break;
        }
    }

    print_test("Apilar 15 floats de un vector", status == true);
    print_test("Ver tope", pila_ver_tope(pila) == &random[14]);

    status = true;
    for(int i = 14; i >= 7; i--){
        if(pila_desapilar(pila) != &random[i]){
            status=false;
            break;
        }
    }
    print_test("Desapilar 7 elementos corroborando orden", status == true);
    print_test("Ver tope", pila_ver_tope(pila) == &random[6]);

    pila_destruir(pila);
    print_test("Destruir pila con 7 elementos",true);
    return;
}

void prueba_volumen(){
    pila_t* pila = pila_crear();
    int vec[MAX];
    bool status=true;
    int * aux;

    for(int i = 0; i < MAX; i++){
        vec[i]=i+1;
        if(pila_apilar(pila,&vec[i]) == false){
            status=false;
            break;
        }
        aux =(int *)pila_ver_tope(pila);
        if(*aux != vec[i]){
            status=false;
            break;
        }
    }
    print_test("Apilar 10000 int y verificar que tope sea correcto para cada elemento",status);
    print_test("Pila con elementos esta vacia?", pila_esta_vacia(pila) == false);

    aux =(int *)pila_ver_tope(pila);
    print_test("Corrobar que tope sea 10000",*aux==MAX);

    status=true;
    for(int i = MAX-1; i >= 0; i--){
        aux =(int *)pila_desapilar(pila);
        if(*aux != vec[i]){
            status=false;
            break;
        }
    }
    print_test("Desapilar 10000 int y verificar que los elementos desapilados sean correctos",status);
    print_test("Desapilar pila (luego de haberla desapilado por completo)", pila_desapilar(pila) == NULL);
    print_test("Ver ultimo elemento de pila vacia (luego de haberla desapilado por completo)", pila_ver_tope(pila) == NULL);
    print_test("Pila esta vacia", pila_esta_vacia(pila) == true);

    status = true;
    for(int i = 0; i < MAX-1; i++){
        if((i % 2) == 0){
            if(pila_apilar(pila,NULL) == false){
                status=false;
                break;
            }
            if(pila_ver_tope(pila) != NULL){
                status=false;
                break;
            }
        } else{
            if(pila_apilar(pila,&vec[i]) == false){
                status=false;
                break;
            }
            aux =(int *)pila_ver_tope(pila);
            if(*aux != vec[i]){
                status=false;
                break;
            }
        }
    }
    print_test("Apilar NULL e int de forma intercalada y verificar que tope sea correcto para cada elemento",status);
    print_test("Corrobar que ultimo elemento sea NULL",pila_ver_tope(pila)==NULL);

    for(int i = MAX-2; i > 1000; i--){
        aux =(int *)pila_desapilar(pila);
        if((i % 2) == 0){
            if(aux != NULL){
                status=false;
                break;
            }
        }else{
            if(*aux != vec[i]){
                status=false;
                break;
            }
        }
    }
    print_test("Desapilar verificar que los elementos de la pila sean correctos",status);

    pila_destruir(pila);
    print_test("Destruir pila con 1000 elementos",true);
    return;
}
void pruebas_pila_alumno() {

    prueba_pila_vacia();
    prueba_un_elemento();
    prueba_varios_elementos();
    prueba_volumen();
}
