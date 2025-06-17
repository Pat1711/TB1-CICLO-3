#include"GestorSistema.h"

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    ajustarConsola();
    srand(static_cast<unsigned int>(time(nullptr))); 
    Console::CursorVisible = false;
    portada(); cin.get();
    
    GestorSistema sistema;
    sistema.ejecutar(); 

    system("pause>0"); 
    return 0;
}