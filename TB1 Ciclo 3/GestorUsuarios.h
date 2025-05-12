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
	GestorUsuarios() : archivo("Usuarios.txt") {
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

    Pasajero* agregarUsuario() {
        string nombres, apellidos, correo;
        string dniStr;

        do {
            cout << "Nombres: "; getline(cin, nombres);
            if (nombres.empty()) cout << "Nombres no puede estar vacío.\n";
        } while (nombres.empty());

        do {
            cout << "Apellidos: "; getline(cin, apellidos);
            if (apellidos.empty()) cout << "Apellidos no puede estar vacío.\n";
        } while (apellidos.empty());

        do {
            cout << "Correo: "; getline(cin, correo);
            if (correo.find('@') == string::npos)
                cout << "Correo inválido.\n";
        } while (correo.find('@') == string::npos);

        do {
            cout << "DNI: "; getline(cin, dniStr);
            if (dniStr.length() != 8 || dniStr.find_first_not_of("0123456789") != string::npos)
                cout << "DNI inválido.\n";
        } while (dniStr.length() != 8 || dniStr.find_first_not_of("0123456789") != string::npos);

        //ACA VALIDAREMOS QUE ESOS DATOS NO SEA REPETIDOS!!!
        if (pLista.test(nombres, apellidos, correo, dniStr)) {
            cout << "[x] No se pudo registrar al pasajero por datos duplicados.\n";
            return nullptr;
        }

        Pasajero* nuevoPasajero = new Pasajero(nombres, apellidos, correo, dniStr);
        //el error esta aca (segun el guru) lo de abajo es una prueba para ver si lo soluciona pero no :v
        getLista().insertarFinal(nuevoPasajero);

        archivo.agregar(nombres);
        archivo.agregar(apellidos);
        archivo.agregar(correo);
        archivo.agregar(dniStr);

        leerUsuarios();

        return nuevoPasajero;
    }

    void mostrar(){
        pLista.mostrarPasajero();
    }

    Lista<Pasajero*> getLista() {
        return pLista;
    }
};

#endif // !_GESTORUSUARIOS_
