class Cola:
    def __init__(self):
        self.prim = None
        self.ult = None
        self.largo = 0

    def encolar(self, dato):
        nodo = _Nodo(dato)
        if not self.prim:
            self.prim = nodo
        else:
            self.ult.prox = nodo
        self.ult = nodo
        self.largo += 1

    def desencolar(self):
        nodo = self.prim
        if nodo == None:
            return None
        if nodo == self.ult:
            self.ult = None
        self.prim = nodo.prox
        self.largo -= 1
        return nodo.dato

    def esta_vacia(self):
        return self.prim == None

    def ver_largo(self):
        return self.largo

class _Nodo:
    def __init__(self, dato):
        self.dato  = dato
        self.prox = None

q = Cola()
print(q.desencolar())
q.encolar(5)
q.encolar(6)
q.encolar(7)
q.encolar(8)
print(q.desencolar())
print(q.desencolar())
print(q.desencolar())
print(q.desencolar())
print(q.desencolar())
