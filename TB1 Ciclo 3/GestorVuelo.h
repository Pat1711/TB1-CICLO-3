#ifndef __GESTOR_VUELOS__
#define __GESTOR_VUELOS__

#include <map>
#include <vector>
#include "Vuelo.h" 
#include <set>

using namespace std;

// --- Varibles Universales --- //
string meses[] = {
        "Enero", "Febrero", "Marzo", "Abril", "Mayo",
        "Junio", "Julio", "Agosto", "Septiembre", "Octubre",
        "Noviembre", "Diciembre"
};

class GestorVuelo {
private:
    //clave: int | valor: [clave: int, valor: vector de vuelos]
    map<int, map<int, vector<Vuelo*>>> vuelosPorMes;
    bool vuelosEncontrados;  
    bool quiereReservar; 
public:
    void agregarVuelo(Vuelo* vuelo) {
        int mesIda = vuelo->getMesIda();
        int diaIda = vuelo->getDiaIda();
        vuelosPorMes[mesIda][diaIda].push_back(vuelo);
    }

    void generarVuelosAutomaticos() {
        set<string> codigosGenerados;

        for (int mes = 1; mes <= 12; mes++) {
            for (int i = 0; i < 10; i++) {
                int origenIdx, destinoIdx;
                do {
                    // -- Destino (Pais) --
                    origenIdx = rand() % 10;
                    destinoIdx = rand() % 10;
                } while (origenIdx == destinoIdx);

                string origen = paises[origenIdx];
                string destino = paises[destinoIdx];

                // -- Dias de ida y vuelta --
                int diaIda = 1 + rand() % 30;
                int diaVuelta = 1 + rand() % 30;

                int mesIda = mes;
                int mesVuelta;



                do {
                    if (mesIda == 12 && diaIda == diaVuelta) {
                        diaVuelta = (diaIda % 30) + 1; // fuerza a que sean distintos
                    }
                    mesVuelta = mesIda + rand() % (13 - mesIda);
                } while (diaIda == diaVuelta && mesVuelta == mesIda);

                string codigoVuelo;
                do {
                    codigoVuelo = "";
                    for (int j = 0; j < 5; j++) {
                        codigoVuelo += '0' + rand() % 10;
                    }
                } while (codigosGenerados.count(codigoVuelo) > 0);

                codigosGenerados.insert(codigoVuelo);

                Vuelo* vuelo = new Vuelo(origen, destino, diaIda, mesIda, diaVuelta, mesVuelta, stoi(codigoVuelo));
                agregarVuelo(vuelo);
            }
        }
    }

    void mostrarVuelosEnFecha(int mes, int dia) {
        //Para poder mostrar
        vector<Vuelo*> vuelosAux;
        vuelosAux.clear();

        vuelosEncontrados = false;
        if (vuelosPorMes.count(mes) && vuelosPorMes[mes].count(dia)) {
            for (Vuelo* v : vuelosPorMes[mes][dia]) {
                vuelosAux.push_back(v);
                vuelosEncontrados = true;
            }
        }

        if (!vuelosEncontrados) {
            ubicar(32, 6);
            cout << BG_WHITE << BLACK << "No se encontraron vuelos disponibles";
        }

        iterarPaginas(vuelosAux);
    }

    void mostrarVuelosPorMes(int mes) {
        //Para poder mostrar
        vector<Vuelo*> vuelosAux; 
        vuelosAux.clear(); 

        vuelosEncontrados = false;
        if (vuelosPorMes.count(mes)) {
            for (int dia = 1; dia <= 30; dia++) {
                if (vuelosPorMes[mes].count(dia)) {
                    for (Vuelo* v : vuelosPorMes[mes][dia]) {
                        vuelosAux.push_back(v); 
                        vuelosEncontrados = true;
                    }
                }
            }
        }

        if (!vuelosEncontrados) {
            ubicar(32, 6);
            cout << BG_WHITE << BLACK << "No se encontraron vuelos disponibles";
        }

        iterarPaginas(vuelosAux); 
    }

