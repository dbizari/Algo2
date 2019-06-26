class Cola:
    def __init__(self):
        self.prim = None
        self.ult = None
        self.cant = 0

    def encolar(self, dato):
        nodo = _Nodo(dato)
        if not self.prim:
            self.prim = nodo
        else:
            self.ult.prox = nodo
        self.ult = nodo
        self.cant += 1

    def desencolar(self):
        nodo = self.prim
        if nodo:
            self.prim = nodo.prox
            self.cant -= 1
            return nodo.dato
        else:
            return None

    def esta_vacia(self):
        return self.cant == 0


class _Nodo:
    def __init__(self, dato):
        self.dato  = dato
        self.prox = None
