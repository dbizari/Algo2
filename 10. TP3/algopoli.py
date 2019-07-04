#!/usr/bin/python3

from pila import Pila
from grafo import Grafo
import csv
import biblioteca

COMANDOS = ["min_seguimientos", "mas_imp", "persecucion", "comunidades", "divulgar", "divulgar_ciclo", "cfc"]

def cargar_archivo(ruta):
    g = Grafo()
    with open(ruta) as archivo:
        arch = csv.reader(archivo, delimiter='\t')
        for linea in arch:
            v1, v2  = linea[0], linea[1]
            g.agregar_arista(v1, v2)
    return g

def main(ruta):
    grafo = cargar_archivo(ruta)
    comando = input()
    comando = comando.split(' ')
    if comando[0] == COMANDOS[0]:
        distancia, padre = biblioteca.camino_minimo_bfs(grafo, comando[1])
        if comando[2] not in distancia:
            print("Seguimiento imposible\n")
        else:
            p = Pila()
            aux = comando[2]
            while aux!=comando[1]:
                p.apilar(aux)
                aux = padre[aux]
            p.apilar(comando[1])
            while not p.esta_vacia():
                if p.ver_tope()!=comando[2]:
                    print(f"{p.desapilar()} -> ", end = '')
                else:
                    print(f"{p.desapilar()}")

main("mensajes.tsv")
