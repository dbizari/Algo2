class Cola:
    def __init__(self):
        self.prim = None
        self.ult = None

    def encolar(self, dato):
        nodo = _Nodo(dato)
        if not self.prim:
            self.prim = nodo
        else:
            self.ult.prox = nodo
        self.ult = nodo

    def desencolar(self):
        nodo = self.prim
        if nodo == None:
            return None
        if nodo == self.ult:
            self.ult = None
        self.prim = nodo.prox
        return nodo.dato

    def esta_vacia(self):
        return self.prim == None

class _Nodo:
    def __init__(self, dato):
        self.dato  = dato
        self.prox = None
