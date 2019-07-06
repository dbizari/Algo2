#!/usr/bin/python3

from pila import Pila
from cola import Cola
from grafo import Grafo
import csv
import biblioteca
import sys
import operator

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
    origen  = args[0]
    destino = args[1]
    distancia, padre = biblioteca.camino_minimo_bfs(grafo, origen,destino)
    if destino not in distancia:
        print("Seguimiento imposible\n")
    else:
        p = Pila()
        aux = destino
        while aux != origen:
            p.apilar(aux)
            aux = padre[aux]
        p.apilar(origen)
        while not p.esta_vacia():
            if p.ver_tope()!=destino:
                print(f"{p.desapilar()} -> ", end = '')
            else:
                print(f"{p.desapilar()}")

def mas_imp(grafo, args):
    cant = int(args[0])
    centralidad = biblioteca.centralidad(grafo)
    cent_ordenado = sorted(centralidad.items(), key=operator.itemgetter(1))
    cent_ordenado.reverse()
    for i in range(cant):
        print(f"{cent_ordenado[i][0]}", end = '')
        if (i<cant-1): print(", ", end = '')
    print("\n")

def persecucion(grafo, args):
    print("persecucion",args)

def comunidades(grafo, args):
    n = int(args[0])
    biblioteca.label_prop(grafo)
    """for comu in comunidades:
        if len(comunidades[comu]) < n: continue
        print(*comunidades[comu], sep=", ")"""

def divulgar(grafo, args):
    origen = args[0]
    n = int(args[1])
    resultado=[]
    visitados = set()
    orden = {}
    orden[origen] = 0
    q = Cola()
    q.encolar(origen)
    visitados.add(origen)
    while not q.esta_vacia():
        v = q.desencolar()
        for w in grafo.adyacentes(v):
            if not w in visitados:
                orden[w] = orden[v] + 1
                if orden[w] > n:
                    print(*resultado, sep=", ")
                    return
                resultado.append(w)
                visitados.add(w)
                q.encolar(w)

def divulgar_ciclo(grafo, args):
    print("divulgar_ciclo",args)

def cfc(grafo, args):
    cfcs = biblioteca.cfc(grafo)
    for cfc in range(len(cfcs)):
        print(f"CFC {cfc + 1}: ", end = '')
        aux = cfcs[cfc]
        largo = len(aux)
        for v in range(largo):
            print(f"{aux[v]}", end = '')
            if v < largo - 1: print(", ", end = '')
        print("\n")

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
