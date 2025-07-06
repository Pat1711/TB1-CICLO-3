#ifndef _GRESERVA_
#define _GRESERVA_

#include "Pila.h"
#include "Sistema.h"
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
		menuSpawn("REALIZAR UNA RESERVA");
		int x = 4, y = 5;
		cout << BG_GRISCLARO << BLACK;
		ubicar(x, y); cout << "1. Id del vuelo";
		ubicar(x, y += 2); cout << "2. Seleccionar asientos";
		ubicar(x, y += 2); cout << "3. Resumen";
		

		int aux = 0; int numAsientos; int aux2 = 0; int auxExcesoPorVip = 0; int cont = 0;
		char opc = ' ';

		x = 35; y = 5;

		//Para que no continue si no inicio sesion
		if (sesion == false) {
			ubicar(x, y++); cout << BG_WHITE << JTROJO << "Debe iniciar sesion para reservar un vuelo"; (void)_getch(); limpiarDerecha();
			return;
		}

		ubicar(x, y++); cout << "INGRESE LOS DATOS SOLICITADOS";

		Pasajero* pAux = gUsuarios.getusuario();

		ubicar(4, 5); cout << BG_GRISCLARO << JTAZUL << "1. Id del vuelo" << BG_WHITE << BLACK;


		ubicar(x, y+=2); cout << "Ingrese id del vuelo: "; ingresarDato(aux);

		Vuelo* vAux = this->gVuelos.getVueloPorCodigo(aux);
		if (vAux == nullptr){ ubicar(x, y += 2); cout << "El vuelo especificado no existe"; (void)_getch(); limpiarDerecha(); return; } //REGRESA SI EL VUELO NO EXISTE 
		vAux->mostrarVuelo2(75,5);
		Asiento* aAux;

		vector<Asiento*> asientos;
		ubicar(4, 7); cout << BG_GRISCLARO << JTAZUL << "2. Seleccionar Asientos" << BG_WHITE << BLACK;

		ubicar(x, y += 2); cout << "Cantidad de asientos: "; ingresarDato(numAsientos);

		//CALCULA LA CANTIDAD DE ASIENTOS LIBRES
		for (int i = 0; i < vAux->getVectorAsientos().size(); i++)
		{
			if (vAux->getVectorAsientos()[i]->getEstado() == 0)aux2++;
		};
		if (numAsientos > aux2-1) { ubicar(x, y += 2); cout << "Cantidad de asientos libres insuficientes"; (void)_getch(); limpiarDerecha(); return; } //REGRESA SI LA CANTIDAD DE ASIENTOS ES SUPERIOR
		ubicar(x, y += 2); cout << "Nota: Por cada asiento VIP se adicionan 50 USD a la tarifa";

		vAux->mostrarMAsientos(83, 17); cout << BG_WHITE;
		y+=2;

		for (int i = 0; i < numAsientos; i++)
		{ 
			ubicar(85, 15); cout << "Seleccione asiento " << i + 1;

			do
			{
				ubicar(x, y++); cout << "Ingrese el id: "; ingresarDato(aux2);
				aAux = vAux->getAsiento(aux2);
				if (aAux == nullptr) { ubicar(x, y++); "Asiento no válido."; limpiarDerecha(); return; }
				if (!asientoValido(aAux)) { ubicar(x, y++); cout << "Asiento ocupado"; }
				if (y > 21) { y -= 7; x += 20; }

			} while (!asientoValido(aAux));

			aAux->setEstado(1);

			//Calculo del extra a pagar por elegir VIP
			if (aAux->getClasificacion() == 'V') {
				cont++; 
				auxExcesoPorVip += 50;
			}

			asientos.push_back(aAux);
			vAux->mostrarMAsientos(83, 17); cout << BG_WHITE;
		}
		if (x > 35) {
			x = 35; y = 21;
		}
		//Lambda para calcular del precio final de la compra
		auto calcularPrecioFinal = [&]() -> int {
			return (vAux->getPrecio() * numAsientos) + auxExcesoPorVip;
			};

		ubicar(4, 9); cout << BG_GRISCLARO << JTAZUL << "3. Resumen" << BG_WHITE << BLACK;

		ubicar(x, y += 2); cout << "Escogio " << cont << " VIP y " << numAsientos - cont << " Economico";
		ubicar(x, y += 1); cout << "Monto a pagar: " << calcularPrecioFinal();

		ubicar(x, y += 1); cout << "Confirmar la reserva: y/n: "; cin >> opc; if (!confirmar(opc)) { limpiarDerecha(); return; }
			
		Reserva a(vAux, asientos, pAux, calcularPrecioFinal());

		reservas.push(a);
		
		ubicar(x, y += 2); cout << "La reserva se realizo con exito."; (void)_getch(); limpiarDerecha(); //creo que es mejor usar el cin.get :v solo estan pausando esta linea
	}

	void mostrarReservas() {
		if (!reservas.estaVacia()) {
			Pila<Reserva> aux;

			while (!reservas.estaVacia()) {
				Reserva val = reservas.pop();
				val.mostrarDatosCompletos(31, 4);
				aux.push(val);
			}

			while (!aux.estaVacia()) {
				reservas.push(aux.pop());
			}
		}

		else {
			cout << BG_WHITE << BLACK;
			ubicar(32, 4); cout << "No hay ninguna reserva";
		}
	}

	Pila<Reserva> getReservas() {
		return reservas;
	}
};

#endif // !_RESERVAS_

