import Grafo
import Cola

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
