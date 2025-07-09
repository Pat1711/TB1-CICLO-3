#ifndef __GESTOR_VUELOS__
#define __GESTOR_VUELOS__

#include <map>
#include <vector>
#include "Vuelo.h" 
#include "ArbolBB.h"
#include "AVL.h"
#include <set>
#include "Grafo.h"

using namespace std;

// --- Varibles Universales --- //
string meses[] = {
        "Enero", "Febrero", "Marzo", "Abril", "Mayo",
        "Junio", "Julio", "Agosto", "Septiembre", "Octubre",
        "Noviembre", "Diciembre"
};

// funciones adicionales para el arbol BB
void imprimirVuelo(Vuelo* v) {
    v->mostrarVuelo(); 
}

int compararVueloPorPrecio(Vuelo* a, Vuelo* b) {
    return a->getPrecio() - b->getPrecio(); 
}

// funciones adicionales para el AVL
int compararVuelosEspecificos(Vuelo* a, Vuelo* b) {
    if (a->getOrigen() != b->getOrigen())
        return a->getOrigen() < b->getOrigen() ? -1 : 1;
    if (a->getDestino() != b->getDestino())
        return a->getDestino() < b->getDestino() ? -1 : 1;
    if (a->getMesIda() != b->getMesIda())
        return a->getMesIda() < b->getMesIda() ? -1 : 1;
    if (a->getDiaIda() != b->getDiaIda())
        return a->getDiaIda() < b->getDiaIda() ? -1 : 1;
    // no pregunten :v
    return 0;
}

class GestorVuelo {
private:
    //clave: int | valor: [clave: int, valor: vector de vuelos]
    map<int, map<int, vector<Vuelo*>>> vuelosPorMes;
    bool vuelosEncontrados;  
    bool quiereReservar; 
    ArbolBB<Vuelo*>* arbol; 
    ArbolAVL<Vuelo*>* avl;
    CGrafo<Vuelo*> grafo;
    vector<vector<Vuelo*>> rutasValidas;
public:
    GestorVuelo() {
        arbol = new ArbolBB<Vuelo*>(imprimirVuelo,compararVueloPorPrecio);
        avl = new ArbolAVL<Vuelo*>(imprimirVuelo, compararVuelosEspecificos);
    }
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
                int diaVuelta = diaIda + 1 + rand() % 14;

                int mesIda = mes;
                int mesVuelta = mes;

                if (diaVuelta > 30) {
                    diaVuelta = abs(diaVuelta - 30);
                    mesVuelta = mesIda + 1;

                    if (mesVuelta > 12) {
                        mesVuelta = 1;
                    }
                }

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

                //GENERAR GRAFO DE VUELOS
                int idxNuevo = grafo.adicionarVertice(vuelo);

