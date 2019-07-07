from grafo import Grafo
from cola import Cola
from pila import Pila
import random

def camino_minimo(grafo, origen):
        visitados = set()
        distancia = {}
        padre = {}
        padre[origen] = None
        distancia[origen] = 0
        q = Cola()
        q.encolar(origen)
        visitados.add(origen)
        while not q.esta_vacia():
            v = q.desencolar()
            for w in grafo.adyacentes(v):
                if not w in visitados:
                    padre[w] = v
                    distancia[w] = distancia[v] + 1
                    visitados.add(w)
                    q.encolar(w)
        return distancia, padre

def camino_minimo_bfs(grafo, origen,destino):
    visitados = set()
    distancia = {}
    padre = {}
    padre[origen] = None
    distancia[origen] = 0
    q = Cola()
    q.encolar(origen)
    visitados.add(origen)
    while not q.esta_vacia():
        v = q.desencolar()
        for w in grafo.adyacentes(v):
            if not w in visitados:
                padre[w] = v
                distancia[w] = distancia[v] + 1
                visitados.add(w)
                if w == destino:
                    return distancia, padre
                q.encolar(w)
    return distancia, padre

def random_walks(grafo):
    apariciones = {}
    cant_vertices = len(grafo.obtener_vertices())
    largo = 100
    recorridos =  1500
    for v in grafo: apariciones[v] = 0
    for i in range(recorridos):
        vertice = grafo.obtener_vertice_random()
        apariciones[vertice] += 1
        for j in range(largo):
            adyacentes = grafo.adyacentes(vertice)
            if len(adyacentes) != 0:
                v2 = random.choice(adyacentes)
                apariciones[v2] += 1

    return apariciones

def dfs_cfc(grafo, v, visitados, orden, p, s, cfcs, en_cfs):
	visitados.add(v)
	s.apilar(v)
	p.apilar(v)
	for w in grafo.adyacentes(v):
		if w not in visitados:
			orden[w] = orden[v] + 1
			dfs_cfc(grafo, w, visitados, orden, p, s, cfcs, en_cfs)
		elif w not in en_cfs:
			while orden[p.ver_tope()] > orden[w]:
				p.desapilar()

	if p.ver_tope() == v:
		p.desapilar()
		z = None
		nueva_cfc = []
		while z != v:
			z = s.desapilar()
			en_cfs.add(z)
			nueva_cfc.append(z)
		cfcs.append(nueva_cfc)

def cfc(grafo):
	visitados = set()
	orden = {}
	p = Pila()
	s = Pila()
	cfcs = []
	en_cfs = set()
	for v in grafo:
		if v not in visitados:
			orden[v] = 0
			dfs_cfc(grafo, v, visitados, orden, p, s, cfcs, en_cfs)
	return cfcs

def _max_freq(entradas, labels, v):
    if entradas.get(v,0) == 0: return labels[v]
    if len(entradas[v]) == 0: return labels[v]
    aux = {}
    max = None
    for w in entradas[v]:
        label = labels[w]
        if not max: max = label
        aux[label] = aux.get(label, 0) + 1 #si no existe el valor w en el dic devuelve 0 mas 1
        if aux[label] > aux[max] : max = label #sino devuelve lo que hay mas 1
    return max

def label_prop(grafo):
    entradas = {}
    labels = {}
    count = 0
    for v in grafo:
        for w in grafo.adyacentes(v):
            if w not in entradas:
                entradas[w] = set()
            entradas[w].add(v)
        labels[v] = count
        count += 1
    for i in range(20):
        for v in labels:
            labels[v] = _max_freq(entradas, labels, v)

    resultado = {}
    for key, value in sorted(labels.items()):
        resultado.setdefault(value, []).append(key)
    return resultado
    #for v in resultado:
        #print(v,resultado[v])

def dfs_ciclo(grafo, v, buscado, visitados, sol_parcial, n):
    for w in grafo.adyacentes(v):
        #En realidad si necesitamos un set de visitados, para que en un mismo recorrido no se repitan datos!!! Entonces debe ser dinámico, cuando se va volviendo de la recursividad, se deben poder recorrer nuevamente
        if len(sol_parcial) > n:
            return None
        if w in visitados:
            if w == buscado and len(sol_parcial) == n:
                return reconstruir_ciclo(sol_parcial, buscado)
        else:
            visitados.add(w)
            sol_parcial.append(w)
            ciclo = dfs_ciclo(grafo, w, buscado, visitados, sol_parcial, n)
            visitados.remove(sol_parcial.pop())
            if ciclo is not None:
                return ciclo
    return None

def reconstruir_ciclo(sol_parcial, inicio):
    camino = []
    camino = sol_parcial.copy()
    camino.append(inicio)
    return camino
