from models.vehicle import Car, Motorcycle
from models.spot import ParkingSpot
from models.parking_lot import ParkingLot
from models.rates import HourlyRatePolicy, FlatRatePolicy


def main():
    # Crear spots
    spots = [
        ParkingSpot("A1", "Car"),
        ParkingSpot("A2", "Car"),
        ParkingSpot("M1", "Motorcycle"),
        ParkingSpot("M2", "Motorcycle")
    ]

    # Elegir política de cobro (puedes cambiarla)
    print("Selecciona politica de cobro:")
    print("1. Por hora")
    print("2. Tarifa fija")

    opc_rate = input("Opción: ")

    if opc_rate == "2":
        rate = FlatRatePolicy()
    else:
        rate = HourlyRatePolicy()

    parking = ParkingLot(spots, rate)

    while True:
        print("\n1. Entrada")
        print("2. Salida")
        print("3. Ver ocupación")
        print("4. Ver tickets")
        print("5. Salir")

        opc = input("Opción: ")

        if opc == "1":
            placas = input("Placas: ")
            tipo = input("Tipo (Car/Motorcycle): ")

            # Crear objeto correcto (HERENCIA)
            if tipo == "Car":
                v = Car(placas)
            elif tipo == "Motorcycle":
                v = Motorcycle(placas)
            else:
                print("Tipo invalido")
                continue

            parking.registrar_entrada(v)

        elif opc == "2":
            try:
                ticket_id = int(input("ID del ticket: "))
                horas = int(input("Horas: "))
                parking.registrar_salida(ticket_id, horas)
            except ValueError:
                print("Entrada invalida")

        elif opc == "3":
            parking.ver_ocupacion()

        elif opc == "4":
            parking.ver_tickets()

        elif opc == "5":
            print("Saliendo...")
            break

        else:
            print("Opción invalida")


if __name__ == "__main__":
    main()