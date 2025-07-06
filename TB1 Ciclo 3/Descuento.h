#pragma once
#include <iostream>
#include "HashTableA.h"
using namespace std; 

class CodigoDescuento {
private:
    string codigo;   
    int porcentaje;   
public: 
    CodigoDescuento(string c, int p) : codigo(c), porcentaje(p) {}

    // Mostrar
    void mostrar() {
        cout << codigo << " - " << porcentaje << "%" << endl;
    }

    string getCodigo() { return codigo; }
    int getPorcentaje() { return porcentaje; }

};

// Funciones para el hash table

auto getKeyCod = [](CodigoDescuento* cd) -> string {
    return cd->getCodigo();
    };

auto funcionHasheoCod = [](CodigoDescuento* cd) -> size_t {
    size_t hashVal = 0;
    for (char c : cd->getCodigo())
        hashVal = 37 * hashVal + c;
    return hashVal;
    };


class Descuento
{
private:
	HashTableA<CodigoDescuento*,string>* tablaCodigos; 

public:
	Descuento() {
        tablaCodigos = new HashTableA<CodigoDescuento*, string>(getKeyCod, funcionHasheoCod, 23); 

        //codigo fijo "ABCDEF" para probar - debug

        tablaCodigos->insert(new CodigoDescuento("ABCDEF", generarPorcentaje()));

        
        for (int i = 0; i < 10; i++) // generamos 10 codigos
        {
            string nuevo = generarCodigo();
            int porc = generarPorcentaje();

            tablaCodigos->insert(new CodigoDescuento(nuevo, porc));
        }
	}
	~Descuento() {}
    
    void mostrarTablaDebug() {
        ubicar(20, 5);
        tablaCodigos->mostrarTodo(); 
    }

    int verificarCodigo(string& codigo, int x, int y) {
        CodigoDescuento* encontrado = tablaCodigos->buscar(codigo); 

        if (encontrado) {
            ubicar(x += 16, y); cout << GREEN << "Codigo valido"; 
            
            ubicar(x -= 16, y += 1); cout << "Descuento: " << encontrado->getPorcentaje() << " % " << BLACK;
            
            return encontrado->getPorcentaje(); 
        }
        ubicar(x, y); cout << JTROJO << "Codigo no encontrado." << BLACK;
        return -1; 
    }

    string generarCodigo() {
        string codigo;  
        for (int i = 0; i < 6; i++) { // Codigos de 6 letras mayusculas
            char letra = 'A' + rand() % 26;
            codigo += letra;
        }
        return codigo;
    }

    int generarPorcentaje() {
        // Generar entre 5 y 35 de descuento 
        return 5 + rand() % 31;
    }
  

};

