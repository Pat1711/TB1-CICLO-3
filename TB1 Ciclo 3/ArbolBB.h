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
	bool _buscar(NodoAr<T>* nodo, T e) {
		if (nodo == nullptr) return false;
		int r = comparar(nodo->elemento, e);
		if (r == 0) return true;
		else if (r < 0) return _buscar(nodo->der, e);
		else return _buscar(nodo->izq, e);
	}

	NodoAr<T>* _obtener(NodoAr<T>* nodo, T e) {
		if (nodo == nullptr) return nullptr;
		int r = comparar(nodo->elemento, e);
		if (r == 0) return nodo;
		else if (r < 0) return _obtener(nodo->der, e);
		else return _obtener(nodo->izq, e);
	}

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

	void _enOrden(NodoAr<T>* nodo) {
		if (nodo == nullptr) return;
		_enOrden(nodo->izq);
		procesar(nodo->elemento);
		_enOrden(nodo->der);
	}

	void _preOrden(NodoAr<T>* nodo) {
		if (nodo == nullptr) return;
		procesar(nodo->elemento);
		_preOrden(nodo->izq);
		_preOrden(nodo->der);
	}

	void _postOrden(NodoAr<T>* nodo) {
		if (nodo == nullptr) return;
		_postOrden(nodo->izq);
		_postOrden(nodo->der);
		procesar(nodo->elemento);
	}

	int _cantidad(NodoAr<T>* nodo) {
		if (nodo == nullptr) return 0;
		return 1 + _cantidad(nodo->izq) + _cantidad(nodo->der);
	}

	int _altura(NodoAr<T>* nodo) {
		if (nodo == nullptr) return 0;
		int ai = 1 + _altura(nodo->izq);
		int ad = 1 + _altura(nodo->der);
		return ai > ad ? ai : ad;
	}

	T _minimo(NodoAr<T>* nodo) {
		if (nodo->izq == nullptr) return nodo->elemento;
		else return _minimo(nodo->izq);
	}

	T _maximo(NodoAr<T>* nodo) {
		if (nodo->der == nullptr) return nodo->elemento;
		else return _maximo(nodo->der);
	}

	bool _eliminar(NodoAr<T>*& nodo, T e) {
		if (nodo == nullptr) return false;

		int r = comparar(nodo->elemento, e);
		if (r < 0) return _eliminar(nodo->der, e);
		else if (r > 0) return _eliminar(nodo->izq, e);
		else {
			if (nodo->der == nullptr && nodo->izq == nullptr) {
				delete nodo;
				nodo = nullptr;
				return true;
			}
			else if (nodo->izq == nullptr) {
				NodoAr<T>* temp = nodo;
				nodo = nodo->der;
				delete temp;
				return true;
			}
			else if (nodo->der == nullptr) {
				NodoAr<T>* temp = nodo;
				nodo = nodo->izq;
				delete temp;
				return true;
			}
			else {
				NodoAr<T>* aux = nodo->der;
				while (aux->izq != nullptr) aux = aux->izq;
				nodo->elemento = aux->elemento;
				return _eliminar(nodo->der, aux->elemento);
			}
		}
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
	void enOrden() { _enOrden(raiz); }
	void preOrden() { _preOrden(raiz); }
	void postOrden() { _postOrden(raiz); }
	int cantidad() { return _cantidad(raiz); }
	int altura() { return _altura(raiz); }
	bool Buscar(T e) { return _buscar(raiz, e); }
	T Minimo() { return _minimo(raiz); }
	T Maximo() { return _maximo(raiz); }
	bool Eliminar(T e) { return _eliminar(raiz, e); }
	NodoAr<T>* getRaiz() {
		return raiz;
	}

	void buscarRangoPrecios(int minPrecio, int maxPrecio, vector<T>& encontrados) {
		_buscarRango(raiz, minPrecio, maxPrecio, encontrados);
	}
};

#endif