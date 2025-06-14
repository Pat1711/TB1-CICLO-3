#pragma once
#include "Sistema.h"
#include "ListaDoble.h"
#include "GestorVuelo.h"
#include "GestorReserva.h"
#include "GestorUsuarios.h"
#include "GestorCheckin.h"
using namespace std;

//Funciones auxiliares

//Lambdas para validar lo valores
auto validarDiaMes = [](int dia, int mes) {
    return dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12;
    };
auto validarDestino = [](int origen, int destino) {
    return origen >= 1 && origen <= 10 && destino >= 1 && destino <= 10;
    }; 
auto menu = [](void menu(), int&opcion) {
    system("cls");
    menu();
    cin >> opcion;
    cin.ignore();
    };
auto mensajeError = []() {
    cout << "Opcion no valida\n"; system("pause");
    };
auto mostrarSeccion = [](void titulo()) {
    system("cls");
    titulo();
    };
auto enRango = [](int valor, int min, int max) {
    return valor >= min && valor <= max;
    };

class GestorSistema {
private:
    GestorUsuarios gUsuario;
    GestorVuelo gVuelos;
    GestorReserva gReservas;
    GestorCheckin gCheckIn;
    CheckIn checkIn;

public:
    GestorSistema() : gReservas(gVuelos, gUsuario), gCheckIn(gUsuario) {
        gUsuario.leerUsuarios();
        gVuelos.generarVuelosAutomaticos();
        
    }

    void ejecutar() {
        int opcion = 0;
        string destino, origen;

        do {
            menu(menuPrincipal, opcion);

            switch (opcion) {
            case 1:
                menuGestionUsuarios();break;
            case 2:
                menuGestionVuelos();break;
            case 3:
                menuGestionCheckin(); break;
            case 4:
                cout << "Gracias por usar el sistema\n"; system("pause"); break;
            default:
                mensajeError(); break;
            }
        } while (opcion != 4);
    }

    void menuGestionUsuarios() {
        int auxUser = 0;
        do {
            menu(menuUsuario, auxUser);
            mostrarSeccion(tituloUsuario);

            switch (auxUser) {
            case 1:
                gUsuario.agregarUsuario();
                cout << "Operación concluida correctamente\n";
                system("pause"); break;
            case 2:
                gUsuario.mostrar();
                system("pause"); break;
            case 3: break;
            default:
                mensajeError(); break;
            }
        } while (auxUser != 3);
    }

    void menuGestionVuelos() {
        int auxVuelo;
        do {
            menu(menuVuelos, auxVuelo);

            switch (auxVuelo) {
            case 1: submenuMostrarVuelos(); break;
            case 2: mostrarVuelosPorMes(); break;
            case 3: mostrarVuelosPorPaises(); break;
            case 4: mostrarVuelosEnFecha(); break;
            case 5: mostrarVuelosEspecificos(); break;
            case 6: break;
            default: mensajeError(); break;
            }
        } while (auxVuelo != 6);
    }

    void submenuMostrarVuelos() {
        int auxSubMenu;
        do {
            menu(subMenuTodosLosVuelos, auxSubMenu);

            switch (auxSubMenu) {
            case 1:
                system("cls"); cout << "=== Ordenamiento por Precio ===\n";
                gVuelos.ordenarTodosLosVuelosPorPrecio();
                gReservas.reservar();
                system("pause"); break;
            case 2:
                system("cls"); cout << "=== Ordenamiento por Pais de Origen ===\n";
                gVuelos.ordenarTodosLosVuelosPorPais();
                gReservas.reservar();
                system("pause"); break;
            case 3:
                system("cls"); cout << "=== Ordenamiento por Id Vuelo ===\n";
                gVuelos.ordenarTodosLosVuelosPorId();
                gReservas.reservar();
                system("pause"); break;
            case 4: break;
            default: mensajeError(); break;
            }
        } while (auxSubMenu != 4);
    }

    void mostrarVuelosPorMes() {
        int auxValor;
        do {
            mostrarSeccion(tituloVuelo);
            selecionMesVuelo();
            cout << "Ingrese el mes: ";
            cin >> auxValor;
            cin.ignore();
            if (!enRango(auxValor, 1, 12)) mensajeError();
        } while (!enRango(auxValor, 1, 12));

        mostrarSeccion(tituloVuelo);
        gVuelos.mostrarVuelosPorMes(auxValor);
        if (gVuelos.isVuelosEncontrados()) {
            cout << "\n";
            gReservas.reservar();
        }
        system("pause");
    }

    void mostrarVuelosPorPaises() {
        int auxOrigen, auxDestino;
        do {
            mostrarSeccion(tituloVuelo);
            seleccionPais();
            cout << "Origen: "; cin >> auxOrigen;
            cout << "Destino: "; cin >> auxDestino;
            if (!validarDestino(auxOrigen, auxDestino)) {
                mensajeError(); break;
            }
        } while (!validarDestino(auxOrigen, auxDestino));

        string origen = paises[auxOrigen - 1];
        string destino = paises[auxDestino - 1];

        gVuelos.mostrarVuelosPorPaises(origen, destino);
        if (gVuelos.isVuelosEncontrados()) {
            cout << "\n";
            gReservas.reservar();
        }
        system("pause");
    }

    void mostrarVuelosEnFecha() {
        int auxDia, auxMes;
        cout << "=====|  Vuelos en Fecha  |=====\n";
        do {
            cout << "\nDia de Ida: "; cin >> auxDia;
            selecionMesVuelo();
            cout << "\nMes de Ida: "; cin >> auxMes;
            if (!validarDiaMes(auxDia, auxMes)) {
                mensajeError(); break;
            }
        } while (!validarDiaMes(auxDia, auxMes));

        gVuelos.mostrarVuelosEnFecha(auxMes, auxDia);
        if (gVuelos.isVuelosEncontrados()) {
            cout << "\n";
            gReservas.reservar();
        }
        system("pause");
    }

    void mostrarVuelosEspecificos() {
        int auxOrigen, auxDestino, auxDiaIda, auxMesIda;
        do {
            mostrarSeccion(tituloVuelo);
            seleccionPais();
            cout << "Origen: "; cin >> auxOrigen;
            cout << "Destino: "; cin >> auxDestino;
            if (!validarDestino(auxOrigen, auxDestino)) {
                mensajeError(); break;
            }
        } while (!validarDestino(auxOrigen, auxDestino));

        string origen = paises[auxOrigen - 1];
        string destino = paises[auxDestino - 1];

        do {
            cout << "\nDia de Ida: "; cin >> auxDiaIda;
            selecionMesVuelo();
            cout << "\nMes de Ida: "; cin >> auxMesIda;
            if (!validarDiaMes(auxDiaIda, auxMesIda)) { 
                mensajeError(); break;
            }
        } while (!validarDiaMes(auxDiaIda, auxMesIda));

        gVuelos.mostrarVuelosDatosIda(origen, destino, auxMesIda, auxDiaIda);
        if (gVuelos.isVuelosEncontrados()) {
            cout << "\n";
            gReservas.reservar();
        }
        system("pause");
    }

    void menuGestionCheckin() {
        int opc;
        do
        {
            menu(menuCheckin, opc);
            switch (opc)
            {
            case 1: //tarjetas embarque
                gCheckIn.mostrarCheckinsPorUsuario();
                system("pause"); break;
            case 2: //reservas
                gReservas.mostrarReservas();
                system("pause"); break;
            case 3: //chekcin
                gCheckIn.realizarCheckIn(gReservas);
                system("pause"); break;
            case 4:
                break;
            default:
                mensajeError(); break;
            }
        } while (opc != 4);
    }
};

