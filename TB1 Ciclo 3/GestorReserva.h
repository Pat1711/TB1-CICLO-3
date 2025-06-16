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
		default();
		menuSpawn("REALIZAR UNA RESERVA");
		int x = 4, y = 5;
		ubicar(x, y); cout << BG_GRISCLARO << BLACK << "1. Seleccionar Usuario";
		ubicar(x, y+=2); cout << "2. Id del vuelo";
		ubicar(x, y += 2); cout << "3. Seleccionar asientos";
		ubicar(x, y += 2); cout << "4. Resumen";
		

		int aux = 0; int numAsientos; int aux2 = 0; int auxExcesoPorVip = 0; int cont = 0;
		char opc = ' ';

		x = 35; y = 5;

		ubicar(x, y); cout << BG_WHITE << "Desea reservar un vuelo? y/n: ";  ingresarChar(opc); cin.ignore();

		if (!confirmar(opc)) return;
		
		ubicar(4, 5); cout << BG_GRISCLARO << JTAZUL << "1. Seleccionar Usuario" << BG_WHITE << BLACK;

		//Para que no continue si no hay usuarios registrados
		if (gUsuarios.getLista().esVacio()) {
			ubicar(x, y++); cout << "No hay usuarios registrados."; _getch();
			return;
		}

		gUsuarios.mostrar(80,5);
		ubicar(x, y+=2); cout << "Número de usuario: ";
		ingresarDatos(aux2);
		pintar(80, 5, 30, 20);

		Pasajero* pAux = gUsuarios.getLista().getDato(aux2 - 1); 
		if (pAux == nullptr) return; //REGRESA SI NO HAY USUARIO

		ubicar(4, 7); cout << BG_GRISCLARO << JTAZUL << "2. Id del vuelo" << BG_WHITE << BLACK;


		ubicar(x, y+=2); cout << "Ingrese id del vuelo: "; ingresarDatos(aux);

		Vuelo* vAux = this->gVuelos.getVueloPorCodigo(aux);
		if (vAux == nullptr){ ubicar(x, y += 2); cout << "El vuelo especificado no existe";  _getch(); return; } //REGRESA SI EL VUELO NO EXISTE 
		vAux->mostrarVuelo2(75,5);
		Asiento* aAux;

		vector<Asiento*> asientos;
		ubicar(4, 9); cout << BG_GRISCLARO << JTAZUL << "3. Seleccionar Asientos" << BG_WHITE << BLACK;

		ubicar(x, y += 2); cout << "Cantidad de asientos: "; ingresarDatos(numAsientos);

		//CALCULA LA CANTIDAD DE ASIENTOS LIBRES
		for (int i = 0; i < vAux->getVectorAsientos().size(); i++)
		{
			if (vAux->getVectorAsientos()[i]->getEstado() == 0)aux2++;
		};
		if (numAsientos > aux2-1) { ubicar(x, y += 2); cout << "Cantidad de asientos libres insuficientes"; _getch(); return; } //REGRESA SI LA CANTIDAD DE ASIENTOS ES SUPERIOR
		ubicar(x, y += 2); cout << "Nota: Por cada asiento VIP se adicionan 50 USD a la tarifa";

		vAux->mostrarMAsientos(83, 17); cout << BG_WHITE;
		y+=2;

		for (int i = 0; i < numAsientos; i++)
		{ 
			ubicar(85, 15); cout << "Seleccione asiento " << i + 1;

			do
			{
				ubicar(x, y++); cout << "Ingrese el id: "; ingresarDatos(aux2);
				aAux = vAux->getAsiento(aux2);
				if (aAux == nullptr) { ubicar(x, y++); "Asiento no válido."; return; }
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

		ubicar(4, 11); cout << BG_GRISCLARO << JTAZUL << "4. Resumen" << BG_WHITE << BLACK;

		ubicar(x, y += 2); cout << "Escogio " << cont << " VIP y " << numAsientos - cont << " Economico";
		ubicar(x, y += 1); cout << "Monto a pagar: " << calcularPrecioFinal();

		ubicar(x, y += 1); cout << "Confirmar la reserva: y/n: "; cin >> opc; if (!confirmar(opc)) return;
			
		Reserva a(vAux, asientos, pAux, calcularPrecioFinal());

		reservas.push(a);

		ubicar(x, y += 2); cout << "La reserva se realizo con exito."; _getch();
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

