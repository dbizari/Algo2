#include <stdlib.h>
#include "data_ptr.h"

// Definición de struct

struct data_ptr{
	char * array_char;
    char * pointer;
	size_t size;
	size_t used;
};

/* *****************************************************************
*                    PRIMITIVAS DE DATA_PTR
* *****************************************************************/
data_ptr_t* data_ptr_create(size_t size){
    data_ptr_t* aux = malloc(sizeof(data_ptr_t));
    if(!aux) return NULL;

    aux->array_char = calloc(size,sizeof(char));
    if(!aux->array_char) return NULL;

    aux->pointer = aux->array_char;
    aux->size = size;
    aux->used = 1;
    return aux;
}

void data_ptr_destroy(data_ptr_t *aux){
    free(aux->array_char);
    free(aux);
    return;
}

bool data_ptr_redimension(data_ptr_t * data_ptr,size_t new_size){
    char * aux = realloc(data_ptr->array_char, new_size * sizeof(char));
    if (new_size > 0 && !aux) return false;

    data_ptr->array_char  = aux;
    data_ptr->size = new_size;
    data_ptr->pointer = data_ptr->array_char;
    for (size_t i = 1; i < data_ptr->used; i++) {
        data_ptr->pointer++;
    }
    return true;
}

bool data_ptr_next(data_ptr_t *data_ptr){
    /*if(data_ptr->used == (data_ptr->size - 1)){
        if(!data_ptr_redimension(data_ptr,data_ptr->size * 2))
            return false;
    }*/
    data_ptr->pointer++;
    data_ptr->used++;
    return true;
}

bool data_ptr_prev(data_ptr_t *data_ptr){
    /*if(data_ptr->used <= data_ptr->size / 4){
        if(!data_ptr_redimension(data_ptr,data_ptr->size / 2))
            return false;
    }*/
    if(data_ptr->pointer == data_ptr->array_char)
        return false;

    data_ptr->pointer--;
    data_ptr->used--;
    return true;
}

void data_ptr_incf(data_ptr_t *data_ptr){
    (*data_ptr->pointer)++;
     return;
}

void data_ptr_decf(data_ptr_t *data_ptr){
    (*data_ptr->pointer)--;
     return;
}

char data_ptr_get(data_ptr_t *data_ptr){
    return (*data_ptr->pointer);
}

void data_ptr_set(data_ptr_t *data_ptr,char data){
    *data_ptr->pointer = data;
    return;
}
