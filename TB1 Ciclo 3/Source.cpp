#include"GestorSistema.h"

int main() {
    ajustarConsola();
    srand(static_cast<unsigned int>(time(nullptr))); 
    Console::CursorVisible = false;
    setlocale(LC_ALL,(""));

    portada(); cin.get();
    
    GestorSistema sistema;
    sistema.ejecutar(); 

    system("pause>0"); 
    return 0;
}