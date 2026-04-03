class RatePolicy:
    def calcular(self, horas, vehicle):
        raise NotImplementedError("Debe implementar calcular()")


class SimpleRatePolicy(RatePolicy):
    def calcular(self, horas, vehicle):
        return horas * 20  # tarifa simple