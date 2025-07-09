#ifndef __GRAFO_H__
#define __GRAFO_H__

#include <vector>
#include <functional>
#include <iostream>
using namespace std;

template<class T>
class CGrafo {
protected:
	class CArco {
	public:
		T info;
		int v; // índice del vértice de llegada
		CArco(int vLlegada) {
			v = vLlegada;
		}
	};
	class CVertice {
	public:
		T info;
		vector<CArco*>* ady; // Lista de adyacencia
		CVertice() {
			ady = new vector<CArco*>();
		}
	};
	vector<CVertice*>* vertices;

public:
	CGrafo() {
		vertices = new vector<CVertice*>();
	}

	int adicionarVertice(T info) {
		CVertice* vert = new CVertice();
		vert->info = info;
		vertices->push_back(vert);
		return static_cast<int>(vertices->size() - 1);
	}

	int cantidadVertices() {
		return static_cast<int>(vertices->size());
	}

	T obtenerVertice(int v) {
		return vertices->at(v)->info;
	}

	int adicionarArco(int v, int vLlegada) {
		CVertice* ver = vertices->at(v);
		CArco* arc = new CArco(vLlegada);
		ver->ady->push_back(arc);
		return static_cast<int>(ver->ady->size() - 1);
	}

	int cantidadArcos(int v) {
		return static_cast<int>(vertices->at(v)->ady->size());
	}

	int obtenerVerticeLlegada(int v, int apos) {
		return vertices->at(v)->ady->at(apos)->v;
	}
};

#endif // __GRAFO_H__
