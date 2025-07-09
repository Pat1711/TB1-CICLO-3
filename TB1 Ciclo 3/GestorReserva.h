#ifndef _GRESERVA_
#define _GRESERVA_

#include "Pila.h"
#include "Sistema.h"
#include "GestorUsuarios.h"
#include "Reserva.h"
#include "Gestortxt.h"
#include "GestorUsuarios.h"
#include "GestorVuelo.h"
#include "Descuento.h"
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
	Descuento* descuento;  
	//SE PASA POR REFERENCIA YA QUE ANTES COMO QUE SE CREABA UNA NUEVA LISTA DE USUARIOS 

public:
	GestorReserva(GestorVuelo& gVuelos, GestorUsuarios& gUsuarios)
		: gVuelos(gVuelos), gUsuarios(gUsuarios) {
		descuento = new Descuento; 
	}
	~GestorReserva() {}

	void reservar(vector<vector<Vuelo*>> rutasValidas = vector<vector<Vuelo*>>()) {
		default();
		menuSpawn("REALIZAR UNA RESERVA");

		int aux = 0, n = 0, aux3; int numAsientos; int aux2 = 0; int auxExcesoPorVip = 0; int cont = 0; float auxDescuento = 0.0f;
		char opc = ' ';
		string texto;

		if(!rutasValidas.empty()){
			ubicar(35, 4); cout << BG_WHITE << BLACK << "Ruta a reservar: "; ingresarDato(n);
			aux3 = static_cast<int>(rutasValidas[n].size());
		}
		else {
			aux3 = 1;
		}
		
		for (int i = 0; i < aux3; i++)
		{
			aux = 0; numAsientos = 0; aux2 = 0; auxExcesoPorVip = 0; cont = 0; auxDescuento = 0.0f;
			opc = ' ';

			int x = 4, y = 5;
			cout << BG_GRISCLARO << BLACK;
			ubicar(x, y); cout << "1. Id del vuelo";
			ubicar(x, y += 2); cout << "2. Seleccionar asientos";
			ubicar(x, y += 2); cout << "3. Resumen";

			x = 35; y = 5;

			//Para que no continue si no inicio sesion
			if (sesion == false) {
				ubicar(x, y++); cout << BG_WHITE << JTROJO << "Debe iniciar sesion para reservar un vuelo"; (void)_getch(); limpiarDerecha();
				return;
			}

			ubicar(x, y++); cout << "INGRESE LOS DATOS SOLICITADOS";
			Pasajero* pAux = gUsuarios.getusuario();


			ubicar(4, 5); cout << BG_GRISCLARO << JTAZUL << "1. Id del vuelo" << BG_WHITE << BLACK;

			if (rutasValidas.empty()) {
				ubicar(x, y += 2); cout << "Ingrese id del vuelo: "; ingresarDato(aux);
			}
			else {
				aux = rutasValidas[n][i]->getCodigoVuelo();
			}
			Vuelo* vAux = this->gVuelos.getVueloPorCodigo(aux);
			if (vAux == nullptr) { ubicar(x, y += 2); cout << "El vuelo especificado no existe"; (void)_getch(); limpiarDerecha(); return; } //REGRESA SI EL VUELO NO EXISTE 
			vAux->mostrarVuelo2(75, 5);
			Asiento* aAux;

			vector<Asiento*> asientos;
			ubicar(4, 7); cout << BG_GRISCLARO << JTAZUL << "2. Seleccionar Asientos" << BG_WHITE << BLACK;

			ubicar(x, y += 2); cout << "Cantidad de asientos: "; ingresarDato(numAsientos);

			//CALCULA LA CANTIDAD DE ASIENTOS LIBRES
			for (int i = 0; i < vAux->getVectorAsientos().size(); i++)
			{
				if (vAux->getVectorAsientos()[i]->getEstado() == 0)aux2++;
			};
			if (numAsientos > aux2 - 1) { ubicar(x, y += 2); cout << "Cantidad de asientos libres insuficientes"; (void)_getch(); limpiarDerecha(); return; } //REGRESA SI LA CANTIDAD DE ASIENTOS ES SUPERIOR
			ubicar(x, y += 2); cout << "Nota: Por cada asiento VIP se adicionan 50 USD a la tarifa";

			vAux->mostrarMAsientos(83, 17); cout << BG_WHITE;
			y += 2;

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

			int precio = calcularPrecioFinal();

			ubicar(4, 9); cout << BG_GRISCLARO << JTAZUL << "3. Resumen" << BG_WHITE << BLACK;

			ubicar(x, y += 2); cout << "Escogio " << cont << " VIP y " << numAsientos - cont << " Economico";
			ubicar(x, y += 1); cout << "Monto a pagar: " << precio;
			ubicar(x, y += 1); cout << "Tiene codigos de descuento y/n: "; cin >> opc;
			if (confirmar(opc)) {
				ubicar(x, y += 1); cout << "Codigo: "; cin >> texto;
				int desc = descuento->verificarCodigo(texto, x, y);

				if (desc != -1)
					auxDescuento = static_cast<float>(desc);
				else
					auxDescuento = 0;

				precio = static_cast<int>(calcularPrecioFinal() - calcularPrecioFinal() * (auxDescuento / 100.0));

				ubicar(x, y += 2); cout << "Nuevo monto a pagar: " << precio;
			}
			ubicar(x, y += 1); cout << "Confirmar la reserva: y/n: "; cin >> opc; if (!confirmar(opc)) { limpiarDerecha(); return; }

			Reserva a(vAux, asientos, pAux, precio);

			reservas.push(a);

			ubicar(x, y += 2); cout << "La reserva se realizo con exito."; (void)_getch(); limpiarDerecha();
		}
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

	void mostrarMisReservas(Pasajero* pasajero) {

		if (!sesion) {
			cout << BG_WHITE << RED;
			ubicar(32, 4); cout << "Debe iniciar sesion para visualizar sus reservas.";
			system("pause>0"); return;
		}

		ubicar(32, 4); cout << BG_WHITE << BLACK << "Reservas de " << pasajero->getNombres();
		if (reservas.estaVacia()) {
			cout << BG_WHITE << BLACK;
			ubicar(32, 4); cout << "No hay ninguna reserva";
			return;
		}

		vector<Reserva*> todos = obtenerMisReservas(reservas, pasajero);
		iterarPaginas(todos, true);

		for (Reserva* r : todos) {
			delete r;
		}
	}

	void mostrarTodasLasReservas() {
		if (reservas.estaVacia()) {
			cout << BG_WHITE << BLACK;
			ubicar(32, 4); cout << "No hay ninguna reserva";
			return;
		}

		vector<Reserva*> todos = obtenerTodasLasReservas(reservas);
		iterarPaginas(todos);

		for (Reserva* r : todos) {
			delete r;
		}
	}

	vector<Reserva*> obtenerTodasLasReservas(Pila<Reserva>& reservas) {
		vector<Reserva*> todas;
		Pila<Reserva> aux;

		while (!reservas.estaVacia()) {
			Reserva r = reservas.pop();
			Reserva* copia = new Reserva(r); 
			todas.push_back(copia);
			aux.push(r); // restauramos la pila
		}

		while (!aux.estaVacia()) {
			reservas.push(aux.pop());
		}

		return todas;
	}

	vector<Reserva*> obtenerMisReservas(Pila<Reserva>& reservas, Pasajero*pasajero) {
		vector<Reserva*> todas;
		Pila<Reserva> aux;

		while (!reservas.estaVacia()) {
			Reserva r = reservas.pop();
			Reserva* copia = new Reserva(r);
			if(copia->getPasajero() == pasajero)todas.push_back(copia);
			aux.push(r); // restauramos la pila
		}

		while (!aux.estaVacia()) {
			reservas.push(aux.pop());
		}

		return todas;
	}

	void iterarPaginas(vector<Reserva*>& reservas, bool rutas = false) {
		int totalPaginas = static_cast<int>((reservas.size() + 3) / 4);
		int paginaActual = 0;
		int tecla;

		do {
			mostrarPagina(reservas, paginaActual, rutas);
			tecla = _getch();

			if (tecla == 224) {
				int flecha = _getch();
				if (flecha == 77 && paginaActual < totalPaginas - 1) { //derecha
					paginaActual++;
				}
				else if (flecha == 75 && paginaActual > 0) { //izquierda
					paginaActual--;
				}
			}
		} while (tecla != 27); // ESC
	}

	void mostrarPagina(vector<Reserva*>& reservas, int pagina, bool rutas) {
		limpiarDerecha(); //limpia la pantalla de info
		int reservasPorPaginas = 4;
		int inicio = pagina * reservasPorPaginas;
		int fin = min(inicio + reservasPorPaginas, (int)reservas.size());

		int x1 = 32, x2 = 75;	
		int yInicio = 4;
		int espacioVertical = 13;

		for (int i = inicio; i < fin; ++i) {
			int localIndex = i - inicio; // de 0 a 3
			int fila = localIndex / 2;   // 0 o 1
			int columna = localIndex % 2; // 0 o 1

			int x = (columna == 0) ? x1 : x2;
			int y = yInicio + fila * espacioVertical;

			if(rutas){
				reservas[i]->mostrarinCompletos(x, y);
			}
			else
			reservas[i]->mostrarDatosCompletos(x, y);
		}

		ubicar(30, 1);
		cout << BG_JTAZUL << WHITE << "Pagina " << (pagina + 1) << " / " << ((reservas.size() + 3) / 4);
		if (pagina < 10) cout << " ";
		ubicar(30, 2);
		cout << "Usa Flechas izq y der para cambiar de pagina. ESC para salir.";
	}

	Pila<Reserva> getReservas() {
		return reservas;
	}

	void mostrarHashDescuentos() {
		descuento->mostrarTablaDebug(); 
	}
};

#endif // !_RESERVAS_
