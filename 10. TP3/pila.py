class Pila:
    def __init__(self):
        self.arreglo = []

    def apilar(self, dato):
        self.arreglo.append(dato)

    def desapilar(self):
        return self.arreglo.pop()

    def esta_vacia(self):
        return len(self.arreglo) == 0

    def ver_tope(self):
        return self.arreglo[0]