                // Conecta con otros vuelos existentes que podrían ser escalas
                for (int i = 0; i < grafo.cantidadVertices() - 1; ++i) {
                    Vuelo* otro = grafo.obtenerVertice(i);

                    if (vuelo->getOrigen() == otro->getDestino() &&
                        (vuelo->getMesIda() > otro->getMesVuelta() ||
                            (vuelo->getMesIda() == otro->getMesVuelta() && vuelo->getDiaIda() > otro->getDiaVuelta()))
                        ) {
                        grafo.adicionarArco(i, idxNuevo); // vuelo "otro" conecta hacia "vuelo"
                    }
                    if (vuelo->getDestino() == otro->getOrigen() &&
                        (vuelo->getMesVuelta() < otro->getMesIda() ||
                            (vuelo->getMesVuelta() == otro->getMesIda() && vuelo->getDiaVuelta() < otro->getDiaIda()))
                        ) {
                        grafo.adicionarArco(idxNuevo, i); // vuelo "vuelo" conecta hacia "otro"
                    }
                }

            }
        }
    }

    void agregarVueloManual() {
        string origen, destino;
        int aux;
        int diaIda, mesIda, diaVuelta, mesVuelta, codigoVuelo;

        int x =32, y = 17;
        
        ubicar(x, y); cout << BG_WHITE << BLACK << "Origen: "; ingresarDato(aux);
        switch (aux)
        {
        case 1: origen = "Peru"; break; case 2: origen = "Chile"; break; case 3: origen = "Argentina"; break;
        case 4: origen = "Brasil"; break; case 5: origen = "Colombia"; break; case 6: origen = "Ecuador"; break;
        case 7: origen = "Mexico"; break; case 8: origen = "EE.UU"; break; case 9: origen = "Espania"; break;
        case 10: origen = "Italia"; break;
        default:break;
        }
        ubicar(x, y+=1); cout << "Destino: "; ingresarDato(aux);
        switch (aux)
        {
        case 1: destino = "Peru"; break; case 2: destino = "Chile"; break; case 3: destino = "Argentina"; break;
        case 4: destino = "Brasil"; break; case 5: destino = "Colombia"; break; case 6: destino = "Ecuador"; break;
        case 7: destino = "Mexico"; break; case 8: destino = "EE.UU"; break; case 9: destino = "Espania"; break;
        case 10: destino = "Italia"; break;
        default:break;
        }
        ubicar(x, y += 2); cout << "Dia de Ida: "; ingresarDato(diaIda);
        ubicar(x, y += 1); cout << "Mes de ida: "; ingresarDato(mesIda);
        ubicar(x, y += 2); cout << "Dia de vuelta: "; ingresarDato(diaVuelta);
        ubicar(x, y += 1); cout << "mesVuelta: "; ingresarDato(mesVuelta);
        ubicar(x, y += 2); cout << BG_WHITE << BLACK << "Codigo: "; ingresarDato(codigoVuelo);


        Vuelo* vuelo = new Vuelo(origen, destino, diaIda, mesIda, diaVuelta, mesVuelta, codigoVuelo);
        agregarVuelo(vuelo);

        ubicar(x, y += 2); cout << "Vuelo agregado correctamente";
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
        rutasValidas.clear();

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
            ubicar(35, 5);
            cout << BG_WHITE << BLACK << "No se encontraron vuelos directos disponibles."; 

            buscarRutasConEscalas(origen, destino);
            if (!rutasValidas.empty()) {
                reservaRuta();
            }
            else {
                system("pause>0");
            }
        }
        else {
            iterarPaginas(vuelosAux);
        }
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

    // PARTE ABB
    void indexarVuelosArbol() {
        vector<Vuelo*> todos = obtenerTodosLosVuelos();
        for (auto v : todos) {
            arbol->insertar(v); 
        }
    }

    // Busqueda de vuelos por rango de precios
    void buscarEnRangoPrecios(int p1, int p2) {
        vector<Vuelo*> encontrados;

        arbol->buscarRangoPrecios(p1, p2, encontrados); // llama a la recursiva que identifica en rango de precios

        iterarPaginas(encontrados); 
    }

    // PARTE DEL AVL
    void indexarVuelosAVL() {
        vector<Vuelo*> todos = obtenerTodosLosVuelos();
        for (Vuelo* v : todos) {
            avl->Insertar(v);
        }
    }

    void buscarPorDatosEspecificos(string origen, string destino, int mes, int dia) {
        vector<Vuelo*> encontrados;
        Vuelo* clave = new Vuelo(origen, destino, dia, mes, 0, 0, 0);

        avl->buscarEspecifico(clave, encontrados);

        if (encontrados.empty()) {
            ubicar(32, 6);
            cout << BG_WHITE << BLACK << "No se encontraron vuelos disponibles";
        }

        iterarPaginas(encontrados);
    }

    bool isVuelosEncontrados() {
        return vuelosEncontrados;
    }
    void mostrarPagina(vector<Vuelo*>& vuelos, int pagina) {
        int vuelosPorPagina = 10;
        int totalPaginas = static_cast<int>((vuelos.size() + 9) / 10);

        if (pagina == totalPaginas - 1) { //limpiar pantalla en ultima pagina
            limpiarDerecha(); 
        }

        int inicio = pagina * vuelosPorPagina;
        int fin = min(inicio + vuelosPorPagina, (int)vuelos.size());

        int x1 = 32, x2 = 75;
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

    void reservaRuta() {
        quiereReservar = false;
        ubicar(30, 2);
        cout << BG_JTAZUL << WHITE << "ESC para salir. ENTER: reservar una ruta.                                 ";
        int tecla;
        /*int n;*/
        do {
            tecla = _getch();

            if (tecla == 13) { // 13 = ENTER
                quiereReservar = true; tecla = 27;
            }

        } while (tecla != 27);
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
            else if (tecla == 13) { // 13 = ENTER
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

    void buscarRutasConEscalas(string origen, string destino) {
        vector<Vuelo*> caminoActual;

        function<void(int, double)> dfs = [&](int idx, double precioAcumulado) {
            Vuelo* actual = grafo.obtenerVertice(idx);
            caminoActual.push_back(actual);

            if(caminoActual.size() > 3) {
                caminoActual.pop_back();
                return;
            }

            if (actual->getDestino() == destino) {
                rutasValidas.push_back(caminoActual);
            }
            else {
                for (int i = 0; i < grafo.cantidadArcos(idx); ++i) {
                    int vecino = grafo.obtenerVerticeLlegada(idx, i);
                    Vuelo* siguiente = grafo.obtenerVertice(vecino);

                    // evitar ciclos
                    if (find(caminoActual.begin(), caminoActual.end(), siguiente) == caminoActual.end()) {
                        dfs(vecino, precioAcumulado + siguiente->getPrecio());
                    }
                }
            }
                caminoActual.pop_back();
            
            };

        // Buscar vuelos que parten del origen
        for (int i = 0; i < grafo.cantidadVertices(); ++i) {
            Vuelo* vuelo = grafo.obtenerVertice(i);
            if (vuelo->getOrigen() == origen) {
                dfs(i, vuelo->getPrecio());
            }
        }

        // Si no hay rutas
        if (rutasValidas.empty()) {
            cout << "No se encontraron rutas desde " << origen << " a " << destino << ".\n";
            return;
        }

        // Ordenar rutas por precio total
        sort(rutasValidas.begin(), rutasValidas.end(), [](const vector<Vuelo*>& a, const vector<Vuelo*>& b) {
            double sumaA = 0, sumaB = 0;
            for (auto v : a) sumaA += v->getPrecio();
            for (auto v : b) sumaB += v->getPrecio();
            return sumaA < sumaB;
            });

        // Mostrar solo las N mejores
        int x = 35, y = 7;
        int cantidad = min(2, (int)rutasValidas.size());
        ubicar(x, y); cout << "Mejores " << cantidad << " vuelos con escalas de " << origen << " a " << destino << "\n";
       
        for (int i = 0; i < cantidad; ++i) {
            y = 9;
            double precioTotal = 0;
            ubicar(x, y);  cout << BG_JTAZUL << WHITE << "Ruta #" << (i + 1) << ": \n" << BG_WHITE << BLACK;
            for (Vuelo* v : rutasValidas[i]) {
                v->mostrarVuelo2(x,y +=2);
                y += 3;
                precioTotal += v->getPrecio();
            }
            ubicar(x, y+=1);  cout << "Precio total: $" << precioTotal << "\n\n";
            x += 43;
        }
    }

    vector<vector<Vuelo*>> getRutasValidas() {
        return rutasValidas;
    }
};

#endif // !__GESTOR_VUELOS__