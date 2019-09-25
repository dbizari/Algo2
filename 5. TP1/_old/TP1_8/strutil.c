#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/*
 * Libera un arreglo dinámico de cadenas, y todas las cadenas que contiene.
 */
void free_strv(char *strv[]){
	for (size_t i = 0;strv[i] != NULL; i++) {
		free(strv[i]);
	}
	free(strv);
	return;
}

char ** create_strv(const char *str, char sep){
	char * pch,**arr_str;
	size_t length = 0;
	//Determino largo del array
	for(pch=strchr(str,sep); pch!=NULL && *pch!='\0' ; pch=strchr(pch+1,sep),length++);
	length+=2; //Agrego posicion para el ultimo elemento y para el NULL
	arr_str = malloc(sizeof(char *) * length);
	if(!arr_str) return NULL;

	arr_str[0] = NULL; //Indico que no tiene datos
	return arr_str;
}

char * substr(const char *str, size_t n){
	size_t length;
	char * str_aux;

	if((length = strlen(str)) > n)
		length = n;

	str_aux = malloc(sizeof(char) * (length + 1)); // \0
	if(!str_aux)
		return NULL;

	strncpy(str_aux,str,length);
	str_aux[length] = '\0'; //En la documentacion de http://www.cplusplus.com/reference/cstring/strncpy/
	// indica que el '\0' no es agregado de forma automatica.
	return str_aux;
}

char ** split(const char *str, char sep){
	char ** arr_str,*aux_str;
	size_t str_length = strlen(str),added = 0;

	if((arr_str = create_strv(str,sep)) == NULL)
		return NULL;

	for(size_t i = 0,tmp_len = 0,start_index = 0; i < str_length + 1; i++){
		if(str[i] != sep && str[i] != '\0'){
			tmp_len++;
			continue;
		}
		aux_str = substr(&str[start_index],tmp_len); //Copio subcadena en nuevo
		if(!aux_str) free_strv(arr_str);
		arr_str[added++] = aux_str; //Agrego al array e incremento indice
		tmp_len = 0;              //Limpio contador de largo
		start_index = i+1;      //Apunto a primer elemento de nueva cadena
	}
	arr_str[added] = NULL; //Agrego NULL indicando que no hay mas elementos
	return arr_str;
}

char * join(char **strv, char sep){
	size_t total_length = 0;
	char* aux_str;


	for(size_t i = 0; strv[i] ; i++){
		total_length += strlen(strv[i]);
		if(sep != '\0')
			total_length++; //separador o \0 al final
	}
	if(sep == '\0') //Para agergar el \0 al final
		total_length++;

	if(!strv || total_length == 0){
		aux_str = malloc(sizeof(char));
		aux_str[0] = '\0';
		return aux_str;
	}

	aux_str = malloc(sizeof(char) * total_length);
	if(!aux_str) return NULL;

	for(size_t i = 0,aux_index = 0; strv[i] ; i++){
		strcpy(&aux_str[aux_index],strv[i]);
		aux_index += strlen(strv[i]);
		if(strv[i+1] && sep != '\0')
			aux_str[aux_index++] = sep;
	}
	aux_str[total_length - 1] = '\0';
	return aux_str;
}
