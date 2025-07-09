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

    void realizarCheckIn(GestorReserva& gestorReserva, Pasajero* pasajero) {
        CheckIn checkin;
        Reserva* reservaConfirmada = checkin.procesarCheckIn(gestorReserva, pasajero);

        if (reservaConfirmada != nullptr) {
            checkinsExitosos.enqueue(*reservaConfirmada);
        }

        else {
            return;
        }
    }


    // --- Muestra todos los CheckIns de un Pasajero --- //

    void mostrarCheckinsPorUsuario(Pasajero* pasajero) {
        
        limpiarDerecha2();
        if (!sesion) {
            cout << BG_WHITE << RED;
            ubicar(32, 4); cout << "Debe iniciar sesion para visualizar sus Tarjetas de embarque.";
            system("pause>0"); return;
        }
        string dni = pasajero->getDni();

        limpiarDerecha();

        //AQUI SE DEBE MOSTRAR LAS PAGINAS DE CHECKINS 
        cout << BG_WHITE << BLACK;

        vector<Reserva> delUsuario = obtenerCheckinsDelPasajero(dni);

        if (delUsuario.empty()) {
            ubicar(31, 4); cout << "No se encontraron check-ins.";
            return;
        }

        bool visualizo = iterarTarjetasEmbarque(delUsuario);

        if (!visualizo) return;
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