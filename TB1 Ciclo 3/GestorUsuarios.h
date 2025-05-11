#ifndef _GESTORUSUARIOS_
#define _GESTORUSUARIOS_
#include "Gestortxt.h"
#include "Pasajero.h"
#include "ListaDoble.h"
class GestorUsuarios
{
private:
	Gestortxt<string> archivo;
	Lista<Pasajero*> pLista;
public:
	GestorUsuarios::GestorUsuarios() : archivo("Usuarios.txt") {
        leerUsuarios();
	}
	~GestorUsuarios(){}

    void leerUsuarios() {
        pLista = Lista<Pasajero*>();

        for (int i = 0; i < archivo.size(); i += 4)
        {
            if (archivo.size() >= i + 4) {
                pLista.insertarFinal(new Pasajero(archivo.getLine(i), archivo.getLine(i + 1), archivo.getLine(i + 2), archivo.getLine(i + 3)));
            }
        }
    }

    void agregarUsuario() {
        string nombres, apellidos, correo;
        string dniStr;

        do {
            cout << "Nombres: "; getline(cin, nombres);
            if (nombres.empty()) cout << "Nombres no puede estar vac�o.\n";
        } while (nombres.empty());

        do {
            cout << "Apellidos: "; getline(cin, apellidos);
            if (apellidos.empty()) cout << "Apellidos no puede estar vac�o.\n";
        } while (apellidos.empty());

        do {
            cout << "Correo: "; getline(cin, correo);
            if (correo.find('@') == string::npos)
                cout << "Correo inv�lido.\n";
        } while (correo.find('@') == string::npos);

        do {
            cout << "DNI: "; getline(cin, dniStr);
            if (dniStr.length() != 8 || dniStr.find_first_not_of("0123456789") != string::npos)
                cout << "DNI inv�lido.\n";
        } while (dniStr.length() != 8 || dniStr.find_first_not_of("0123456789") != string::npos);

        archivo.agregar(nombres);
        archivo.agregar(apellidos);
        archivo.agregar(correo);
        archivo.agregar(dniStr);

        leerUsuarios();
    }

    void mostrar(){
        pLista.mostrarPasajero();
    }
};

#endif // !_GESTORUSUARIOS_
