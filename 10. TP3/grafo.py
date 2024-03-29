import random

class Grafo:
    def __init__(self):
        self.vertices = {}
        self.cant_vertices = 0;

    def adyacentes(self,v):
        if v not in self.vertices: return []
        return self.vertices[v]

    def agregar_vertice(self, v):
        if v not in self.vertices:
            self.vertices[v] = []
            self.cant_vertices += 1

    def borrar_vertice(self, v):
        if v not in self.vertices: return
        del self.vertices[v]
        for w in grafo:
            if v in self.vertices[w]:
                self.vertices[w].pop(v)
        self.cant_vertices-=1

    def agregar_arista(self, v1, v2):
        #if v1 == v2: return
        if v1 not in self.vertices:
            self.agregar_vertice(v1)
        if v2 not in self.vertices:
            self.agregar_vertice(v2)
        self.vertices[v1].append(v2)

    def borrar_arista(self, v1, v2):
        if v1 not in self.vertices or v2 not in self.vertices:
            return
        self.vertices[v1].discard(v2) #Cambie remove por discard por si no se encuentra presente

    def obtener_vertices(self):
        return list(self.vertices.keys())

    def obtener_vertice_random(self):
        return random.choice(list(self.vertices.keys()))

    def estan_unidos(self, v1, v2):
        if v2 in self.vertices[v1]: return True
        return False

    def existe(self, v):
        return (v in self.vertices)

    def __iter__(self):
        return iter(self.vertices)
