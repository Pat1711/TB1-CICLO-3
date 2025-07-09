#ifndef __LISTA_DOBLE__
#define __LISTA_DOBLE__

#include <iostream>
#include "Nodo.h"
#include "Vuelo.h"
#include "Pasajero.h"
//vuelos y pasajeros

using namespace std;

template<class T>
class Lista {
private:
	Nodo<T>* inicio;

public:
	Lista() { inicio = nullptr; }
	~Lista();
	void insertarFinal(T v);
	bool esVacio();
	void mostrarPasajero(int x, int y);
	T getDato(int index) const;

	bool test(string nombres, string apellidos, string correo, string dni);

	int longitud() {
		Nodo<T>* nodo = inicio;
		int count = 0;
		while (nodo != nullptr) {
			count++;
			nodo = nodo->siguiente;
		}
		return count;
	}

};

// ---
template<class T>
Lista<T>::~Lista() {
	Nodo<T>* temp;
	while (!esVacio()) {
		temp = inicio;
		inicio = inicio->siguiente;
		delete temp;
		temp = nullptr;
	}
	inicio = nullptr;
}

// ---
template<class T>
void Lista<T>::insertarFinal(T v) {
	Nodo<T>* nodo = new Nodo<T>(v, nullptr, nullptr);

	if (esVacio()) inicio = nodo;
	else {
		Nodo<T>* aux = inicio;

		while (aux->siguiente != nullptr) {
			aux = aux->siguiente;
		}

		aux->siguiente = nodo;
	}
}

// ---
template<class T>
bool Lista<T>::esVacio() {
	if (inicio == nullptr) return true;
	else return false;
}

// ---
template<class T>
void Lista<T>::mostrarPasajero(int x, int y) {
	Nodo<T>* nodo = inicio; //Nodo<tipo T> apunta (*) hacua 'nodo'

	int i = 1;
	
	while (nodo != nullptr) {
		/*Pasajero* psj = (Pasajero*)(nodo->dato);*/ //Pasajero apunta a psj con valor Pasajero que apunta al dato del nodo
		Pasajero* psj = static_cast<Pasajero*>(nodo->dato); 
		ubicar(x, y++); cout << "# " << i++ << ". ---";
		psj->mostrar(x, y++);
		ubicar(x, y+=3); cout << "->";

		nodo = nodo->siguiente;
	}
	ubicar(x, y++);
}

// ---


// ---
template<class T>
bool Lista<T>::test(string nombres, string apellidos, string correo, string dni) {
	Nodo<T>* nodo = inicio;

	while (nodo != nullptr) {
		Pasajero* psj = static_cast<Pasajero*>(nodo->dato);

		if (psj->getDni() == dni) {
			cout << "Ya existe un pasajero con ese DNI.\n";
			return true;
		}
		if (psj->getCorreo() == correo) {
			cout << "Ya existe un pasajero con ese correo.\n";
			return true;
		}
		if (psj->getNombres() == nombres && psj->getApellidos() == apellidos) {
			cout << "Ya existe un pasajero con ese nombre y apellido.\n";
			return true;
		}
		nodo = nodo->siguiente;
	}
	return false;
}

template<class T>
T Lista<T>::getDato(int index) const{
	Nodo<T>* nodo = inicio;
	int contador = 0;

	while (nodo != nullptr) {
		if (contador == index) {
			return nodo->dato;
		}
		nodo = nodo->siguiente;
		contador++;
	}

	cout << "Fuera de rango"; system("pause>0");
	return nullptr;
}


#endif // !__LISTA_DOBLE__