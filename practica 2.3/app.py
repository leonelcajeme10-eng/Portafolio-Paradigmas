from flask import Flask, render_template, request, redirect
from models.vehicle import Car, Motorcycle
from models.spot import ParkingSpot
from models.parking_lot import ParkingLot
from models.rates import HourlyRatePolicy

app = Flask(__name__)

# Inicializar sistema (igual que CLI)
spots = [
    ParkingSpot("A1", "Car"),
    ParkingSpot("A2", "Car"),
    ParkingSpot("M1", "Motorcycle"),
    ParkingSpot("M2", "Motorcycle")
]

rate = HourlyRatePolicy()
parking = ParkingLot(spots, rate)


@app.route("/")
def dashboard():
    libres = sum(1 for s in spots if s.esta_libre())
    ocupados = len(spots) - libres
    tickets = parking._tickets_activos.values()

    return render_template("dashboard.html",
                           libres=libres,
                           ocupados=ocupados,
                           tickets=tickets)


@app.route("/entry", methods=["GET", "POST"])
def entry():
    if request.method == "POST":
        placas = request.form["placas"]
        tipo = request.form["tipo"]

        if tipo == "Car":
            v = Car(placas)
        else:
            v = Motorcycle(placas)

        parking.registrar_entrada(v)
        return redirect("/")

    return render_template("entry.html")


@app.route("/exit", methods=["GET", "POST"])
def exit():
    if request.method == "POST":
        ticket_id = int(request.form["ticket_id"])
        horas = int(request.form["horas"])

        parking.registrar_salida(ticket_id, horas)
        return redirect("/")

    return render_template("exit.html")


if __name__ == "__main__":
    app.run(debug=True)