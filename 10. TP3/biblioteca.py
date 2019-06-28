from grafo import Grafo
from cola import Cola
from pila import Pila

def camino_minimo_bfs(grafo, origen):
    visitados = {}
    distancia = {}
    padre = {}
    padre[origen] = None
    distancia[origen] = 0
    q = Cola()
    q.encolar(origen)
    while not q.esta_vacia():
        v = q.desencolar()
        visitados[v] = True
        for w in grafo.adyacentes(v):
            if not w in visitados:
                padre[w] = v
                distancia[w] = distancia[v] + 1
                q.encolar(w)
    return distancia, padre

def centralidad(grafo):
    cent = {}
    for v in grafo: cent[v] = 0
    for v in grafo:
        # hacia todos los demas vertices
        distancia, padre = camino_minimo_bfs(grafo, v)
        cent_aux = {}
        for w in grafo: cent_aux[w] = 0
        # Aca filtramos (de ser necesario) los vertices a distancia infinita,
        # y ordenamos de mayor a menor
        vertices_ordenados = ordenar_vertices(grafo, distancia)
        for w in vertices_ordenados:
            cent_aux[padre[w]] += 1 + cent_aux[w]
        # le sumamos 1 a la centralidad de todos los vertices que se encuentren en
        # el medio del camino
        for w in grafo:
            if w == v: continue
            cent[w] += cent_aux[w]
    return cent


def dfs_cfc(grafo, v, visitados, orden, p, s, cfcs, en_cfcs):
	visitados.add(v)
	s.apilar(v)
	p.apilar(v)
	for w in grafo.adyacentes(v):
		if w not in visitados:
			orden[w] = orden[v] + 1
			dfs_cfc(grafo, w, visitados, orden, p, s, cfcs, en_cfcs)
		elif w not in en_cfcs:
			while orden[p.ver_tope()] > orden[w]:
				p.desapilar()

	if p.ver_tope() == v:
		p.desapilar()
		z = None
		nueva_cfc = []
		while z != v:
			z = s.desapilar()
			en_cfcs.add(z)
			nueva_cfc.append(z)
		cfcs.append(nueva_cfc)
		p.desapilar()

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
