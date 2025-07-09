#ifndef __ARBOLBB_HPP__
#define __ARBOLBB_HPP__

#include <functional>
using namespace std;

template <class T>
class NodoAr {
public:
	T elemento;
	NodoAr* izq = nullptr;
	NodoAr* der = nullptr;
};

template <class T>
class ArbolBB {
	typedef function<int(T, T)> Comp;

	NodoAr<T>* raiz;
	void(*procesar)(T);
	Comp comparar;

private:
	bool _insertar(NodoAr<T>*& nodo, T e) {
		if (nodo == nullptr) {
			nodo = new NodoAr<T>();
			nodo->elemento = e;
			return true;
		}
		int r = comparar(nodo->elemento, e);
		if (r == 0) return false;
		else if (r < 0) return _insertar(nodo->der, e);
		else return _insertar(nodo->izq, e);
	}

	//funciones adicionales
	void _buscarRango(NodoAr<T>* nodo, int minPrecio, int maxPrecio, vector<T>& resultado) {
		if (nodo == nullptr) return;

		int precio = nodo->elemento->getPrecio();

		if (precio >= minPrecio)
			_buscarRango(nodo->izq, minPrecio, maxPrecio, resultado);

		if (precio >= minPrecio && precio <= maxPrecio)
			resultado.push_back(nodo->elemento);

		if (precio <= maxPrecio)
			_buscarRango(nodo->der, minPrecio, maxPrecio, resultado);
	}

public:
	ArbolBB(void(*procesar)(T), Comp comparar) {
		this->procesar = procesar;
		this->comparar = comparar;
		raiz = nullptr;
	}

	bool insertar(T e) { return _insertar(raiz, e); }

	void buscarRangoPrecios(int minPrecio, int maxPrecio, vector<T>& encontrados) {
		_buscarRango(raiz, minPrecio, maxPrecio, encontrados);
	}
};

#endif