#include "Sistema.h"
#include "ListaDoble.h"

int main() {
    Lista<Pasajero*> pLista;
    Lista<Vuelo*> vLista;

    //prueba para mostrar pasajeros wazaaa
    pLista.insertarInicio(new Pasajero("buki", "buki2", "hola@gmail.com", 75202855));
    pLista.insertarInicio(new Pasajero("buki2", "buki3", "hola2@gmail.com", 65202855));
    pLista.insertarInicio(new Pasajero("buki4", "buki5", "hola3@gmail.com", 55202855));
        
    int opcion;
    Pasajero* nuevo;
    do {
        system("cls"); menuPrincipal();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
        case 1: {
            int auxUser;
            do {
                system("cls"); menuUsuario();
                cin >> auxUser;
                cin.ignore();

                switch (auxUser) {
                case 1: system("cls"); tituloUsuario();
                    // -- Registro de pasajero --
                    nuevo = pedirDatosPasajero();
                    pLista.insertarInicio(nuevo);
                    // -- Conclusi�n --
                    cout << "Pasajero registrado correctamente\n";
                    system("pause"); break;
                case 2: system("cls"); tituloUsuario();
                    // -- Mostrar Pasajeros ---
                    pLista.mostrar();
                    // -- Conclusi�n --
                    system("pause"); break;
                case 3: system("pause"); break;
                default: cout << "Opci�n no v�lida\n"; system("pause"); break;
                }
            } while (auxUser != 3);
            break;
        }
        case 2: system("cls"); cout << "En trabajo\n"; system("pause"); break;
        case 3: system("cls"); cout << "En trabajo\n"; system("pause"); break;
        case 4: system("cls"); cout << "En trabajo\n"; system("pause"); break;
        case 5: cout << "Gracias por usar el sistema\n"; system("pause"); break;
        default: cout << "Opci�n inv�lida\n"; system("pause"); break;
        }

    } while (opcion != 5);

    return 0;
}
