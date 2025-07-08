#ifndef _GESTORCHECKIN_
#define _GESTORCHECKIN_

#include "CheckIn.h"
#include "Cola.h"

class GestorCheckin {
private:
    Cola<Reserva> checkinsExitosos;
    GestorUsuarios& gUsuarios;

public:
    GestorCheckin(GestorUsuarios& gestor) : gUsuarios(gestor) {}
    ~GestorCheckin() {}

    // --- Realiza un CheckIn --- //

    void realizarCheckIn(GestorReserva& gestorReserva) {
        CheckIn checkin;
        Reserva* reservaConfirmada = checkin.procesarCheckIn(gestorReserva);

        if (reservaConfirmada != nullptr) {
            checkinsExitosos.enqueue(*reservaConfirmada);
        }

        else {
            return;
        }
    }

    // --- Muestra todos los CheckIns Realizados --- //

    void mostrarCheckinsRealizados() {
        if (checkinsExitosos.esVacia()) {
            cout << "\nNo hay check-ins registrados.\n";
            return;
        }

        Cola<Reserva> aux;
        cout << "\n=== HISTORIAL DE CHECK-INS ===\n";
        while (!checkinsExitosos.esVacia()) {
            Reserva reserva = checkinsExitosos.dequeue();
            reserva.mostrarDatosCompletos(0, 0);
            aux.enqueue(reserva);
        }

        while (!aux.esVacia()) {
            checkinsExitosos.enqueue(aux.dequeue());
        }
    }

    // --- Muestra todos los CheckIns de un Pasajero --- //

    void mostrarCheckinsPorUsuario() {
        cout << BG_WHITE << BLACK;
        if (checkinsExitosos.esVacia()) {
            ubicar(31, 4); cout << "No hay check-ins registrados";
            return;
        }

        if (gUsuarios.getLista().esVacio()) {
            ubicar(31, 4); cout << "No hay usuarios registrados";
            return;
        }

        limpiarDerecha2();
        gUsuarios.mostrarTodosLosUsuarios();
        limpiarDerecha2();

        string dni; // continuacion waza
        cout << BG_WHITE << BLACK;
        ubicar(54, 27); cout << "Ingrese el DNI del pasajero: "; ingresarDato(dni);

        if (!gUsuarios.getLista().validarDNI(dni)) {
            ubicar(31, 11); cout << "No se encontró un pasajero con ese DNI";
            return;
        }

        /*Cola<Reserva> aux;
        bool hayCoincidencias = false;*/

        limpiarDerecha();

        //AQUI SE DEBE MOSTRAR LAS PAGINAS DE CHECKINS 

        cout << BG_WHITE << BLACK;
        /* ubicar(31, 4); cout << "=== CHECK-INS DEL USUARIO CON DNI: " << dni << " ===";*/
        /*while (!checkinsExitosos.esVacia()) {
            Reserva reserva = checkinsExitosos.dequeue();

            if (reserva.getPasajero()->getDni() == dni) {
                reserva.mostrarDatosCompletos(31, 5);
                hayCoincidencias = true;
            }
          
            aux.enqueue(reserva);
        }*/
        vector<Reserva> delUsuario = obtenerCheckinsDelPasajero(dni);

        if (delUsuario.empty()) {
            ubicar(31, 21); cout << "No se encontraron check-ins para el DNI proporcionado.";
            return;
        }

        bool visualizo = iterarTarjetasEmbarque(delUsuario);

        if (!visualizo) return;
        // end

        /*while (!aux.esVacia()) {
            checkinsExitosos.enqueue(aux.dequeue());
        }

        if (!hayCoincidencias) {
            ubicar(31, 21); cout << "No se encontraron check-ins para el DNI proporcionado.";
        }*/
    }

    //parte final

    vector<Reserva> obtenerCheckinsDelPasajero(const string& dni) {
        vector<Reserva> resultado;
        Cola<Reserva> aux;

        while (!checkinsExitosos.esVacia()) {
            Reserva reserva = checkinsExitosos.dequeue();

            if (reserva.getPasajero()->getDni() == dni) {
                resultado.push_back(reserva);
            }

            aux.enqueue(reserva); 
        }

        while (!aux.esVacia()) {
            checkinsExitosos.enqueue(aux.dequeue());
        }

        return resultado;
    }

    bool iterarTarjetasEmbarque(vector<Reserva>& reservas) {
        if (reservas.empty()) return false;

        int totalPaginas = static_cast<int>(reservas.size());
        int paginaActual = 0;
        int tecla;

        do {
            mostrarTarjeta(reservas[paginaActual], paginaActual, totalPaginas);
            tecla = _getch();

            if (tecla == 224) {
                int flecha = _getch();
                if (flecha == 77 && paginaActual < totalPaginas - 1) paginaActual++;     // derecha
                else if (flecha == 75 && paginaActual > 0) paginaActual--;              // izquierda
            }
        } while (tecla != 27); // ESC

        return true;
    }

    void mostrarTarjeta(Reserva& reserva, int pagina, int totalDePaginas) {
        limpiarDerecha(); 
        int x = 32, y = 4;

        ubicar(x, y);
        cout << BG_WHITE << BLACK << "=== TARJETA DE EMBARQUE ===";

        reserva.mostrarDatosCompletos(x, y + 2); 

        ubicar(30, 1);
        cout << BG_JTAZUL << WHITE << "Pagina " << (pagina + 1) << " / " << totalDePaginas;
        if (pagina < 10) cout << " ";
        ubicar(30, 2);
        cout << "Usa Flechas izq y der para cambiar de pagina. ESC para salir.";
    }
};

#endif 