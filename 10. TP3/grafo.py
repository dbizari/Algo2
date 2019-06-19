class grafo:
    def __init__(self):
        self.vertices = {}

    def adyacentes(self, vertice):
        res = []
        for ady in self.vertices[vertice]:
            res.append(ady)
        return res

    def agregar_arista(self, v1, v2):
        if v1 not in self.vertices:
            self.vertices[v1] = {v2}
        else:
            self.vertices[v1].add(v2)
