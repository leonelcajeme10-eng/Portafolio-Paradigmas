class ParkingSpot:
    def __init__(self, spot_id, tipo_permitido):
        self._id = spot_id
        self._tipo_permitido = tipo_permitido
        self._ocupado = False

    def esta_libre(self):
        return not self._ocupado

    def ocupar(self):
        if self._ocupado:
            raise Exception("El lugar ya está ocupado")
        self._ocupado = True

    def liberar(self):
        self._ocupado = False

    def get_id(self):
        return self._id

    def get_tipo_permitido(self):
        return self._tipo_permitido