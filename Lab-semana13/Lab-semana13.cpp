#include <vector>
#include <iostream>
#include <algorithm> 
#include <stdexcept> 
using namespace std;

template<class T, T vacio = -1>
class CGrafo {
private:
	class CArco {
	public:
		T info;
		int v; //indice del vertice de llegada
		CArco(int vLlegada, T pInfo) {
			//info = vacio;
			info = pInfo;
			v = vLlegada;
		}
	};
	class CVertice {
	public:
		T info;
		vector<CArco*>* ady; //Lista de adyacencia
		CVertice() {
			info = vacio;
			ady = new vector<CArco*>();
		}
	};
	//Lista de vértices
	vector<CVertice*>* vertices;

	bool dfsTopologico(int u, vector<int>& estados, vector<int>& resultado) {
		estados[u] = 1;  // Mark as visiting

		// Visit all adjacent vertices
		CVertice* vertU = vertices->at(u);
		for (int j = 0; j < vertU->ady->size(); j++) {
			int v = obtenerVerticeLlegada(u, j);
			if (estados[v] == 0) {  // Unvisited
				if (!dfsTopologico(v, estados, resultado))
					return false;
			}
			else if (estados[v] == 1) {  // Cycle detected
				return false;
			}
		}

		estados[u] = 2;  // Mark as visited
		resultado.push_back(u);
		return true;
	}

public:
	CGrafo() {
		vertices = new vector<CVertice*>();
	}

	//Operaciones del Grafo
	int adicionarVertice(T info) {
		CVertice* vert = new CVertice();
		vert->info = info;
		vertices->push_back(vert);
		return vertices->size() - 1;
	}

	int cantidadVertices() {
		return vertices->size();
	}

	T obtenerVertice(int v) {
		return (vertices->at(v))->info;
	}
	void modificarVertice(int v, T info) {
		(vertices->at(v))->info = info;
	}
	//Operaciones del arco
	int adicionarArco(int v, int vLlegada) {
		CVertice* ver = vertices->at(v);
		//Crear el objeto ARCO
		CArco* arc = new CArco(vLlegada, obtenerVertice(vLlegada));
		ver->ady->push_back(arc);
		return ver->ady->size() - 1;
	}

	int cantidadArcos(int v) {
		return (vertices->at(v))->ady->size();
	}

	T obtenerArco(int v, int apos) {
		CVertice* ver = vertices->at(v);
		return (ver->ady->at(apos))->info;
	}

	void modificarArco(int v, int apos, T info) {
		CVertice* ver = vertices->at(v);
		(ver->ady->at(apos))->info = info;
	}

	int obtenerVerticeLlegada(int v, int apos) {
		CVertice* ver = vertices->at(v);
		return (ver->ady->at(apos))->v; //indice del vertice de llegada
	}

	vector<int> ordenTopologico() {
		int n = cantidadVertices();
		vector<int> estados(n, 0);  // 0=unvisited, 1=visiting, 2=visited
		vector<int> resultado;

		for (int i = 0; i < n; i++) {
			if (estados[i] == 0) {
				if (!dfsTopologico(i, estados, resultado)) {
					throw runtime_error("Grafo contiene ciclo");
				}
			}
		}

		reverse(resultado.begin(), resultado.end());
		return resultado;
	}
};

int main() {
	CGrafo<int>* G = new CGrafo<int>();

	// Add vertices and edges (without cycles)
	G->adicionarVertice(2);
	G->adicionarVertice(15);
	G->adicionarVertice(30);
	G->adicionarVertice(7);

	G->adicionarArco(0, 1);
	G->adicionarArco(0, 3);
	G->adicionarArco(1, 2);
	// Remove any cycle: G->adicionarArco(2, 0);

	try {
		vector<int> orden = G->ordenTopologico();
		cout << "Orden topologico (indices): ";
		for (int idx : orden) {
			cout << idx << " ";
		}

		cout << "\nOrden topologico (valores): ";
		for (int idx : orden) {
			cout << G->obtenerVertice(idx) << " ";
		}
		cout << endl;
	}
	catch (const exception& e) {
		cerr << "Error: " << e.what() << endl;
	}

	cin.get();
	return 0;
}