    void mostrarVuelosPorPaises(string origen, string destino) {
        //Para poder mostrar
        vector<Vuelo*> vuelosAux; 
        vuelosAux.clear();

        vuelosEncontrados = false;

        for (auto itMes = vuelosPorMes.begin(); itMes != vuelosPorMes.end(); ++itMes) {
            int mes = itMes->first;
            map<int, vector<Vuelo*>>& dias = itMes->second;

            for (auto itDia = dias.begin(); itDia != dias.end(); ++itDia) {
                int dia = itDia->first;
                vector<Vuelo*>& listaVuelos = itDia->second;

                for (Vuelo* vuelo : listaVuelos) {
                    if (vuelo->getOrigen() == origen && vuelo->getDestino() == destino) {
                        vuelosAux.push_back(vuelo); 
                        vuelosEncontrados = true;
                    }
                }
            }
        }


        if (!vuelosEncontrados) {
            ubicar(32, 6);
            cout << BG_WHITE << BLACK << "No se encontraron vuelos disponibles"; 
        }

        iterarPaginas(vuelosAux);
    }

    void mostrarVuelosDatosIda(string origen, string destino, int mesIda, int diaIda) {
        //Para poder mostrar
        vector<Vuelo*> vuelosAux;
        vuelosAux.clear();

        vuelosEncontrados = false;

        if (vuelosPorMes.count(mesIda) && vuelosPorMes[mesIda].count(diaIda)) {
            vector<Vuelo*>& listaVuelos = vuelosPorMes[mesIda][diaIda];

            for (Vuelo* vuelo : listaVuelos) {
                if (vuelo->getOrigen() == origen && vuelo->getDestino() == destino) {          
                    vuelosAux.push_back(vuelo);
                    vuelosEncontrados = true;
                }
            }
        }

        if (!vuelosEncontrados) {
            ubicar(32, 6);
            cout << BG_WHITE << BLACK << "No se encontraron vuelos disponibles";
        }

        iterarPaginas(vuelosAux);

    }

    //Recursivas
    void mostrarVuelosDelDia(vector<Vuelo*>& vuelos, size_t i = 0) {
        if (i >= vuelos.size()) return;
        vuelos[i]->mostrarVuelo();
        mostrarVuelosDelDia(vuelos, i + 1);
    }

    void mostrarVuelosDelMes(map<int, vector<Vuelo*>>& dias, map<int, vector<Vuelo*>>::iterator itDia) {
        if (itDia == dias.end()) return;
        mostrarVuelosDelDia(itDia->second);
        mostrarVuelosDelMes(dias, next(itDia));
    }

    // iterador es lo mismo que auto, pero como lo estamos definiedo en los argumentos no puede ir auto debe ir iterador

    void mostrarTodosLosVuelosRec(map<int, map<int, vector<Vuelo*>>>& vuelosPorMes, map<int, map<int, vector<Vuelo*>>>::iterator itMes) {
        if (itMes == vuelosPorMes.end()) return;
        mostrarVuelosDelMes(itMes->second, itMes->second.begin());
        mostrarTodosLosVuelosRec(vuelosPorMes, next(itMes));
    }

    void mostrarTodosLosVuelos() {
        cout << "\n=== Todos los vuelos registrados ===\n";
        mostrarTodosLosVuelosRec(vuelosPorMes, vuelosPorMes.begin());
    }

    //Extraemos el vector de vuelos de map, sin importar la fecha
    vector<Vuelo*> obtenerTodosLosVuelos() {
        vector<Vuelo*> todos;
        for (auto& itMes : vuelosPorMes) {
            for (auto& itDia : itMes.second) {
                for (Vuelo* v : itDia.second) {
                    todos.push_back(v);
                }
            }
        }
        return todos;
    }

    void ordenarTodosLosVuelosPorPrecio() {
        vector<Vuelo*> todos = obtenerTodosLosVuelos();
        size_t n = todos.size();

        //Ordenamiento de selección
        for (int i = 0; i < n - 1; i++) {
            int menor = i;
            for (int j = i + 1; j < n; j++) {
                if (todos[j]->getPrecio() < todos[menor]->getPrecio()) {
                    menor = j;
                }
            }

            if (menor != i) {
                Vuelo* temp = todos[i];
                todos[i] = todos[menor];
                todos[menor] = temp;
            }
        }

        iterarPaginas(todos);
    }

