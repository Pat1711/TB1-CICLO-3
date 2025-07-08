#ifndef __GRAFO_H__
#define __GRAFO_H__

#include <vector>
#include <queue>
#include <stack>
#include <functional>
#include <algorithm>
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

	CVertice* obtenerVerticePtr(int v) {
		return vertices->at(v);
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

	void modificarVertice(int v, T info) {
		vertices->at(v)->info = info;
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

	T obtenerArco(int v, int apos) {
		CVertice* ver = vertices->at(v);
		return ver->ady->at(apos)->info;
	}

	void modificarArco(int v, int apos, T info) {
		CVertice* ver = vertices->at(v);
		ver->ady->at(apos)->info = info;
	}

	int obtenerVerticeLlegada(int v, int apos) {
		return vertices->at(v)->ady->at(apos)->v;
	}

	void imprimirGrafo() {
		for (int i = 0; i < vertices->size(); ++i) {
			CVertice* v = vertices->at(i);
			cout << i << " -> ";
			for (CArco* arco : *(v->ady)) {
				cout << obtenerVertice(arco->v) << " ";
			}
			cout << endl;
		}
	}

	void imprimirGrafo2(function<void(ArbolBB<int>*)> mostrarArbol) {
		for (int i = 0; i < vertices->size(); ++i) {
			CVertice* v = vertices->at(i);
			cout << i << " -> ";
			mostrarArbol(v->info);
			cout << " conecta con: ";
			for (CArco* arco : *(v->ady)) {
				mostrarArbol(obtenerVertice(arco->v));
			}
			cout << endl;
		}
	}

	int BFSbuscar(int inicio, T objetivo) {
		vector<bool> visitado(vertices->size(), false);
		queue<int> q;

		q.push(inicio);
		visitado[inicio] = true;

		while (!q.empty()) {
			int actual = q.front(); q.pop();
			if (obtenerVertice(actual) == objetivo) return actual;

			for (int i = 0; i < cantidadArcos(actual); ++i) {
				int vecino = obtenerVerticeLlegada(actual, i);
				if (!visitado[vecino]) {
					visitado[vecino] = true;
					q.push(vecino);
				}
			}
		}
		return -1;
	}

	int DFSbuscar(int inicio, T objetivo) {
		vector<bool> visitado(vertices->size(), false);
		stack<int> s;
		s.push(inicio);

		while (!s.empty()) {
			int actual = s.top(); s.pop();
			if (!visitado[actual]) {
				visitado[actual] = true;
				if (obtenerVertice(actual) == objetivo) return actual;

				for (int i = cantidadArcos(actual) - 1; i >= 0; --i) {
					int vecino = obtenerVerticeLlegada(actual, i);
					if (!visitado[vecino]) s.push(vecino);
				}
			}
		}
		return -1;
	}

	vector<T> detectarCicloDirigido() {
		int n = vertices->size();
		vector<bool> visitado(n, false);
		vector<bool> enCamino(n, false);
		vector<int> camino;
		vector<T> ciclo;

		function<bool(int)> dfs = [&](int v) -> bool {
			visitado[v] = true;
			enCamino[v] = true;
			camino.push_back(v);

			for (int i = 0; i < cantidadArcos(v); ++i) {
				int vecino = obtenerVerticeLlegada(v, i);
				if (!visitado[vecino]) {
					if (dfs(vecino)) return true;
				}
				else if (enCamino[vecino]) {
					auto it = find(camino.begin(), camino.end(), vecino);
					for (; it != camino.end(); ++it)
						ciclo.push_back(obtenerVertice(*it));
					ciclo.push_back(obtenerVertice(vecino));
					return true;
				}
			}
			enCamino[v] = false;
			camino.pop_back();
			return false;
			};

		for (int i = 0; i < n; ++i) {
			if (!visitado[i]) {
				if (dfs(i)) break;
			}
		}
		return ciclo;
	}

	int caminosMinimosDesde(int inicio) {
		int n = vertices->size();
		vector<bool> visitado(n, false);
		int aristas = 0;

		function<void(int)> dfs = [&](int v) {
			visitado[v] = true;
			for (int i = 0; i < cantidadArcos(v); ++i) {
				int vecino = obtenerVerticeLlegada(v, i);
				if (!visitado[vecino]) {
					aristas++;
					dfs(vecino);
				}
			}
			};

		dfs(inicio);
		return aristas;
	}
};

#endif // __GRAFO_H__
