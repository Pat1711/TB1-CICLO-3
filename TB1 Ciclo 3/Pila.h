#ifndef __PILA_H__
#define __PILA_H__
using namespace std;

template<class T>
class Pila {
private:
	Nodo<T>* tope;
public:
	Pila() { tope = nullptr; };
	void push(T v);
	T pop();
	bool estaVacia();
	T mostrarDato();
};

template<class T>
void Pila<T>::push(T v) {
	if (estaVacia()) {
		tope = new Nodo<T>(v, nullptr, nullptr);
	}
	else {
		tope = new Nodo<T>(v, nullptr, tope);
	}
}
template<class T>
T Pila<T>::pop() {
	if (estaVacia()) {
		throw "Error, pila vacia";
	}
	else {
		T elemento = (T)(tope->dato);
		tope = (Nodo<T>*) tope->siguiente;
		return elemento;
	}
}

template<class T>
T Pila<T>::mostrarDato() {
	if (estaVacia()) {
		throw "Error, pila vacia";
	}
	else {
		T elemento = (T)(tope->dato);
		return elemento;
	}
}

template<class T>
bool Pila<T>::estaVacia() {
	return (tope == nullptr);
}
#endif
