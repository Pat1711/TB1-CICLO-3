#ifndef __ARBOLAVL_HPP__
#define __ARBOLAVL_HPP__

template<class T>
class NodoAv {
public:
	T elemento;
	NodoAv* izq;
	NodoAv* der;
	int altura;

	NodoAv() {
		izq = nullptr;
		der = nullptr;
		altura = 0;
	}
};

template<class T>
class ArbolAVL {
private:
	typedef function<int(T, T)> Comp;

	NodoAv<T>* raiz;
	void(*procesar)(T); //puntero a función
	Comp comparar;

	//Operaciones privadas
	int _altura(NodoAv<T>* nodo) {
		if (nodo == nullptr) return 0;
		return nodo->altura;
	}

	void _rotarDerecha(NodoAv<T>*& nodo) {
		NodoAv<T>* p = nodo->izq;
		nodo->izq = p->der;
		p->der = nodo;
		//Actualizamos la altura

		nodo = p;
	}

	void _rotarIzquierda(NodoAv<T>*& nodo) {
		NodoAv<T>* p = nodo->der;
		nodo->der = p->izq;
		p->izq = nodo;
		//Actualizamos la altura

		nodo = p;
	}
	void _balanceo(NodoAv<T>*& nodo) {
		int hizq = _altura(nodo->izq);
		int hder = _altura(nodo->der);
		int fb = hder - hizq;

		if (fb > 1) { //rotar a la izq
			int hhizq = _altura(nodo->der->izq);
			int hhder = _altura(nodo->der->der);
			if (hhizq > hhder) { //verificar si aplica doble rotación
				_rotarDerecha(nodo->der);
			}
			_rotarIzquierda(nodo);
		}
		if (fb < -1) { //rotar a la der
			int hhizq = _altura(nodo->izq->izq);
			int hhder = _altura(nodo->izq->der);
			if (hhizq < hhder) {//verificar si aplica doble rotación 
				_rotarIzquierda(nodo->izq);
			}
			_rotarDerecha(nodo);
		}
		//Actualizar la altura del nodo raiz
		hizq = _altura(nodo->izq);
		hder = _altura(nodo->der);
		nodo->altura = 1 + ((hizq > hder) ? hizq : hder);
	}

	bool _insertar(NodoAv<T>*& nodo, T e) {

		if (nodo == nullptr) {
			//Nuevo elemento
			nodo = new NodoAv<T>();
			nodo->elemento = e;
			return true;
		}
		int cmp = comparar(e, nodo->elemento);
		if (cmp == 0) return false;
		else if (cmp < 0) _insertar(nodo->izq, e);
		else _insertar(nodo->der, e);
		_balanceo(nodo);
		return true;
	}

	void _inOrden(NodoAv<T>* nodo) {
		if (nodo == nullptr) return;
		_inOrden(nodo->izq);
		procesar(nodo->elemento);
		_inOrden(nodo->der);
	}

	void _inOrdenH(NodoAv<T>* nodo) {
		if (nodo == nullptr) return;
		_inOrdenH(nodo->izq);
		procesar(nodo->altura);
		_inOrdenH(nodo->der);
	}

	//funciones adicionales
	void _buscarEspecifico(NodoAv<T>* nodo, T clave, vector<T>& encontrados) {
		if (nodo == nullptr) return;

		int cmp = comparar(clave, nodo->elemento);

		if (cmp == 0) {
			encontrados.push_back(nodo->elemento);
			_buscarEspecifico(nodo->izq, clave, encontrados);
			_buscarEspecifico(nodo->der, clave, encontrados);
			return;
		}

		if (cmp <= 0) _buscarEspecifico(nodo->izq, clave, encontrados);
		if (cmp >= 0) _buscarEspecifico(nodo->der, clave, encontrados);
	}

public:
	ArbolAVL(void(*nuevaFuncion)(T), Comp comparar) {
		this->procesar = nuevaFuncion;
		this->comparar = comparar;
		this->raiz = nullptr;
	}

	bool Insertar(T e) {
		return _insertar(raiz, e);
	}
	void inOrden() {
		_inOrden(raiz);
	}
	void inOrdenH() {
		_inOrdenH(raiz);
	}

	NodoAv<T>* getRaiz() {
		return raiz;
	}

	void buscarEspecifico(T clave, vector<T>& encontrados) {
		_buscarEspecifico(raiz, clave, encontrados);
	}


};
#endif // !__ARBOLAVL_HPP__
