#ifndef __VUELO__
#define __VUELO__

#include <map>
#include <vector>
#include <istream>
#include <algorithm>
#include "Asiento.h"

using namespace std;

// --- Variables Universales ---

string paises[10] = { "Peru", "Chile", "Argentina", "Brasil", "Colombia", "Ecuador", "Mexico", "EE.UU", "Espana", "Italia" };

// --- Clase Vuelo --- 

class Vuelo {
private:
    string origen, destino;
    int diaIda, mesIda, diaVuelta, mesVuelta, codigoVuelo, precio;
    vector<Asiento*> asientos;

public:
    Vuelo() {}

    Vuelo(string origen, string destino, int diaIda, int mesIda, int diaVuelta, int mesVuelta, int codigoVuelo)
        : origen(origen), destino(destino), diaIda(diaIda), mesIda(mesIda), diaVuelta(diaVuelta), mesVuelta(mesVuelta), codigoVuelo(codigoVuelo) {

        //Para asignar 20 asientos por cada Vuelo
        for (int i = 0; i < 20; i++)
        {
            //Creamos un asiento
            char clasificacion = (rand() % 2 ? 'V' : 'E'); // Vip o Economico
            bool estado = rand() % 2; // 1 lleno, 0 vacio 
            int idAsiento = i + 101; // ids unicos del 101 al 120

            asientos.push_back(new Asiento(clasificacion, estado, idAsiento));
        }

        //Asignar precios aleatorios
        precio = (250 + rand() % (1000 + 1 - 250)) * 2; // pq es ida y vuelta
    }
    ~Vuelo() {}

    void mostrarVuelo() {
        cout << "Vuelo nro: " << codigoVuelo << " |  " << origen << " - " << destino << endl;
        cout << "Ida: " << diaIda << "/" << mesIda << "\nVuelta: " << diaVuelta << "/" << mesVuelta << 
            "\nPrecio en USD:" << precio << endl << endl;
    }

    //CON COORDENADAS
    void mostrarVuelo2(int x, int y) {
        cout << BG_WHITE << BLACK;
        ubicar(x, y); cout << "Vuelo nro: " << codigoVuelo << " |  " << origen << " - " << destino << "      ";
        ubicar(x, y += 1); cout << "Ida: " << diaIda << "  / " << mesIda << "  ";
        ubicar(x, y += 1); cout << "Vuelta: " << diaVuelta << "  / " << mesVuelta << "  ";
        ubicar(x, y += 1); cout << "Precio en USD:" << precio << "  ";
    }

    string getOrigen() { return origen; }
    string getDestino() { return destino; }
    int getDiaIda() { return diaIda; }
    int getMesIda() { return mesIda; }
    int getDiaVuelta() { return diaVuelta; }
    int getMesVuelta() { return mesVuelta; }
    int getCodigoVuelo() { return codigoVuelo; }
    int getPrecio() { return precio; }
    void setCodigoVuelo(int codigoVuelo) { this->codigoVuelo = codigoVuelo; }
    vector<Asiento*> getVectorAsientos() { return asientos; }

    int getIndicePaisOrigen() {
        for (int i = 0; i < 10; i++) {
            if (origen == paises[i]) {
                return i;
            }
        }
        return 1;
    }

    Asiento* getAsiento(int idAsiento) {
        for (int i = 0; i < asientos.size(); i++)
        {
            if (asientos[i]->getIdAsiento() == idAsiento) {
                return asientos[i];
            }
        }
        return nullptr;
    }

    void mostrarAsientos() {
        for (int i = 0; i < asientos.size(); i++)
        {
            asientos[i]->mostrarAsiento();

        }
    }

    void mostrarMAsientos(int x, int y) {
        for (int i = 0; i < 20; i+=4)
        {
            
            asientos[i]->mostrarColor(x,y);
            asientos[i+1]->mostrarColor(x+=6, y);
            asientos[i + 2]->mostrarColor(x += 8, y);
            asientos[i + 3]->mostrarColor(x += 6, y);
                
            x -= 20;
            y += 1;
        }
    }

    void mostrarAsientosDisponibles() {
        for (int i = 0; i < asientos.size(); i++)
        {
            asientos[i]->mostrarAsientoDisponible();

        }
    }
};

#endif // !__VUELO__