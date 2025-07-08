#ifndef __HASHTABLA_HPP__
#define __HASHTABLA_HPP__

#include <vector>
#include <list>
#include <functional>
#include <iostream>

using namespace std;

template<typename T, typename Key = int, typename HashFunc = function<size_t(T)>>
class HashTableA {
private:
    vector<list<T>> theLists;         // tabla de listas - hashing abierto
    function<Key(T)> getKey;          // función para obtener la clave de un T
    HashFunc funcionHash;             // nuestra función hash 
    equal_to<Key> equals;             // comparación de claves 

public:
    HashTableA(function<Key(T)> getKeyFunc, HashFunc hashFunc, int size = 23)
        : getKey(getKeyFunc), funcionHash(hashFunc)
    {
        theLists.resize(size);
    }

    bool insert(T x) { 
        Key clave = getKey(x);
        size_t index = myhash(x);

        auto& whichList = theLists[index];

        // verificar si ya existe la clave
        for (auto& elem : whichList) {
            if (equals(getKey(elem), clave)) {
                return false; // hay duplicado
                throw runtime_error("Clave duplicada.");
            }
        }

        whichList.push_back(x);
        return true;
    }
       
    int obtenerPos(Key& key) const {
        for (int i = 0; i < theLists.size(); i++) {
            for (auto& elem : theLists[i]) {
                if (getKey(elem) == key) { 
                    return i;
                }
            }
        }
        return -1; 
    }

    T buscar(Key& claveBuscada) {
        for (int i = 0; i < theLists.size(); i++) {
            for (auto& elem : theLists[i]) {
                if (getKey(elem) == claveBuscada) {
                    return elem;
                }
            }
        }
        return nullptr; 
    }

    void mostrarTodo(int x, int y) {
        int pos = 0;
        for (auto& lista : theLists) {
            // Mueve el cursor a la posición x, y
            ubicar(x, y++);
            cout << BG_WHITE <<BLACK << "Cod[" << pos << "]: ";

            for (auto& elem : lista) {
                cout << getKey(elem) << " ";
            }
            pos++;
        }
    }

    void vaciar() {
        for (auto& lista : theLists) {
            lista.clear(); // borra todos los elementos de cada lista
        }
    }

private:
    size_t myhash(const T& x) const {
        return funcionHash(x) % theLists.size();
        //return 10;
    }

};

#endif