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

        ubicar(31, 4); cout << "Seleccione un usuario (DNI):";
        gUsuarios.getLista().mostrarPasajero(31,5);

        string dni;
        ubicar(31, 10); cout << "Ingrese el DNI del pasajero: "; ingresarDato(dni);

        if (!gUsuarios.getLista().validarDNI(dni)) {
            ubicar(31, 11); cout << "No se encontró un pasajero con ese DNI";
            return;
        }

        Cola<Reserva> aux;
        bool hayCoincidencias = false;

        defaultPanelDerecho();

        cout << BG_WHITE << BLACK;
        ubicar(31, 4); cout << "=== CHECK-INS DEL USUARIO CON DNI: " << dni << " ===";
        while (!checkinsExitosos.esVacia()) {
            Reserva reserva = checkinsExitosos.dequeue();

            if (reserva.getPasajero()->getDni() == dni) {
                reserva.mostrarDatosCompletos(31, 5);
                hayCoincidencias = true;
            }
          
            aux.enqueue(reserva);
        }

        while (!aux.esVacia()) {
            checkinsExitosos.enqueue(aux.dequeue());
        }

        if (!hayCoincidencias) {
            ubicar(31, 21); cout << "No se encontraron check-ins para el DNI proporcionado.";
        }
    }
};

#endif 