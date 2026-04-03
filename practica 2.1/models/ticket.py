class Ticket:
    def __init__(self, ticket_id, vehicle, spot):
        self._id = ticket_id
        self._vehicle = vehicle
        self._spot = spot
        self._activo = True

    def cerrar(self):
        if not self._activo:
            raise Exception("El ticket ya está cerrado")
        self._activo = False

    def esta_activo(self):
        return self._activo

    def get_id(self):
        return self._id

    def get_vehicle(self):
        return self._vehicle

    def get_spot(self):
        return self._spot