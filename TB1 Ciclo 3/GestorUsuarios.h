#ifndef _GESTORUSUARIOS_
#define _GESTORUSUARIOS_
#include "Gestortxt.h"
#include "Pasajero.h"
#include "ListaDoble.h"
#include "HashTableA.h"
#include "functional"

class GestorUsuarios
{
private:
    Gestortxt<string> archivo;
    Lista<Pasajero*> pLista;
    Pasajero* usuarioActual;

    HashTableA<Pasajero*>* hash;

public:
    GestorUsuarios() : archivo("Usuarios.txt") {
        auto clave = [](Pasajero* pasajero)->int {
            return stoi(pasajero->getDni());
            };

        auto funcionHasheo = [](Pasajero* pasajero)->int { //funcion de hasheo basada en nombre y dni
            size_t aux = 0;
            for (char c : pasajero->getNombres()) {
                aux += c * 19;
            }
            return stoi(pasajero->getDni())* 19 + aux;
            };

        hash = new HashTableA<Pasajero*>(clave,funcionHasheo);

        leerUsuarios();
    }
    ~GestorUsuarios() {}

    void leerUsuarios() {
        pLista = Lista<Pasajero*>();
        hash->vaciar();

        for (int i = 0; i < archivo.size(); i += 4)
        {
            if (archivo.size() >= i + 4) {
                pLista.insertarFinal(new Pasajero(archivo.getLine(i), archivo.getLine(i + 1), archivo.getLine(i + 2), archivo.getLine(i + 3)));
                hash->insert(getLista().getDato(pLista.longitud() - 1));
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

        hash->insert(nuevoPasajero);

        archivo.agregar(nombres);
        archivo.agregar(apellidos);
        archivo.agregar(correo);
        archivo.agregar(dniStr);

        ubicar(x, y++); cout << "Operación concluida correctamente";

        return nuevoPasajero;
    }

    void iniciarSesion() {
        limpiarDerecha();
        int x = 35; int y = 5;
        string correo, dni;
        ubicar(x, y); cout << BG_WHITE << BLACK << "Ingrese correo electronico: "; ingresarDato(correo);
        ubicar(x, y += 2); cout << "Ingrese dni: "; ingresarDato(dni);

        int key = stoi(dni);
        int pos = hash->obtenerPos(key); 

        if (pos == -1) {
            ubicar(x, y += 2); cout << JTROJO << "Usuario no encontrado." << BLACK; cin.ignore();
            return;
        }

        for (int i = 0; i < getLista().longitud(); ++i) {
            Pasajero* p = getLista().getDato(i);
            if (stoi(p->getDni()) == key && p->getCorreo() == correo) {
                usuarioActual = p;
                ubicar(x, y += 2); cout << GREEN << "Inicio de sesion exitoso" << BLACK; system("pause>0"); cin.ignore();
                sesion = true;
                return;
            }
        }

        ubicar(x, y++); cout << JTROJO << "Correo incorrecto o no coincide con el DNI." << BLACK; system("pause>0");
    }

    //
    void mostrarTodosLosUsuarios() {
        if (pLista.esVacio()) {
            cout << BG_WHITE << BLACK;
            ubicar(32, 4); cout << "No hay ninguna reserva";
            return;
        }

        vector<Pasajero*> todos = obtenerTodosLosPasajeros();
        iterarPaginas(todos);
    }

    vector<Pasajero*> obtenerTodosLosPasajeros() {
        return pLista.getTodos();
    }

    void iterarPaginas(vector<Pasajero*>& pasajeros) {
        int totalPaginas = static_cast<int>((pasajeros.size() + 7) / 8);
        int paginaActual = 0;
        int tecla;

        do {
            mostrarPagina(pasajeros, paginaActual);
            tecla = _getch();

            if (tecla == 224) {
                int flecha = _getch();
                if (flecha == 77 && paginaActual < totalPaginas - 1) { //derecha
                    paginaActual++;
                }
                else if (flecha == 75 && paginaActual > 0) { //izquierda
                    paginaActual--;
                }
            }
        } while (tecla != 27); // ESC
    }

    void mostrarPagina(vector<Pasajero*>& pasajeros, int pagina) {
        limpiarDerecha(); //limpia la pantalla de info
        int pasajerosPorPagina = 8;
        int inicio = pagina * pasajerosPorPagina;
        int fin = min(inicio + pasajerosPorPagina, (int)pasajeros.size());

        int x1 = 32, x2 = 75;        
        int yInicio = 4;
        int espacioVertical = 2;    

        for (int i = inicio; i < fin; ++i) {
            int localIndex = i - inicio; // 0 a 7
            int fila = localIndex / 2;   // 0 a 3
            int columna = localIndex % 2; // 0 o 1

            int x = (columna == 0) ? x1 : x2;
            int y = yInicio + fila * espacioVertical;

            cout << BG_WHITE << BLACK;
            pasajeros[i]->mostrar(x, y);
        }

        ubicar(30, 1);
        cout << BG_JTAZUL << WHITE << "Pagina " << (pagina + 1) << " / " << ((pasajeros.size() + 3) / 4);
        if (pagina < 10) cout << " ";
        ubicar(30, 2);
        cout << "Usa Flechas izq y der para cambiar de pagina. ESC para salir.";
    }

    //

    void cerrarSesion() {
        usuarioActual = nullptr;
        sesion = false;
    }
    void mostrar(int x, int y) {

        cout << BG_WHITE << BLACK;
        pLista.mostrarPasajero(x, y);
    }

    Lista<Pasajero*>& getLista() {
        return pLista;
    }

    Pasajero* getusuario() {
        return usuarioActual;
    }
};

#endif // !_GESTORUSUARIOS_