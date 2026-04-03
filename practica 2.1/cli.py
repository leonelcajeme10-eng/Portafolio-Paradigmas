from models.vehicle import Vehicle
from models.spot import ParkingSpot
from models.parking_lot import ParkingLot
from models.rates import SimpleRatePolicy
import os


def main():
    spots = [
        ParkingSpot("A1", "Car"),
        ParkingSpot("A2", "Car"),
        ParkingSpot("M1", "Motorcycle"),
        ParkingSpot("M2", "Motorcycle")
    ]

    rate = SimpleRatePolicy()
    parking = ParkingLot(spots, rate)

    while True:
        print("\n1. Entrada")
        print("2. Salida")
        print("3. Ver ocupacion")
        print("4. Ver tickets")
        print("5. Salir")

        opc = input("Opcion: ")

        if opc == "1":
            placas = input("Placas: ")
            tipo = input("Tipo (Car/Motorcycle): ")
            v = Vehicle(placas, tipo)
            parking.registrar_entrada(v)

        elif opc == "2":
            ticket_id = int(input("ID del ticket: "))
            horas = int(input("Horas: "))
            parking.registrar_salida(ticket_id, horas)

        elif opc == "3":
            parking.ver_ocupacion()

        elif opc == "4":
            parking.ver_tickets()

        elif opc == "5":
            break

        else:
            print("Opción inválida")


if __name__ == "__main__":
    main()