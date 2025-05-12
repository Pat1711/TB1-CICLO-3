#ifndef __COLA_H__
#define __COLA_H__

#include "Nodo.h"

template<class T>
class Cola {
private:
	Nodo<T>* inicio;
	Nodo<T>* fin;
public:
	Cola() {
		this->inicio = nullptr;
		this->fin = nullptr;
	}
	void enqueue(T v);
	T dequeue();
	bool esVacia();

};

template<class T>
bool Cola<T>::esVacia() {
	return (inicio == nullptr);
}

template<class T>
void Cola<T>::enqueue(T v) {
	Nodo<T>* nodo = new Nodo<T>(v, nullptr, nullptr);
	/*Nodo<T>* nodo = new Nodo<T>(v);*/
	if (esVacia()) {
		inicio = nodo;
		fin = inicio;
	}
	else {

		fin->siguiente = nodo;
		fin = nodo;
	}
	// 1 -> 2  -> (3) -> nullptr
}

template<class T>
T Cola<T>::dequeue() {
	T dato = inicio->dato;

	if (inicio == fin) {
		inicio = nullptr;
		fin = nullptr;
	}
	else {
		inicio = inicio->siguiente;
	}

	return dato;
}

#endif