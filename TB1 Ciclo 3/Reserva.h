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

	void mostrarDatosVuelo() {
		cout << "Vuelo: \n";
		vuelo->mostrarVuelo();
		cout << "Asientos: \n";
		for (int i = 0; i < asiento.size(); i++)
		{
			asiento[i]->mostrarAsiento();
		}
		cout << "Monto a pagar: " << precioFinal << endl; 
	}

	void mostrarDatosCompletos() {
		cout << "Pasajero: " << user->getNombres() << ", " << user->getApellidos() << "\n";
		cout << "DNI: " << user->getDni() << "\n";
		cout << "Vuelo: \n";
		/*vuelo->mostrarVuelo();*/
		cout << "Asientos: \n";
		for (int i = 0; i < asiento.size(); i++)
		{
			asiento[i]->mostrarAsiento();
		}
		cout << "Monto a pagar: " << precioFinal << endl;
	}

	Pasajero* getPasajero() { return user; }
	Vuelo* getVuelo() {	return vuelo; }
	int getPrecioFinal() { return precioFinal; }
};

#endif // _RESERVA_
