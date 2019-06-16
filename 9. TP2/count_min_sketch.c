#include "count_min_sketch.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#define CANT_TABLAS 3
/* *****************************************************************
 *                          DEFINICIONES
 * *****************************************************************/

struct count_min_sketch {
	size_t** tablas;
	size_t tam;
	size_t cantidad_tablas;
};

typedef size_t (*fh_t)(const char *str);

//Funcion de Hash JBD2
size_t f_hash1(const char *str)
{
	size_t hash = 5381;
    int c;

    while ((c = *str++)) //Compilador pedia poner doble parentesis
        hash = ((hash << 5) + hash) + (size_t)c; /* hash * 33 + c */

    return hash;
}
// Funcion de Hash SDBM
size_t f_hash2(const char *str){
	unsigned long hash = 0;
    int c;

    while ((c = *str++))
        hash = (unsigned long)c + (hash << 6) + (hash << 16) - hash;

    return hash;
}
// Función de Hash sacada de http://www.cs.yale.edu/homes/aspnes/pinewiki/C(2f)HashTables.html?highlight=%28CategoryAlgorithmNotes%29
size_t f_hash3(const char *str)
{
	unsigned long hash;
    unsigned const char *us;

	/* cast s to unsigned const char * */
	/* this ensures that elements of s will be treated as having values >= 0 */
	us = (unsigned const char *) str;

	hash = 0;
	while(*us != '\0') {
		hash = hash * 37 + *us;
		us++;
	}

    return hash;
}

fh_t functions[3]={f_hash1,f_hash2,f_hash3};
/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/
//Devuelve array con posiciones
void get_positions(const count_min_sketch_t * cms,const char *clave,size_t * array){
	for (size_t i = 0; i < CANT_TABLAS; i++) {
		array[i] = functions[i](clave) % cms->tam;
	}
}
/* *****************************************************************
*                    PRIMITIVAS DE COUNT_MIN_SKETCH
* *****************************************************************/

count_min_sketch_t * count_min_sketch_crear(size_t tam){
	count_min_sketch_t* cms = malloc(sizeof(count_min_sketch_t));
	if(!cms) return NULL;

	cms->tablas = malloc(sizeof(size_t*) * CANT_TABLAS);
	if(!cms->tablas){
		free(cms);
		return NULL;
	}

	cms->cantidad_tablas = 0;

	for (size_t i = 0; i < CANT_TABLAS; i++) {
		cms->tablas[i] = calloc(tam,sizeof(size_t));
		if(!cms->tablas[i]){
			count_min_sketch_destruir(cms);
			return NULL;
		}
		cms->cantidad_tablas++;
	}
	cms->tam = tam;
	return cms;
}

void count_min_sketch_guardar(count_min_sketch_t *cms, const char *clave){
	size_t posiciones[CANT_TABLAS];

	get_positions(cms,clave,posiciones);
	for(size_t i = 0; i < CANT_TABLAS; i++){
		cms->tablas[i][posiciones[i]]++;
	}
}

size_t count_min_sketch_obtener_min(const count_min_sketch_t *cms, const char *clave){
	size_t posiciones[CANT_TABLAS];
	size_t min;

	printf("%s:\n",clave );
	get_positions(cms,clave,posiciones);
	min = cms->tablas[0][posiciones[0]];
	printf("Tabla1:%lu\t", cms->tablas[0][posiciones[0]]);
	for(size_t i = 1; i < CANT_TABLAS; i++){
		printf("Tabla%lu:%lu\t",i+1,cms->tablas[i][posiciones[i]]);
		if(cms->tablas[i][posiciones[i]] < min)
			min = cms->tablas[i][posiciones[i]];
	}
	putchar('\n');
	return min;
}

void count_min_sketch_destruir(count_min_sketch_t *cms){
	for (size_t i = 0; i < cms->cantidad_tablas; i++) {
		free(cms->tablas[i]);
	}
	free(cms->tablas);
	free(cms);
}
/*
int main(int argc, char const *argv[]) {
	count_min_sketch_t * cms= count_min_sketch_crear(10);

	count_min_sketch_guardar(cms,"gato");
	count_min_sketch_guardar(cms,"perro");
	count_min_sketch_guardar(cms,"parro");
	count_min_sketch_guardar(cms,"gbto");
	count_min_sketch_guardar(cms,"cor");
	count_min_sketch_guardar(cms,"csr");
	count_min_sketch_guardar(cms,"zzz");
	count_min_sketch_guardar(cms,"csasdfr");
	count_min_sketch_guardar(cms,"tumama");
	count_min_sketch_guardar(cms,"kiii");
	count_min_sketch_guardar(cms,"crre");


	printf("gato: %lu\tperro: %lu\n",count_min_sketch_obtener_min(cms,"asfad"),count_min_sketch_obtener_min(cms,"perro") );
	count_min_sketch_destruir(cms);
	return 0;
}*/
