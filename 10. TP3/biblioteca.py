from grafo import Grafo
from cola import Cola
from pila import Pila

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

def centralidad(grafo):
    cent = {}
    for v in grafo: cent[v] = 0
    for v in grafo:
        for w in grafo:
            if v == w: continue
            # con el algoritmo que corresponda al grafo
            distancia, padre = camino_minimo_bfs(grafo, v, w)
            # salteamos si no hay camino de v a w
            if w not in distancia: continue
            actual = padre[w]
            # le sumamos 1 a la centralidad de todos los vertices que se encuentren en
            # el medio del camino
            while actual != v:
                cent[actual] += 1
                actual = padre[actual]
    return cent



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
    for i in range(500):
        for v in labels:
            labels[v] = _max_freq(entradas, labels, v)

    resultado = {}
    for key, value in sorted(labels.items()):
        resultado.setdefault(value, []).append(key)
    return resultado
    #for v in resultado:
        #print(v,resultado[v])
