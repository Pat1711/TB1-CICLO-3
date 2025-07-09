#ifndef _CHECKIN_
#define _CHECKIN_

#include "GestorReserva.h"

class CheckIn {
private:
	Reserva* reserva;
	Pasajero* psj;
public:
	CheckIn() {}
	~CheckIn() {}


	// --- Valida datos y procesa un Checkin y lo usamos en el GestorCheckIn --- //

	Reserva* procesarCheckIn(GestorReserva& gestorReserva, Pasajero*pasajero) {
		string dni;
		int codigoVuelo, x = 31, y = 4;

		if (!sesion) {
			cout << BG_WHITE << RED;
			ubicar(32, 4); cout << "Debe iniciar sesion para realizar un check in";
			system("pause>0"); return nullptr;
		}
		cout << BG_WHITE << BLACK;

		dni = pasajero->getDni();
        ubicar(x, y += 1); cout << "Ingrese Codigo del vuelo: "; cin >> codigoVuelo;

		Pila<Reserva> reservasAux = gestorReserva.getReservas(); //no referencia sino copia

		while (!reservasAux.estaVacia()) {
			Reserva reserva = reservasAux.pop();

			if (reserva.getPasajero()->getDni() == dni && reserva.getVuelo()->getCodigoVuelo() == codigoVuelo) {
				// Mostrar la tarjeta de embarque
				this->reserva = new Reserva(reserva);
				ubicar(x, y += 1); cout << "Check-in exitoso!";
				/*mostrarTarjeta(this->reserva);*/
				return this->reserva;
			}
		}

		ubicar(x, y += 1); cout << "No se encontraron reservas con el codigo de vuelo proporcionados";
		return nullptr;
	}
};

#endif