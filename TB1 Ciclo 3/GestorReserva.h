#ifndef _GRESERVA_
#define _GRESERVA_

#include "Pila.h"
#include "GestorUsuarios.h"
#include "Reserva.h"
#include "Gestortxt.h"
#include "GestorUsuarios.h"
#include "GestorVuelo.h"
#include <conio.h>
using namespace std;

auto confirmar = [](char c) -> bool {
	return c == 'y' || c == 'Y';
	};
auto asientoValido = [](Asiento* a) -> bool {
	return a != nullptr && a->getEstado() == 0;
	};


class GestorReserva
{
private:
	Pila<Reserva> reservas;
	GestorVuelo& gVuelos;
	GestorUsuarios& gUsuarios;
	//SE PASA POR REFERENCIA YA QUE ANTES COMO QUE SE CREABA UNA NUEVA LISTA DE USUARIOS 
	
public:
	GestorReserva(GestorVuelo& gVuelos, GestorUsuarios& gUsuarios)
		: gVuelos(gVuelos), gUsuarios(gUsuarios) {}
	~GestorReserva(){}

	void reservar() {
		int aux; int numAsientos; int aux2 = 0; int auxExcesoPorVip = 0; int cont = 0;
		char opc;
		cout << "Desea reservar un vuelo y/n: "; cin >> opc;
		if (!confirmar(opc)) return;
		
		cout << "\n === Reservar Vuelo ===\n";
		cout << "Seleccione usuario: \n";

		//Para que no continue si no hay usuarios registrados
		if (gUsuarios.getLista().esVacio()) {
			cout << "No hay usuarios registrados.\n";
			return;
		}

		gUsuarios.getLista().mostrarPasajero();
		cout << "Numero de usuario: ";
		cin >> aux2;

		Pasajero* pAux = gUsuarios.getLista().getDato(aux2 - 1); 
		if (pAux == nullptr) return; //REGRESA SI NO HAY USUARIO


		cout << "Ingrese id del vuelo: "; cin >> aux; cout << "\n"; 

		Vuelo* vAux = this->gVuelos.getVueloPorCodigo(aux);
		if (vAux == nullptr) return; //REGRESA SI EL VUELO NO EXISTE 
		Asiento* aAux;

		vector<Asiento*> asientos;

		cout << "Cantidad de asientos: "; cin >> numAsientos;

		//CALCULA LA CANTIDAD DE ASIENTOS LIBRES
		for (int i = 0; i < vAux->getVectorAsientos().size(); i++)
		{
			if (vAux->getVectorAsientos()[i]->getEstado() == 0)aux2++;
		};
		if (numAsientos > aux2) { cout << "\n Cantidad de asientos libres insuficientes\n"; system("pause"); return; } //REGRESA SI LA CANTIDAD DE ASIENTOS ES SUPERIOR

		cout << "\nNota: Por cada asiento VIP se adicionan 50 USD a la tarifa\n"; 
		for (int i = 0; i < numAsientos; i++)
		{ 
			cout << "\nSeleccione asiento " << i + 1 << " \n";
			vAux->mostrarAsientosDisponibles();
			do
			{
				cout << "Ingrese el id: "; 
				cin >> aux2;
				aAux = vAux->getAsiento(aux2);  cout << endl; system("pause>0");
				if (aAux == nullptr) return;
				if (!asientoValido(aAux)) cout << "Asiento ocupado\n";

			} while (!asientoValido(aAux));
			aAux->setEstado(1);

			//Calculo del extra a pagar por elegir VIP
			if (aAux->getClasificacion() == 'V') {
				cont++; 
				auxExcesoPorVip += 50;
			}

			asientos.push_back(aAux);
		}

		//Lambda para calcular del precio final de la compra
		auto calcularPrecioFinal = [&]() -> int {
			return (vAux->getPrecio() * numAsientos) + auxExcesoPorVip;
			};


		cout << "\nEscogio " << cont << " VIP y " << numAsientos - cont << " Economico\n"; 
		cout << "Monto a pagar: " << calcularPrecioFinal() << endl << endl;

		cout << "Confirmar la reserva: y/n: "; cin >> opc; if (!confirmar(opc)) return;
			
		Reserva a(vAux, asientos, pAux, calcularPrecioFinal());

		reservas.push(a);

		cout << "\nLa reserva se realizo con exito. \n"; system("pause>0");
	}

	void mostrarReservas() {
		Pila<Reserva> aux;

		while (!reservas.estaVacia()) {
			Reserva val = reservas.pop();
			val.mostrarDatosCompletos();
			aux.push(val);
		}

		while (!aux.estaVacia()) {
			reservas.push(aux.pop());
		}
	}

	Pila<Reserva> getReservas() {
		return reservas;
	}
};

#endif // !_RESERVAS_

