
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

Para resolver el problema necesitamos realizar un recorrido en profundidad del grafo no dirido. Usamos un vector para los colores en las posiciones de los 
vertices, siendo -1 si no tiene color o, 0 y 1 para los 2 colores existentes. Si el vertice no esta coloreado entonces lo pintamos de uno (en este caso el
primero es 0), y luego vamos comprobando sus adyacentes para ver si no estan pintados del mismo color, o si estan sin pintar les asignamos el opuesto (1).

Si en algun caso algun vertice adyacente tiene el mismo color que el vertice actual, la busqueda termina y el grafo no es bipartito

COSTE: recorrido en profundidad de cada vertice V y arista A en el caso peor -> O(V+A) 

COSTE EN ESPACIO ADICIONAL: el numero de vertives y aristas -> O(V+A)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class GrafoBipartito {
private:
	vector<int>color;
	bool bipartito;

	bool dfs(const Grafo& g, int v, int c) {
		color[v] = c;
		// w es el vertice adyacente al que estamos actualmente 
		for (int w : g.ady(v)) { 
			if (color[w] == -1) { // si el vertice no esta visitado lo pintamos del color opuesto
				if (!dfs(g, w, 1 - c)) {
					return false;
				}
			}
			else if (color[w] == color[v]) { // si es del mismo color entonces no es bipartito
				return false;
			}
		}

		return true;
	}

public:
	//inicializamos la clase con los atributos deseados para nuestras variables de clase (las privadas)
	GrafoBipartito(const Grafo& g) : bipartito(true), color(vector<int>(g.V(), -1)) {
		for (int v = 0; v < g.V() && bipartito; v++) {
			if (color[v] == -1) {
				bipartito = dfs(g, v, 0);
			}
		}
	}

	bool esBipartito() {
		return bipartito;
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	Grafo grafo(cin);

	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	GrafoBipartito gLibre(grafo);
	bool bipartito = gLibre.esBipartito();

	if (bipartito) {
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
	std::ifstream in("4_2.in");
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
