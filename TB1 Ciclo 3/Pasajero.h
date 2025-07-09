#ifndef __PASAJERO__
#define __PASAJERO__

#include <iostream>
#include <string>	
#include <sstream>

using namespace std;

// --- Clase Pasajero --- 

class Pasajero {
private:
    string nombres;
    string apellidos;
    string correo;
    string dni;
public:
    Pasajero(){}
    Pasajero(string nombres, string apellidos, string correo, string dni)
        : nombres(nombres), apellidos(apellidos), correo(correo), dni(dni) {
    }
    ~Pasajero() {}

    string getNombres() { return nombres; }
    string getApellidos() { return apellidos; }
    string getCorreo() { return correo; }
    string getDni() { return dni; }

    void mostrar(int x, int y) {
        ubicar(x, y++); cout << "Nombres: " << nombres;
        ubicar(x, y++); cout << "Apellidos: " << apellidos;
        ubicar(x, y++); cout << "Correo: " << correo;
        ubicar(x, y++); cout << "DNI: " << dni;
    }
};

#endif // !__PASAJERO__