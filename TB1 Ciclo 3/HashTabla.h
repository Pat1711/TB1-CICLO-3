#ifndef HASHTABLA_HPP
#define HASHTABLA_HPP

#include <iostream>
#include "ListaDoble.h"
#include <functional>
using namespace std;

template <typename T>
class HashTabla {
private:
    static const int TABLE_SIZE = 23;
    Lista<T> tabla[TABLE_SIZE];
    int numElementos;
    function<int(T)> obtenerClave;

    int hash(int key) const {
        return key % TABLE_SIZE;
    }

    int longitudLista(int pos) const {
        Nodo<T>* actual = tabla[pos].getInicio();
        int contador = 0;
        while (actual != nullptr) {
            contador++;
            actual = actual->siguiente;
        }
        return contador;
    }

public:
    HashTabla(function<int(T)> obtenerClave) : numElementos(0), obtenerClave(obtenerClave) {}

    int size() const {
        return TABLE_SIZE;
    }

    int sizeActual() const {
        return numElementos;
    }

    void insertar(int key, T value) {
        int pos = hash(key);

        for (int i = 0; i < longitudLista(pos); i++) {
            if (obtenerClave(tabla[pos].getDato(i)) == key) {
                throw runtime_error("Clave duplicada.");
            }
        }

        tabla[pos].insertarFinal(value);
        numElementos++;
    }

    T obtener(int key) const {
        int pos = hash(key);
        for (int i = 0; i < longitudLista(pos); i++) {
            T elem = tabla[pos].getDato(i);
            if (obtenerClave(elem) == key)
                return elem;
        }
        throw runtime_error("Clave no encontrada");
    }

    int buscar(int key) const {
        int pos = hash(key);
        for (int i = 0; i < longitudLista(pos); i++) {
            if (obtenerClave(tabla[pos].getDato(i)) == key)
                return pos;
        }
        return -1;
    }

    void eliminar(int key) {
        int pos = hash(key);
        Lista<T>& lista = tabla[pos];
        Nodo<T>* nodo = lista.getInicio();
        int index = 0;

        while (nodo != nullptr) {
            if (obtenerClave(nodo->dato) == key) {
                lista.eliminaEn(index);
                numElementos--;
                return;
            }
            nodo = nodo->siguiente;
            index++;
        }

        throw runtime_error("Clave no encontrada para eliminar.");
    }

    void mostrar(function<void(T)> mostrarFn) const {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Tabla[" << i << "]: ";
            for (int j = 0; j < longitudLista(i); j++) {
                mostrarFn(tabla[i].getDato(j));
                cout << " -> ";
            }
            cout << "NULL\n";
        }
    }

    void vaciar() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            tabla[i] = Lista<T>();  // reinicia la lista
        }
        numElementos = 0;
    }
};

#endif