    void ordenarTodosLosVuelosPorId() {
        vector<Vuelo*> todos = obtenerTodosLosVuelos();
        size_t n = todos.size();
        bool ordenado;

        //Ordenamiento de Bubble Sort
        for (int i = 0; i < n - 1; i++) {
            ordenado = true;
            for (int j = 0; j < n - i - 1; j++) {
                if (todos[j]->getCodigoVuelo() > todos[j + 1]->getCodigoVuelo()) {
                    Vuelo* aux = todos[j];
                    todos[j] = todos[j + 1];
                    todos[j + 1] = aux;
                    ordenado = false;
                }
            }
            if (ordenado) break;
        }

        iterarPaginas(todos);

    }

    void ordenarTodosLosVuelosPorPais() {
        vector<Vuelo*> todos = obtenerTodosLosVuelos();
        size_t n = todos.size();
        int k;

        //Ordenamiento de Insercion
        for (int i = 1; i < n; i++) {
            Vuelo* aux = todos[i];
            k = i - 1;
            while (k >= 0 && aux->getIndicePaisOrigen() < todos[k]->getIndicePaisOrigen()) {
                todos[k + 1] = todos[k];
                k--;
            }
            todos[k + 1] = aux;
        }

        iterarPaginas(todos);

    }

    Vuelo* getVueloPorCodigo(int codeVuelo) {
        for (auto itMes = vuelosPorMes.begin(); itMes != vuelosPorMes.end(); ++itMes) {
            int mes = itMes->first;
            map<int, vector<Vuelo*>>& dias = itMes->second;

            for (auto itDia = dias.begin(); itDia != dias.end(); ++itDia) {
                int dia = itDia->first;
                vector<Vuelo*>& listaVuelos = itDia->second;

                for (Vuelo* vuelo : listaVuelos) {
                    if (vuelo->getCodigoVuelo() == codeVuelo) {
                        return vuelo;
                    }
                }
            }
        }
        return nullptr;
    }

    bool isVuelosEncontrados() {
        return vuelosEncontrados;
    }
    void mostrarPagina(vector<Vuelo*>& vuelos, int pagina) {

        int vuelosPorPagina = 10;
        int inicio = pagina * vuelosPorPagina;
        int fin = min(inicio + vuelosPorPagina, (int)vuelos.size());

        int x1 = 32, x2 = 78;
        int yInicio = 4;
        int espacioVertical = 5;

        for (int i = inicio; i < fin; ++i) {
            int localIndex = i - inicio; // 0 a 9
            int x = (localIndex < 5) ? x1 : x2;
            int y = yInicio + (localIndex % 5) * espacioVertical;
            vuelos[i]->mostrarVuelo2(x, y);
        }

        // Mostrar número de página
        ubicar(30, 1);
        cout << BG_JTAZUL << WHITE << "Pagina " << (pagina + 1) << " / " << ((vuelos.size() + 9) / 10);
        if (pagina < 10) cout << " ";
        ubicar(30, 2);
        cout << "Usa Flechas izq y der para cambiar de pagina. ESC para salir. ENTER: reservar";
    }



    void iterarPaginas(vector<Vuelo*>& vuelos) {
        int totalPaginas = static_cast<int>((vuelos.size() + 9) / 10);
        int paginaActual = 0;
        int tecla;
        quiereReservar = false; 

        do {
            mostrarPagina(vuelos, paginaActual);
            tecla = _getch();

            if (tecla == 224) {
                int flecha = _getch();
                if (flecha == 77 && paginaActual < totalPaginas - 1) { //  flecha derecha
                    paginaActual++;
                }
                else if (flecha == 75 && paginaActual > 0) { //  flecha izquierda
                    paginaActual--;
                }
            }
            else if (tecla == 13) {
                quiereReservar = true; tecla = 27; 
            }

        } while (tecla != 27); // 27 = ESC
    }

    bool isQuiereReservar() {
        return quiereReservar; 
    }

    void setQuiereReservar(bool quiereReservar) {
        this->quiereReservar = quiereReservar;
    }
};

#endif // !__GESTOR_VUELOS__