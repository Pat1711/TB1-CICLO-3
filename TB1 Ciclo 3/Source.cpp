#include"GestorSistema.h"

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    portada(); cin.get();

    GestorSistema sistema; 
    sistema.ejecutar(); 

    system("pause>0"); 
    return 0;
}