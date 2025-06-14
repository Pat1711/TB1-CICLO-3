#pragma once
#include "Sistema.h"
#include "ListaDoble.h"
#include "GestorVuelo.h"
#include "GestorReserva.h"
#include "GestorUsuarios.h"
#include "GestorCheckin.h"
using namespace std;

//Funciones auxiliares

//Lambda para validar los valores que se ingresan en dia y mes
auto validarDiaMes = [](int dia, int mes) {
    return dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12;
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
            system("cls");
            menuPrincipal();
            cin >> opcion;
            cin.ignore();

            switch (opcion) {
            case 1:
                menuGestionUsuarios();
                break;
            case 2:
                menuGestionVuelos();
                break;
            case 3:
                menuGestionCheckin();
                break;
            case 4:
                cout << "Gracias por usar el sistema\n"; system("pause"); break;
            default:
                cout << "Opci?n inv?lida\n"; system("pause"); break;
            }
        } while (opcion != 4);
    }

    void menuGestionUsuarios() {
        int auxUser;
        do {
            system("cls");
            menuUsuario();
            cin >> auxUser;
            cin.ignore();

            switch (auxUser) {
            case 1:
                system("cls"); tituloUsuario();
                gUsuario.agregarUsuario();
                cout << "Operaci?n concluida correctamente\n";
                system("pause"); break;
            case 2:
                system("cls"); tituloUsuario();
                gUsuario.mostrar();
                system("pause"); break;
            case 3: break;
            default:
                cout << "Opcion no valida\n"; system("pause"); break;
            }
        } while (auxUser != 3);
    }

    void menuGestionVuelos() {
        int auxVuelo;
        do {
            system("cls");
            menuVuelos();
            cin >> auxVuelo;
            cin.ignore();

            switch (auxVuelo) {
            case 1: submenuMostrarVuelos(); break;
            case 2: mostrarVuelosPorMes(); break;
            case 3: mostrarVuelosPorPaises(); break;
            case 4: mostrarVuelosEnFecha(); break;
            case 5: mostrarVuelosEspecificos(); break;
            case 6: break;
            default: cout << "Opci?n no v?lida\n"; system("pause"); break;
            }
        } while (auxVuelo != 6);
    }

    void submenuMostrarVuelos() {
        int auxSubMenu;
        do {
            system("cls");
            subMenuTodosLosVuelos();
            cin >> auxSubMenu;
            cin.ignore();

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
            default: cout << "Opcion no valida\n"; system("pause"); break;
            }
        } while (auxSubMenu != 4);
    }

    void mostrarVuelosPorMes() {
        int auxValor;
        do {
            system("cls"); tituloVuelo();
            selecionMesVuelo();
            cout << "Ingrese el mes: ";
            cin >> auxValor;
            cin.ignore();
            if (auxValor < 0 || auxValor > 12) {
                cout << "Opcion no valida\n"; system("pause");
            }
        } while (auxValor < 0 || auxValor > 12);

        system("cls"); tituloVuelo();
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
            system("cls"); tituloVuelo();
            seleccionPais();
            cout << "Origen: "; cin >> auxOrigen;
            cout << "Destino: "; cin >> auxDestino;
            if ((auxOrigen < 1 || auxOrigen > 10) || (auxDestino < 1 || auxDestino > 10)) {
                cout << "Opcion no valida\n"; system("pause");
            }
        } while ((auxOrigen < 1 || auxOrigen > 10) || (auxDestino < 1 || auxDestino > 10));

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
                cout << "Opcion no valida\n"; system("pause");
            }
        } while ((auxDia < 1 || auxDia > 31) || (auxMes < 1 || auxMes > 12));

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
            system("cls"); tituloVuelo();
            seleccionPais();
            cout << "Origen: "; cin >> auxOrigen;
            cout << "Destino: "; cin >> auxDestino;
            if ((auxOrigen < 1 || auxOrigen > 10) || (auxDestino < 1 || auxDestino > 10)) {
                cout << "Opcion no valida\n"; system("pause");
            }
        } while ((auxOrigen < 1 || auxOrigen > 10) || (auxDestino < 1 || auxDestino > 10));

        string origen = paises[auxOrigen - 1];
        string destino = paises[auxDestino - 1];

        do {
            cout << "\nDia de Ida: "; cin >> auxDiaIda;
            selecionMesVuelo();
            cout << "\nMes de Ida: "; cin >> auxMesIda;
            if (!validarDiaMes(auxDiaIda, auxMesIda)) { 
                cout << "Opcion no valida\n"; system("pause");
            }
        } while ((auxDiaIda < 1 || auxDiaIda > 31) || (auxMesIda < 1 || auxMesIda > 12));

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
            system("cls"); menuCheckin(); cin >> opc;
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
                cout << "Opción no válida\n"; system("pause"); break;
            }
        } while (opc != 4);
    }
};

