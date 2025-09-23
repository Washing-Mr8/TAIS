
/*@ <authors>
 *
 * E42 Washington Morocho Lema
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;


/*@ <answer>


COSTE: 


COSTE EN ESPACIO ADICIONAL: O(N) siendo N el numero de pacientes a atender

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Comic {
	int id;
	int orden;
};

bool operator <(const Comic& a, const Comic& b) {
	return (b.orden < a.orden) || (b.orden == a.orden && b.id < a.id);

}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N = 0; cin >> N;

	if (!cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones

	vector<priority_queue<Comic>> pilas(N);

	int k = 0, id = 0, mejor_ejemplar = 100000000;
	
	for (int i = 0; i < N; i++) {
		 cin >> k;

		while (k > 0) {
			cin >> id;
			pilas[i].push({id, k});
			if (id < mejor_ejemplar) {
				mejor_ejemplar = id;
			}
			k--;
		}

	}
	
	// escribir la solución

	bool encontrado = false;
	int turno = 1;

	cout << "MEJOR EJEMPLAR: " << mejor_ejemplar << "\n";
	for (int i = 0; i < N; i++) {
		cout << "Pila de comics Numero " << i+1 << ": ";
		while (!pilas[i].empty()) {
			auto comic = pilas[i].top();
			cout << comic.id << ", ";
			pilas[i].pop();
		}
		cout << "\n";
	}


	/*while (!encontrado || !comics.empty()) {
		auto comic = comics.top();
		cout << "ID " << comic.id << " y ORDEN" <<  comic.orden << ", ";
		comics.pop();
		if (comic.id == mejor_ejemplar) {
			encontrado = true;
			cout << "\n";
		}
		else {
			turno++;
		}
	}*/

	cout << turno << "\n";


	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("2_5.in");
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
