#ifndef _ARCHIVO_
#define _ARCHIVO_
#include <fstream>
template<class T>
class Gestortxt
{
private:
	string nombreArchivo;
	vector<T> lines;

	void cargar() {
		lines.clear();
		T linea;
		ifstream archivo(nombreArchivo); //Lectura

		if (archivo.is_open()) {
			while (getline(archivo, linea)) { //CHECKEA LAS LINEAS UNA POR UNA
				lines.push_back(linea);
			}
			archivo.close();
		}
	}

	void guardar() {
		ofstream archivo(nombreArchivo, ios::trunc); // sobreescribe el archivo
		if (archivo.is_open()) {
			for (int i = 0; i < lines.size(); i++) {
				archivo << lines[i] << endl;
			}
			archivo.close();
		}
	}

public:
	Gestortxt(string nom){
		nombreArchivo = nom;
        cargar();
	}
	~Gestortxt(){}

    size_t size() {
        return lines.size();
    }

	//Agregar elemento al final
	void agregar(T elem) {
		lines.push_back(elem);
		guardar();
	}

    T getLine(int i) {
        if(i >= 0 && i < lines.size())
        return lines[i];
        return T(); //habia un error aca
    }


};

#endif // !_ARCHIVO_
