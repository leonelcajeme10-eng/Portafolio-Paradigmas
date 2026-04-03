from models.ticket import Ticket

class ParkingLot:
    def __init__(self, spots, rate_policy):
        self._spots = spots
        self._rate_policy = rate_policy
        self._tickets_activos = {}
        self._contador_tickets = 1

    def registrar_entrada(self, vehicle):
        for spot in self._spots:
            if spot.esta_libre() and spot.get_tipo_permitido() == vehicle.get_tipo():
                spot.ocupar()
                ticket = Ticket(self._contador_tickets, vehicle, spot)
                self._tickets_activos[self._contador_tickets] = ticket
                self._contador_tickets += 1

                print(f"Ticket #{ticket.get_id()} asignado al spot {spot.get_id()}")
                return

        print("No hay lugares disponibles")

    def registrar_salida(self, ticket_id, horas):
        if ticket_id not in self._tickets_activos:
            print("Ticket no existe")
            return

        ticket = self._tickets_activos[ticket_id]
        ticket.cerrar()

        spot = ticket.get_spot()
        spot.liberar()

        costo = self._rate_policy.calcular(horas, ticket.get_vehicle())

        del self._tickets_activos[ticket_id]

        print(f"Salida completada. Costo: ${costo}")

    def ver_ocupacion(self):
        libres = sum(1 for s in self._spots if s.esta_libre())
        ocupados = len(self._spots) - libres
        print(f"Libres: {libres}, Ocupados: {ocupados}")

    def ver_tickets(self):
        if not self._tickets_activos:
            print("No hay tickets activos")
            return

        for t in self._tickets_activos.values():
            print(f"Ticket #{t.get_id()} - {t.get_vehicle().get_placas()}")