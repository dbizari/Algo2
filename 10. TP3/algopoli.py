#!/usr/bin/python3

from pila import Pila
from grafo import Grafo
import csv
import biblioteca
import sys

def validar_argumentos():
    if len(sys.argv) != 2:
        return None
    return sys.argv[1]

def cargar_archivo(ruta):
    g = Grafo()
    with open(ruta) as archivo:
        arch = csv.reader(archivo, delimiter='\t')
        for linea in arch:
            v1, v2  = linea[0], linea[1]
            g.agregar_arista(v1, v2)
    return g

def min_seguimientos(grafo, args):
    print("min_seg",args)
    """distancia, padre = biblioteca.camino_minimo_bfs(grafo, p1)
    if p2 not in distancia:
        print("Seguimiento imposible\n")
    else:
        p = Pila()
        aux = p2
        while aux!=p1:
            p.apilar(aux)
            aux = padre[aux]
        p.apilar(p1)
        while not p.esta_vacia():
            if p.ver_tope()!=p2:
                print(f"{p.desapilar()} -> ", end = '')
            else:
                print(f"{p.desapilar()}")"""

def mas_imp(grafo, args):
    print("mas_imp",args)

def persecucion(grafo, args):
    print("persecucion",args)

def comunidades(grafo, args):
    print("comunidades",args)

def divulgar(grafo, args):
    print("divulgar",args)

def divulgar_ciclo(grafo, args):
    print("divulgar_ciclo",args)

def cfc(grafo, args):
    print("cfc",args)

def main():
    ruta = validar_argumentos()
    if ruta == None: return None
    grafo = cargar_archivo(ruta)

    for line in sys.stdin:
        line = line.split()
        COMANDOS[line[0]](grafo,line[1:])

COMANDOS = {
    "min_seguimientos": min_seguimientos,
    "mas_imp": mas_imp,
    "persecucion": persecucion,
    "comunidades": comunidades,
    "divulgar": divulgar,
    "divulgar_ciclo": divulgar_ciclo,
    "cfc": cfc
}
MAX_ARGS = 2
main()
