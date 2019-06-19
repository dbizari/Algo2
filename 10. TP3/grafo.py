class grafo:
    def __init__(self):
        self.vertices = {}
        self.cant_vertices = 0;

    def adyacentes(self, vertice):
        res = []
        for ady in self.vertices[vertice]:
            res.append(ady)
        return res

    def agregar_vertice(self, v):
        self.vertices[v] = set()
        self.cant_vertices += 1

    def agregar_arista(self, v1, v2):
        if v1 not in self.vertices:
            self.vertices[v1] = {v2}
            self.cant_vertices += 1
        else if v2 not in self.vertices[v1]:
            self.vertices[v1].add(v2)
