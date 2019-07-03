import random

class Grafo:
    def __init__(self):
        self.vertices = {}
        self.cant_vertices = 0;

    def adyacentes(self,v):
        if v not in self.vertices: return None
        return list(self.vertices[v])

    def agregar_vertice(self, v):
        if v not in self.vertices:
            self.vertices[v] = set()
            self.cant_vertices += 1

    def borrar_vertice(self, v):
        if v not in self.vertices: return
        del self.vertices[v]
        self.cant_vertices-=1

    def agregar_arista(self, v1, v2):
        if v1 == v2: return
        if v1 not in self.vertices:
            self.agregar_vertice(v1)
        if v2 not in self.vertices:
            self.agregar_vertice(v2)
        self.vertices[v1].add(v2)

    def borrar_arista(self, v1, v2):
        if v1 not in self.vertices or v2 not in self.vertices:
            return
        self.vertices[v1].discard(v2) #Cambie remove por discard por si no se encuentra presente

    def obtener_vertices(self):
        vertices = []
        for v in self.vertices:
            vertices.append(v)
        return vertices

    def obtener_vertice_random(self):
        return random.choice(list(self.vertices.keys()))

    def estan_unidos(self, v1, v2):
        if v2 in self.vertices[v1]: return True
        return False

    def __iter__(self):
        return iter(self.vertices)
