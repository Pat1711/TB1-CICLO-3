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
auto validarPrecio = [](int p1, int p2) {
    return p1 >= 200 && p1 <= 10000 && p2 >= 200 && p2 <= 10000;
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
        gVuelos.indexarVuelosArbol(); 
    }

    void ejecutar() {
        int opcion = 0, n = 5;
        string destino, origen;

        do {
            if (debug) n = 6; else n = 5;
            menuSpawn("JetSMART");

            if (sesion)seleccionarOpc(opcion, opcPrincipalAlt, n);
            else seleccionarOpc(opcion, opcPrincipal, n);

            switch (opcion) {
            case 0:
                menuGestionVuelos(); break;
            case 1: //INICIAR SESION/CERRAR SESION
                if (!sesion)sesionMenu();
                else gUsuario.cerrarSesion();
                break;
            case 2:
                gReservas.reservar(); break;
            case 3:
                menuGestionCheckin(); break;
            case 4://SALIR
                break;
            case 5:
                menuGestionAdmin(); break;
            default:
                opcion = 0; break;
            }

        } while (opcion != 4);
    }

    void sesionMenu() {
        int auxUser2 = 0;
        menuSpawn("INICIAR SESION");
        do {
            seleccionarOpc(auxUser2, opcSesion, 3);
            limpiarDerecha();

            switch (auxUser2) {
            case 0:
                gUsuario.iniciarSesion(); break;
            case 1:
                gUsuario.agregarUsuario(); system("pause>0"); break;
            case 2:
                break;
            default:
                mensajeError(); break;
            }

            if (sesion) auxUser2 = 2;

        } while (auxUser2 != 2);
    }

    void menuGestionAdmin() {
        int auxUser = 0;
        menuSpawn("Menu Admin");
        do {
            seleccionarOpc(auxUser, opcUsuario, 4);
            limpiarDerecha();

            switch (auxUser) {
            case 0:
                gUsuario.agregarUsuario(); system("pause>0"); break;
                system("pause>0"); break;
            case 1:
                gUsuario.mostrar(35, 5); break;
            case 2:
                seleccionPais(); selecionMesVuelo(32, 10);
                gVuelos.agregarVueloManual();
                break;
            case 3: break;
            default:
                mensajeError(); break;
            }

        } while (auxUser != 2);
    }

    void menuGestionVuelos() {
        int auxVuelo = 0;
        menuSpawn("Buscar Vuelos");
        do {
            limpiarIzquierda();
            seleccionarOpc(auxVuelo, opcVuelos, 7);

            switch (auxVuelo) {
            case 0: submenuMostrarVuelos(); break;
            case 1: mostrarVuelosPorMes(); break;
            case 2: mostrarVuelosPorPaises(); break;
            case 3: mostrarVuelosEnFecha(); break;
            case 4: mostrarVuelosEspecificos(); break;
            case 5: mostrarVuelosRangoPrecios(); break;
            case 6: break;
            default: mensajeError(); break;
            }
        } while (auxVuelo != 6);
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
                if (gVuelos.isQuiereReservar())
                {
                    gReservas.reservar(); gVuelos.setQuiereReservar(0); return;
                }
                seleccionarOpc(auxSubMenu, opcOrdenar, 4); break;
            case 1:
                barraSpawn("Ordenamiento por origen");
                gVuelos.ordenarTodosLosVuelosPorPais();
                if (gVuelos.isQuiereReservar())
                {
                    gReservas.reservar(); gVuelos.setQuiereReservar(0); return;
                }
                seleccionarOpc(auxSubMenu, opcOrdenar, 4); break;
            case 2:
                barraSpawn("Ordenamiento por id   ");
                gVuelos.ordenarTodosLosVuelosPorId();
                if (gVuelos.isQuiereReservar())
                {
                    gReservas.reservar(); gVuelos.setQuiereReservar(0); return;
                }
                seleccionarOpc(auxSubMenu, opcOrdenar, 4); break;
            case 3: break;
            default: mensajeError(); break;
            }
        } while (auxSubMenu != 3);
    }

    void mostrarVuelosPorMes() {
        int auxValor;
        barraSpawn("Buscar por Mes     ");
        limpiarDerecha();

        do {
            selecionMesVuelo();
            ubicar(49, 9); ingresarDato(auxValor);
            cin.ignore();
            if (!enRango(auxValor, 1, 12)) mensajeError();
        } while (!enRango(auxValor, 1, 12));

        limpiarDerecha();
        barraSpawn("Vuelos de " + meses[auxValor - 1]);
        gVuelos.mostrarVuelosPorMes(auxValor);
        if (gVuelos.isQuiereReservar())
        {
            gReservas.reservar(); gVuelos.setQuiereReservar(0); return;
        }
    }

    void mostrarVuelosPorPaises() {
        int auxOrigen, auxDestino;
        barraSpawn("Buscar por Pais     ");
        limpiarDerecha();
        do {
            seleccionPais();
            ubicar(32, 9); cout << "Origen: "; ingresarDato(auxOrigen);
            ubicar(32, 10); cout << "Destino: "; ingresarDato(auxDestino);

            if (!validarDestino(auxOrigen, auxDestino)) {
                mensajeError(); break;
            }
        } while (!validarDestino(auxOrigen, auxDestino));

        string origen = paises[auxOrigen - 1];
        string destino = paises[auxDestino - 1];

        limpiarDerecha();
        barraSpawn("Vuelos " + origen + "- " + destino + "   ");
        gVuelos.mostrarVuelosPorPaises(origen, destino);
        if (gVuelos.isQuiereReservar())
        {
            gReservas.reservar(gVuelos.getRutasValidas()); gVuelos.setQuiereReservar(0); return;
        }
    }

    void mostrarVuelosEnFecha() {
        int auxDia, auxMes;
        barraSpawn("Buscar por Fecha  ");
        limpiarDerecha();

        do {
            ubicar(32, 5); cout << BG_WHITE << BLACK << "Dia de Ida: "; ingresarDato(auxDia);
            selecionMesVuelo(32, 6);
            ingresarDato(auxMes);
            if (!validarDiaMes(auxDia, auxMes)) {
                mensajeError(); break;
            }
        } while (!validarDiaMes(auxDia, auxMes));

        limpiarDerecha();
        barraSpawn("Vuelos para el " + to_string(auxDia) + "/" + to_string(auxMes));
        gVuelos.mostrarVuelosEnFecha(auxMes, auxDia);
        if (gVuelos.isQuiereReservar())
        {
            gReservas.reservar(); gVuelos.setQuiereReservar(0); return;
        }
    }

    void mostrarVuelosEspecificos() {
        int auxOrigen, auxDestino, auxDiaIda, auxMesIda;
        barraSpawn("Busqueda Especifica");
        limpiarDerecha();

        do {
            seleccionPais();
            ubicar(32, 9); cout << "Origen: "; ingresarDato(auxOrigen);
            ubicar(32, 10); cout << "Destino: "; ingresarDato(auxDestino);
            if (!validarDestino(auxOrigen, auxDestino)) {
                mensajeError(); break;
            }
        } while (!validarDestino(auxOrigen, auxDestino));

        string origen = paises[auxOrigen - 1];
        string destino = paises[auxDestino - 1];

        do {
            ubicar(32, 12); cout << BG_WHITE << BLACK << "Dia de Ida: "; ingresarDato(auxDiaIda);
            selecionMesVuelo(32, 13);
            ingresarDato(auxMesIda);
            if (!validarDiaMes(auxDiaIda, auxMesIda)) {
                mensajeError(); break;
            }
        } while (!validarDiaMes(auxDiaIda, auxMesIda));

        limpiarDerecha();
        gVuelos.mostrarVuelosDatosIda(origen, destino, auxMesIda, auxDiaIda);
        if (gVuelos.isQuiereReservar())
        {
            gReservas.reservar(); gVuelos.setQuiereReservar(0); return;
        }
    }

    void mostrarVuelosRangoPrecios() {
        int auxPrecio1, auxPrecio2;
        barraSpawn("Buscar rango Precios   ");
        limpiarDerecha();

        do {
            ubicar(32, 5); cout << BG_WHITE << BLACK << "Ingresar el rango de precios:"; 
            ubicar(32, 7); cout << BG_WHITE << BLACK << "Precio Base: "; ingresarDato(auxPrecio1);
            ubicar(32, 8); cout << BG_WHITE << BLACK << "Precio Tope: "; ingresarDato(auxPrecio2); 
            if (!validarPrecio(auxPrecio1, auxPrecio2)) {
                mensajeError(); break;
            }
        } while (!validarPrecio(auxPrecio1, auxPrecio2)); 

        limpiarDerecha();
        barraSpawn("Vuelos de " + to_string(auxPrecio1) + " - " + to_string(auxPrecio2) + " $  ");
        gVuelos.buscarEnRangoPrecios(auxPrecio1, auxPrecio2);
        if (gVuelos.isQuiereReservar())
        {
            gReservas.reservar(); gVuelos.setQuiereReservar(0); return;
        }
    }

    void menuGestionCheckin() {
        int opc = 0;
        menuSpawn("Check in");
        do
        {
            limpiarDerecha();
            seleccionarOpc(opc, opcCheckin, 4);

            switch (opc)
            {
            case 0: //tarjetas embarque
                gCheckIn.mostrarCheckinsPorUsuario();
                system("pause>0"); break;
            case 1: //reservas //YA ESTA
                gReservas.mostrarTodasLasReservas();
                system("pause>0"); break;
            case 2: //chekcin
                gCheckIn.realizarCheckIn(gReservas);
                system("pause>0"); break;
            case 3:
                break;
            default:
                mensajeError(); break;
            }
        } while (opc != 3);
    }
};
