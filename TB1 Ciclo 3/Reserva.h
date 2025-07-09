#ifndef _RESERVA_
#define _RESERVA
#include "Pasajero.h"
#include "Vuelo.h"
#include "Asiento.h"

class Reserva
{
private:
	Vuelo* vuelo;
	vector<Asiento*> asiento;
	Pasajero* user;
	int precioFinal; 
public:
	Reserva(){}
	Reserva(Vuelo *vuelo, vector<Asiento*> asiento, Pasajero* user, int precioFinal) {
		for (int i = 0; i < asiento.size(); i++)
		{
			asiento[i]->setEstado(1);
		}

		this->vuelo = vuelo;
		this->asiento = asiento;
		this->user = user;
		this->precioFinal = precioFinal;
	}
	~Reserva(){}

	void mostrarDatosCompletos(int x, int y) {
		cout << BG_WHITE << BLACK;
		ubicar(x, y); cout << "Pasajero: " << user->getNombres() << ", " << user->getApellidos();
		ubicar(x, y += 1); cout << "DNI: " << user->getDni();

		vuelo->mostrarVuelo2(x, y += 2);
		
		ubicar(x, y += 5); cout << "Asientos:";
		for (int i = 0; i < asiento.size(); i++) {
			ubicar(x, y += 1); asiento[i]->mostrarAsiento();
		}
		ubicar(x, y += 1); cout << "Monto a pagar: " << precioFinal;
	}

	void mostrarinCompletos(int x, int y) {
		cout << BG_WHITE << BLACK;
		vuelo->mostrarVuelo2(x, y);

		ubicar(x, y += 5); cout << "Asientos:";
		for (int i = 0; i < asiento.size(); i++) {
			ubicar(x, y += 1); asiento[i]->mostrarAsiento();
		}
		ubicar(x, y += 1); cout << "Monto a pagar: " << precioFinal;
	}

	Pasajero* getPasajero() { return user; }
	Vuelo* getVuelo() {	return vuelo; }
};

#endif // _RESERVA_
