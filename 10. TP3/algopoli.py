from grafo import Grafo
import csv

def cargar_archivo(ruta):
    g = Grafo()
    with open(ruta) as archivo:
        arch = csv.reader(archivo, delimiter='\t')
        for linea in arch:
            v1, v2  = linea[0], linea[1]
            g.agregar_arista(v1, v2)
    return g
