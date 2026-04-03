class RatePolicy:
    def calcular(self, horas, vehicle):
        raise NotImplementedError()


class HourlyRatePolicy(RatePolicy):
    def calcular(self, horas, vehicle):
        if vehicle.get_tipo() == "Car":
            return horas * 20
        elif vehicle.get_tipo() == "Motorcycle":
            return horas * 10
        return horas * 15


class FlatRatePolicy(RatePolicy):
    def calcular(self, horas, vehicle):
        return 50  # tarifa fija