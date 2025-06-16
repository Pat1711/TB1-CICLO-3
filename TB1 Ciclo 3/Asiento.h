#ifndef __ASIENTOS__
#define __ASIENTOS__

#include <iostream>

using namespace std;

class Asiento {
private:
	char clasificacion;
	bool estado;
	int idAsiento;
public:
	Asiento(char clasificacion, bool estado, int idAsiento) : clasificacion(clasificacion), estado(estado), idAsiento(idAsiento) {

	};
	~Asiento() {};

	void mostrarAsiento() {
		cout << idAsiento << " - " << clasificacion << " [" << estado << "]";
	}

	void mostrarColor(int x, int y) {
		ubicar(x, y);
		if (estado == 0)cout << BG_GREEN; else cout << BG_RED;
		cout << idAsiento << "-" << clasificacion;
	}

	void setEstado(bool a) {
		estado = a;
	}
	bool getEstado() {
		return estado;
	}

	void mostrarAsientoDisponible() {
		if (estado == false)mostrarAsiento();
	}

	char getClasificacion() {
		return clasificacion;
	}

	bool isEstado() {
		return estado;
	}

	int getIdAsiento() {
		return idAsiento;
	}
};

#endif // !__ASIENTOS__