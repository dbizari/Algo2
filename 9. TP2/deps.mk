CC := gcc
CFLAGS := -g -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion

procesar_tweets: procesar_tweets.o strutil.o count_min_sketch.o hash.o lista.o tag.o heap.o pila.o
procesar_usuarios: procesar_usuarios.o strutil.o hash.o lista.o heap.o