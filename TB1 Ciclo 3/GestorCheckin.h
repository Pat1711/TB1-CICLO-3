#ifndef _GESTORCHECKIN_
#define _GESTORCHECKIN_

#include "CheckIn.h"
#include "Cola.h"

class GestorCheckin {
private:
    Cola<Reserva> checkinsExitosos;
    GestorUsuarios gUsuarios;

public:
    GestorCheckin() {}

    // --- Realiza un CheckIn --- //

    void realizarCheckIn(GestorReserva& gestorReserva) {
        CheckIn checkin;
        Reserva* reservaConfirmada = checkin.procesarCheckIn(gestorReserva);

        if (reservaConfirmada != nullptr) {
            checkinsExitosos.enqueue(*reservaConfirmada); 
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
            reserva.mostrarDatosCompletos();
            aux.enqueue(reserva);
        }

        while (!aux.esVacia()) {
            checkinsExitosos.enqueue(aux.dequeue());
        }
    }

    // --- Muestra todos los CheckIns de un Pasajero --- //
    //ayuda
    void mostrarCheckinsPorUsuario() {
        cout << "[DEBUG] Verificando si lista está vacía...\n";
        if (gUsuarios.getLista().esVacio()) {
            cout << "Lista vacía. No hay usuarios.\n";
            cin.get();
            return;
        }

        if (checkinsExitosos.esVacia()) {
            cout << "\nNo hay check-ins registrados.\n";
            return;
        }

        if (gUsuarios.getLista().esVacio()) {
            cout << "No hay usuarios registrados.\n";
            return;
        }

        cout << "\nSeleccione un usuario (DNI):\n";
        gUsuarios.getLista().mostrarPasajero();

        string dni;
        cout << "Ingrese el DNI del pasajero: ";
        cin >> dni;

        if (!gUsuarios.getLista().validarDNI(dni)) {
            cout << "No se encontró un pasajero con ese DNI.\n";
            return;
        }

        Cola<Reserva> aux;
        bool hayCoincidencias = false;

        cout << "\n=== CHECK-INS DEL USUARIO CON DNI: " << dni << " ===\n";
        while (!checkinsExitosos.esVacia()) {
            Reserva reserva = checkinsExitosos.dequeue();

            if (reserva.getPasajero()->getDni() == dni) {
                reserva.mostrarDatosCompletos();
                hayCoincidencias = true;
            }

            aux.enqueue(reserva); 
        }

        while (!aux.esVacia()) {
            checkinsExitosos.enqueue(aux.dequeue());
        }

        if (!hayCoincidencias) {
            cout << "No se encontraron check-ins para el DNI proporcionado.\n";
        }
    }
};

#endif