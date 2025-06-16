#ifndef __SISTEMA__
#define __SISTEMA__

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "Color.h"

#define ANCHO 120
#define ALTO 30
using namespace std;
using namespace System;

bool debug = true; //idea para mostrar/ocultar opciones -> mas fidelidad a como se veria si fueras usuario

// --- Menu Principal --- ///
void ajustarConsola() {
	Console::SetWindowSize(ANCHO, ALTO);
}
void ubicar(int x, int y) {
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void pintar(int x, int y, int ancho, int alto) {
	ubicar(x, y);
	for (int i = 0; i < alto; i++)
	{
		for (int j = 0; j < ancho; j++)
		{
			cout << " ";
		}
		y++;
		ubicar(x, y);
	}
	ubicar(0, 0);
}
void portada() {
	cout << BG_JTAZUL;pintar(0,1, ANCHO, ALTO-2);
	cout << BG_WHITE; pintar(0, 14, ANCHO, 8);

	cout << WHITE << BG_JTAZUL;
	
	ubicar(1, 5);
	cout << " \t ____  _                           _     _                      _      _    _____                      _ " << endl;
	cout << " \t|  _ \\(_)                         (_)   | |                    | |    | |  / ____|                    | | " << endl;
	cout << " \t| |_) |_  ___ _ ____   _____ _ __  _  __| | ___     __ _       | | ___| |_| (___  _ __ ___   __ _ _ __| |_ " << endl;
	cout << " \t|  _ <| |/ _ \\ '_ \\ \\ / / _ \\ '_ \\| |/ _` |/ _ \\   / _` |  _   | |/ _ \\ __|\\___ \\| '_ ` _ \\ / _` | '__| __|" << endl;
	cout << " \t| |_) | |  __/ | | \\ V /  __/ | | | | (_| | (_) | | (_| | | |__| |  __/ |_ ____) | | | | | | (_| | |  | |_ " << endl;
	cout << " \t|____/|_|\\___|_| |_|\\_/ \\___|_| |_|_|\\__,_|\\___/   \\__,_|  \\____/ \\___|\\__|_____/|_| |_| |_|\\__,_|_|   \\__|" << endl;

	
	ubicar(1, 15);
	cout << JTROJO << BG_WHITE;

	cout << "\t\t\t\t   -.                 `|." << endl;
	cout << "\t\t\t\t   |:\\-,              .| \\." << endl;
	cout << "\t\t\t\t   |: `.------------------------------------." << endl;
	cout << "\t\t\t\t   / /   o o o o o o o o o o o o o.-.o o   (_`. " << endl;
	cout << "\t\t\t\t  /_ \\_              .     .=     |'|         `) " << endl;
	cout << "\t\t\t\t       ``-----------//----/------------------'' " << endl;

	cout << RESET;
}

void default() {
	cout << BG_WHITE; pintar(0, 1, ANCHO, ALTO - 2);
	cout << BG_GRISCLARO; pintar(0, 4, 30, ALTO - 5);
	cout << BG_JTAZUL; pintar(0, 1, ANCHO, 3);
	cout << RESET;
}

void defaultPanelDerecho() {
	cout << BG_WHITE; pintar(30, 4, 89, 25);
}

void imprimirDibujo(string dibujo[], size_t filas, int x, int y) {
	cout << JTROJO << BG_WHITE;
	for (int i = 0; i < filas; i++) {
		ubicar(x, y + i);
		cout << dibujo[i];
	}
	cout << RESET;
}

//TODAS LAS OPCIONES BRO
string opcPrincipal[5] = {  "Buscar vuelos", "Menu de Usuario","Reservar un vuelo","Check-In", "Salir" };
string opcUsuario[3] = { "Registrar Usuario", "Registro de Usuarios", "Salir" };
string opcVuelos[6] = {"Ver todos", "Buscar por mes", "Buscar por pais", "Buscar por fecha", "Buscar especifico", "Salir"};
string opcCheckin[4] = { "Tarjetas de embarque", "Reservas", "Check in", "Salir"};
string opcOrdenar[4] = {"Por precio", "Por país de origen", "Por código", "Salir"};


void seleccionarOpc(int&opcion, string opciones[], int n) {
	char tecla;
	int x = 4, y = 5;
	
	do {
		for (int i = 0; i < n; i++) {
			if (i == opcion) {
				cout << BG_GRISCLARO << JTAZUL;
				ubicar(x, y + 2*i); cout << " --> " << opciones[i];
			}
			else {
				cout << BG_GRISCLARO << BLACK;
				ubicar(x, y + 2 * i); cout << opciones[i] << "      ";
			}
			
		}

		tecla = _getch();

		if (tecla == 72) { // Flecha arriba
			opcion--;
			if (opcion < 0) opcion = 0;
		}
		else if (tecla == 80) { // Flecha abajo
			opcion++;
			if (opcion > n-1) opcion = n-1;
		}

	} while (tecla != 13); //tecla enter

	cout << RESET;
}

void ingresarDatos(int&a) {
	Console::CursorVisible = true;
	cin >> a;
	Console::CursorVisible = false;
}

void menuSpawn(string titulo) {
	default();
	ubicar(4, 2); cout << BG_JTAZUL << titulo;
	cout << RESET;
}
void barraSpawn(string titulo) {
	ubicar(4, 2); cout << BG_JTAZUL << titulo;
	cout << RESET;
}
void menuPrincipal() {
	default();

	ubicar(4, 2); cout << BG_JTAZUL << "JetSMART";

	cout << RESET;
}

//Dejo esto porsiaca
// --- Menu Usuario --- ///

void menuUsuario() {
	cout << "=====| Menu de Usuario |=====\n";
	cout << "1. Registrar nuevo usuario\n";
	if (debug) cout << "2. Registro de usuarios\n";
	cout << "3. Salir\n";
}

void tituloUsuario() {
	cout << "=====| Menu de Usuario |=====\n";
}

// --- Menu Vuelos --- ///

void menuVuelos() {
	cout << "=====|  Menu de Vuelos  |=====\n";
	cout << "1. Ver todos los vuelos\n";
	cout << "2. Buscar vuelos por mes\n";
	cout << "3. Buscar vuelos por pais\n";
	cout << "4. Buscar vuelos por Fecha Especifica\n";
	cout << "5. Buscar vuelos por Origen, Destino y Fecha de Ida\n";
	cout << "6. Salir\n";
}

void subMenuTodosLosVuelos() {
	cout << "=====|  Como desea ordenar todos los vuelos  |=====\n";
	cout << "1. Por precio\n";
	cout << "2. Por pais de Origen\n";
	cout << "3. Por codigo de vuelo\n";
	cout << "4. Salir\n";
}

void tituloVuelo() {
	cout << "=====|  Menu de Vuelos  |=====\n";
}

void selecionMesVuelo() {
	cout << "Listado de Meses\n";
	cout << "1. Enero\t 2. Febrero\t 3. Marzo\n";
	cout << "4. Abril\t 5. Mayo\t 6. Junio\n";
	cout << "7. Julio\t 8. Agosto\t 9. Septiembre\n";
	cout << "10. Octubre\t 11. Noviembre\t 12. Diciembre\n";
}

void seleccionPais() {
	cout << "Listado de paises\n";
	cout << "1. Peru\t\t 2. Chile\t 3. Argentina\n";
	cout << "4. Brasil\t 5. Colombia\t 6. Ecuador\n";
	cout << "7. Mexico\t 8. EE.UU\t 9. Espania\n";
	cout << "10. Italia\n";
}

// --- Menu Checkin --- ///

void menuCheckin() {
	cout << "=====| Menu de Check in |=====\n";
	cout << "1. Ver tarjetas de embarque\n";
	cout << "2. Ver reservas\n";
	cout << "3. Check in\n";
	cout << "4. Salir\n";
}

#endif // !__SISTEMA__
