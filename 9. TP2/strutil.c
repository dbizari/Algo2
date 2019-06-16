#include "strutil.h"
#include <string.h>
#include <stdlib.h>

char *substr(const char *str, size_t n) {

	char* resultado = malloc((n+1)*sizeof(char));
	
	if (resultado == NULL) {
		return NULL;
	}

	strncpy(resultado, str, n);
	resultado[n] = '\0';
	return resultado;
}

char **split(const char *str, char sep) {
	size_t cant = 0;

	for (size_t i = 0; str[i]!='\0'; i++) {
		if (str[i] == sep) cant++;
	}

	char** arr = malloc((cant+2)*sizeof(char*));
	if (arr == NULL) return NULL;

	size_t pos_inicial = 0;
	size_t pos_final;
	size_t aux = 0;

	for(size_t i = 0; str[i]!='\0'; i++) {
		if (str[i] == sep) {
			pos_final = i;
			arr[aux] = substr(str + pos_inicial, pos_final - pos_inicial);
			pos_inicial = i+1;
			aux++;
		}

	}
	arr[aux] = substr(str + pos_inicial, strlen(str) - pos_inicial);
	arr[cant+1] = NULL;
	return arr;
	
}

char *join(char **strv, char sep) {
	size_t largo = 0;
	if (strv[0] != NULL) {
		for (size_t i = 0; strv[i]!=NULL; i++) {
			largo += strlen(strv[i]);
			if (sep) largo ++;
		}
	} else {
		largo = 1;
	}
	if (!sep) largo++;
	char* res = malloc(largo*sizeof(char));
	if (res == NULL) return NULL;

	size_t pos = 0;

	for(size_t i = 0; strv[i]!= NULL; i++) {
		for (size_t j = 0; strv[i][j]!='\0'; j++) {
			res[pos] = strv[i][j];
			pos++;
		}
		if (strv[i+1]!=NULL && sep) {
			res[pos] = sep;
			pos++;
		}	
	}
	res[largo-1]='\0';

	return res;	
}

void free_strv(char *strv[]) {
	for (size_t i = 0; strv[i]!=NULL; i++) {
		free(strv[i]);
	}
	free(strv);
}
