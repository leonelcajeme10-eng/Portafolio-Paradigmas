class Vehicle:
    def __init__(self, placas, tipo):
        self._placas = placas
        self._tipo = tipo

    def get_placas(self):
        return self._placas

    def get_tipo(self):
        return self._tipo