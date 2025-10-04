
/*@ <authors>
 *
 * E42 Washington Morocho Lema
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Grafo.h"

using namespace std;


/*@ <answer>

Para resolver el problema necesitamos averiguar la maxima componente conexa, es decir, el subgrafo con mayor numero de aristas. leemos la entrada para crear
el grafo manualmente y luego lo recorremos en profundidad para cada vertice para hayar la maxima componente. 

COSTE: recorrido en profundidad de cada vertice V y arista A en el caso peor -> O(V+A)

COSTE EN ESPACIO ADICIONAL: el numero de vertives y aristas -> O(V+A)

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

class MaximaComponenteConexa {
private:
	vector<bool>visit;
	int maximo;

	int dfs(const Grafo& g, int v) {
		visit[v] = true;
		int cont = 1;
		for (int w : g.ady(v)) {
			if (!visit[w]) {
				cont += dfs(g, w);
			}
		}
		return cont;
	}

public:
	//inicializamos la clase con los atributos deseados para nuestras variables de clase (las privadas)
	MaximaComponenteConexa(const Grafo& g) : visit(g.V(),false) ,maximo(0){
		for (int v = 0; v < g.V(); v++) {
			if (!visit[v]) {
				int cont = dfs(g,v);
				maximo = max(maximo, cont);
			}
		}
	}

	int maxAmigos() {
		return maximo;
	}
};

void resuelveCaso() {
	// leer los datos de la entrada
	int N = 0, M = 0;

	cin >> N >> M;
	Grafo grafo(N);

	int v1 = 0, v2 = 0;

	for (int i = 0; i < M; i++) {
		cin >> v1 >> v2;
		grafo.ponArista(--v1, --v2);
	}
	// resolver el caso posiblemente llamando a otras funciones
	MaximaComponenteConexa amigos(grafo);

	cout << amigos.maxAmigos() << "\n";
}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("4_3.in");
	if (!in.is_open())
		cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
	auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	cin.rdbuf(cinbuf);
#endif
	return 0;
}

