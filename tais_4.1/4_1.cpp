
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

Para resolver el problema necesitamos recorrer en profundidad el grafo para verificar si es conexo y ademas que no contenga ciclos. Revisamos si es conexo en 
cada llamada a dfs, verificando que los vertices adyacentes al actual no se hayan visitado. En caso de que si, si el anterior no es el actual, quiere decir 
que hay otro camino para llegar hasta el invalidando la propiedad conexa del grafo.

COSTE: recorrido en profundidad de cada vertice V y arista A -> O(V+A)

COSTE ADICIONAL EN ESPACIO: el numero de vertives y aristas -> O(V+A)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class GrafoLibre {
private:
	vector<bool> visit;
	vector<int> ant;
	int s;
	int num_visitados;
	bool libre;

	bool dfs(const Grafo& g, int v) {
		visit[v] = true;
		num_visitados++;
		bool conexo = true;
		int i = 0;
		while (conexo && i < g.ady(v).size()) { //exploramos los vertices adyacentes
			int w = g.ady(v)[i]; // w es el vertice adyacente al que estamos actualmente 
			if (visit[w] && ant[v] != w) {
				conexo = false;// si ya esta visitado y no es nuestro anterior, entonces no es conexo
			}
			else if(!visit[w]) { //si no lo hemos visitado, lo añadimos
				ant[w] = v;
				conexo = dfs(g, w);
			}
			i++;
		}
		return conexo;
	}

public:
	//inicializamos la clase con los atributos deseados para nuestras variables de clase (las privadas)
	GrafoLibre(const Grafo& g, int s) : visit(vector<bool>(g.V(), false)), ant(vector<int>(g.V())), s(s), num_visitados(0) {
		libre = dfs(g, s) && num_visitados == g.V();
	}

	bool esLibre() {
		return libre;
	}

};

bool resuelveCaso() {
	// leer los datos de la entrada
	Grafo grafo(cin);

	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	GrafoLibre gLibre(grafo, 0);
	bool libre = gLibre.esLibre();

	if (libre) {
		cout << "SI\n";
	}
	else {
		cout << "NO\n";
	}

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("4_1.in");
	if (!in.is_open())
		std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout << "Pulsa Intro para salir..." << std::flush;
	std::cin.get();
#endif
	return 0;
}
