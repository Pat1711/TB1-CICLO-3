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
        int x = 35, y = 5;
        Console::CursorVisible = true;

        do {
            ubicar(x, y++); cout << BG_WHITE << BLACK << "Nombres: "; getline(cin, nombres);
            ubicar(x, y++); if (nombres.empty()) cout << JTROJO <<"Nombres no puede estar vacío." << BLACK;
        } while (nombres.empty());

        do {
            ubicar(x, y++); cout << "Apellidos: "; getline(cin, apellidos);
            ubicar(x, y++); if (apellidos.empty()) cout << JTROJO << "Apellidos no puede estar vacío." << BLACK;
        } while (apellidos.empty());

        do {
            ubicar(x, y++); cout << "Correo: "; getline(cin, correo);
            if (correo.find('@') == string::npos) {
                ubicar(x, y++); cout << JTROJO<< "Correo inválido." << BLACK;
            }
        } while (correo.find('@') == string::npos);

        do {
            ubicar(x, y++); cout << "DNI: "; getline(cin, dniStr);
            if (dniStr.length() != 8 || dniStr.find_first_not_of("0123456789") != string::npos) {
                ubicar(x, y++); cout << JTROJO << "DNI inválido." << BLACK;
            }
        } while (dniStr.length() != 8 || dniStr.find_first_not_of("0123456789") != string::npos);

        //ACA VALIDAREMOS QUE ESOS DATOS NO SEA REPETIDOS!!!
        if (pLista.test(nombres, apellidos, correo, dniStr)) {
            ubicar(x, y++); cout << JTROJO << "[x] No se pudo registrar al pasajero por datos duplicados." << BLACK;
            return nullptr;
        }
        Console::CursorVisible = false;

        Pasajero* nuevoPasajero = new Pasajero(nombres, apellidos, correo, dniStr);

        getLista().insertarFinal(nuevoPasajero);

        archivo.agregar(nombres);
        archivo.agregar(apellidos);
        archivo.agregar(correo);
        archivo.agregar(dniStr);

        ubicar(x, y++); cout << "Operación concluida correctamente";

        //EL leerUsuarios(); BORRABA TODOS LOS DATOS

        return nuevoPasajero;
    }

    void mostrar(int x, int y){

        cout << BG_WHITE << BLACK;
        pLista.mostrarPasajero(x, y);
    }

    Lista<Pasajero*>& getLista() {
        return pLista;
    }
};

#endif // !_GESTORUSUARIOS_
