#ifndef _CHECKIN_
#define _CHECKIN_

#include "GestorReserva.h"

class CheckIn {
private:
	Reserva* reserva;
	Pasajero* psj;
	int puerta, hora; 
public:
	CheckIn() {
		puerta = 100 + rand() % (299 + 1 - 100); 
		hora = 0 + rand() % 24;
	}
	~CheckIn() {}

	// --- Función algo demás --- //

	void mostrarTarjeta(Reserva* reserva) {
		if (reserva == nullptr) return;
		int x = 31, y = 4;
		cout << BG_WHITE << BLACK;
		ubicar(x, y); cout << "|=============== TARJETA DE EMBARQUE ===============|";
		reserva->mostrarDatosCompletos(x, y += 1);
		ubicar(x, y += 11); cout << "Puerta: " << puerta;
		ubicar(x, y += 1); cout << "Hora de Embarque: " << hora;
		ubicar(x, y += 1); cout << "|===================================================|";
	}

	// --- Valida datos y procesa un Checkin y lo usamos en el GestorCheckIn --- //

	Reserva* procesarCheckIn(GestorReserva& gestorReserva) {
		string dni;
		int codigoVuelo, x = 31, y = 4;

		cout << BG_WHITE << BLACK;
		ubicar(x, y); cout << "Ingrese el DNI del pasajero: "; cin >> dni;
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

		ubicar(x, y += 1); cout << "No se encontro una reserva con el DNI y el codigo de vuelo proporcionados";
		return nullptr;
	}
};

#endif