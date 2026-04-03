class Vehicle:
    def __init__(self, placas):
        self._placas = placas

    def get_placas(self):
        return self._placas

    def get_tipo(self):
        raise NotImplementedError()


class Car(Vehicle):
    def get_tipo(self):
        return "Car"


class Motorcycle(Vehicle):
    def get_tipo(self):
        return "Motorcycle"