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
auto menu = [](void menu(), int& opcion) {
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
            menuSpawn("JetSMART");
            seleccionarOpc(opcion, opcPrincipal, 5);

            switch (opcion) {
            case 0:
                menuGestionVuelos(); break;
            case 1:
                menuGestionUsuarios(); break;
            case 2:
                gReservas.reservar(); break;
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
        menuSpawn("Menu Usuarios");
        do {
            seleccionarOpc(auxUser, opcUsuario, 3);
            limpiarDerecha();

            switch (auxUser) {
            case 0:
                gUsuario.agregarUsuario();
                system("pause>0"); break;
            case 1:
                gUsuario.mostrar(35,5);
                system("pause>0"); break;

            case 2: break;
            default:
                mensajeError(); break;
            }
        } while (auxUser != 2);
    }

    void menuGestionVuelos() {
        int auxVuelo = 0;
        menuSpawn("Buscar Vuelos");
        do {
            limpiarDerecha();
            seleccionarOpc(auxVuelo, opcVuelos, 6);

            switch (auxVuelo) {
            case 0: submenuMostrarVuelos(); break;
            case 1: mostrarVuelosPorMes(); break;
            case 2: mostrarVuelosPorPaises(); break;
            case 3: mostrarVuelosEnFecha(); break;
            case 4: mostrarVuelosEspecificos(); break;
            case 5: break;
            default: mensajeError(); break;
            }
        } while (auxVuelo != 5);
    }

    void submenuMostrarVuelos() {
        int auxSubMenu = 0;
        menuSpawn("Ordenar resultados");
        seleccionarOpc(auxSubMenu, opcOrdenar, 4);
        do {

            switch (auxSubMenu) {
            case 0:
                barraSpawn("Ordenamiento por precio");
                gVuelos.ordenarTodosLosVuelosPorPrecio();
                seleccionarOpc(auxSubMenu, opcOrdenar, 4); break;
            case 1:
                barraSpawn("Ordenamiento por origen");
                gVuelos.ordenarTodosLosVuelosPorPais();
                seleccionarOpc(auxSubMenu, opcOrdenar, 4); break;
            case 2:
                barraSpawn("Ordenamiento por id   ");
                gVuelos.ordenarTodosLosVuelosPorId();
                seleccionarOpc(auxSubMenu, opcOrdenar, 4); break;
            case 3: break;
            default: mensajeError(); break;
            }
        } while (auxSubMenu != 3);
    }

    void mostrarVuelosPorMes() {
        int auxValor;
        menuSpawn("Buscar por Mes");
        do {
            mostrarSeccion(tituloVuelo);
            selecionMesVuelo();
            cout << "Ingrese el mes: ";
            cin >> auxValor;
            cin.ignore();
            if (!enRango(auxValor, 1, 12)) mensajeError();
        } while (!enRango(auxValor, 1, 12));

        mostrarSeccion(tituloVuelo);
        barraSpawn("Vuelos de " + meses[auxValor - 1]);
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
        int opc = 0;
        do
        {
            menuSpawn("Check in");
            seleccionarOpc(opc, opcCheckin, 4);

            switch (opc)
            {
            case 0: //tarjetas embarque
                gCheckIn.mostrarCheckinsPorUsuario();
                system("pause>0"); break;
            case 1: //reservas
                gReservas.mostrarReservas();
                system("pause>0"); break;
            case 2: //chekcin
                gCheckIn.realizarCheckIn(gReservas);
                system("pause>0"); break;
            case 3: break;
            default:
                mensajeError(); break;
            }
        } while (opc != 3);
    }
};