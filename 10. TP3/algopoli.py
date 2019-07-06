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

def _min_seguimientos(grafo, origen, destino):
    distancia, padre = biblioteca.camino_minimo_bfs(grafo, origen,destino)
    if destino not in distancia: return None
    p = Pila()
    aux = destino
    while aux != origen:
        p.apilar(aux)
        aux = padre[aux]
    p.apilar(origen)
    camino = []
    while not p.esta_vacia():
        camino.append(p.desapilar())
    return camino

def min_seguimientos(grafo, args):
    camino = _min_seguimientos(grafo, args[0], args[1])
    if not camino:
        print("Seguimiento imposible\n")
    else:
        print(*camino, sep = " -> ")

def _mas_imp(grafo, cant):
    centralidad = biblioteca.centralidad(grafo)
    cent_ordenado = sorted(centralidad.items(), key=operator.itemgetter(1))
    cent_ordenado.reverse()
    mas_imp_cant = []
    for i in range(cant):
        mas_imp_cant.append(cent_ordenado[i][0])
    return mas_imp_cant

def mas_imp(grafo, args):
    cant = int(args[0])
    mas_imp_cant = _mas_imp(grafo, cant)
    print(*mas_imp_cant, sep = ", ")

def persecucion(grafo, args):
    cant = int(args[len(args) - 1])
    mas_imp = _mas_imp(grafo, cant)
    importancia = {}
    for i in range(len(mas_imp)):
        importancia[mas_imp[i]] = i

    caminos = []
    for i in range(len(args) - 1):
        for j in range(cant):
            camino = _min_seguimientos(grafo, args[i], mas_imp[j])
            if camino:
                caminos.append(camino)
    caminos.sort(key = len) #ordeno de menos elementos a mas
    min = len(caminos[0])
    camino = caminos[0]
    for i in range(1, len(caminos)):
        if len(caminos[i]) > min: break
        d1 = camino[min-1]
        d2 = caminos[i][min-1]
        if importancia[d1] > importancia[d2]:
            camino = caminos[i]
    print(*camino, sep = " -> ")

def comunidades(grafo, args):
    n = int(args[0])
    comunidades = biblioteca.label_prop(grafo)
    cont_comu = 1
    for comu in comunidades:
        if len(comunidades[comu]) < n: continue
        print(f"Comunidad {cont_comu}: ", end = '')
        print(*comunidades[comu], sep=", ")
        cont_comu += 1

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
