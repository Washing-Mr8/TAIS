
/*@ <authors>
 *
 * Washington Morocho Lema E42
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "TreeSet_AVL.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

Para resolver el problema tenemos que implementar la funcion kesimo en el TAD del arbol AVl (set), añadimos una variable mas al arbol
AVL llamada tam_i, que sera el tamaño del subarbol izquierdo de ese nodo + 1. Con la funcion kesimo_rec recorremos recursivamente por
niveles el arbol en busca del minimo elmento que coincida con k. La funcion recursiva tendria un coste de O(h) siendo h la altura del arbol,
ya que en cada paso descendemos un nivel. Aunque en el caso peor recorreriamos una parte del arbol, pero no en su totalidad -> COSTE: O(logN)

Cada insercion en el arbol es de coste O(logN), asi que a la hora de leer los valores de los nodos tendriamos un coste de O(NlogN). 

El coste total de la funcion seria: el numero total de consultas (M) por el coste de la funcion kesimo (logN) -> O(MlogN)
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int N;
	cin >> N;

	if (N == 0) return false;

	Set<int> conjunto;

	// Insertar N elementos en el conjunto
	for (int i = 0; i < N; ++i) {
		int valor;
		cin >> valor;
		conjunto.insert(valor);
	}

	int M;
	cin >> M;

	// Realizar M consultas kesimo
	for (int i = 0; i < M; ++i) {
		int k;
		cin >> k;

		try {
			int resultado = conjunto.kesimo(k);
			cout << resultado << "\n";
		}
		catch (const out_of_range& e) {
			cout << "??\n";
		}
	}

	cout << "---\n" ;


	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("2.in");
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
