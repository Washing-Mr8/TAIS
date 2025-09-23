
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

Para resolver el problema necesitamos varias colas de prioridad de minimos ordenadas en funcion del orden en el que estan colocados los comics. Cada
comic tiene un id que tomaremos en cuenta para saber cual elegir en caso de que tengan el mismo orden. Aprovechamos la lectura de datos de entrada para 
averiguar de una vez cual es el mejor comic , que es el que tenga menor id (esto puede suponer un coste de O(M log N) debido a que M colas y ademas
tenemos que insertar N comics en cada cola con su respectiva prioridad).

Una vez tenemos todas las colas ordenadas, miraremos el elemento mas priotario de las M colas y nos quedaremos con el menor, eliminandolo y aumentando en 1
el turno que nos toca esperar. Seguiremos haciendo esto hasta que encontremos el mejor ejemplar dando por finalizado el problema

COSTE: los datos de entrada como dijimos anteriormente escalan a O(M log N), y como tenemos que obtener el top de cada cola para saber cual tenemos que elegir,
recorremos M veces la cola de tamaño N, que como no siempre la recorremos al completo el coste es logN.

En resumen el coste de resolver el problema omitiendo la entrada es de -> O(M log N)

COSTE EN ESPACIO ADICIONAL: O(M log N) siendo M el numero de colas y N la cantidad de comics en cada cola

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
			pilas[i].push({ id, k });
			if (id < mejor_ejemplar) {
				mejor_ejemplar = id;
			}
			k--;
		}

	}

	// escribir la solución

	bool encontrado = false;
	int turno = 1;
	
	while (!encontrado) {
		int menor_index = 0, ultimo_comprado = 100000000;
		for (int i = 0; i < N; i++) {
			auto comic = pilas[i].top();
			if (comic.id < ultimo_comprado) {
				ultimo_comprado = comic.id;
				menor_index = i;
			}
		}
		auto comic = pilas[menor_index].top();
		//cout << "ID: " << comic.id << " orden: " << comic.orden << ", ";
		pilas[menor_index].pop();
		if (comic.id == mejor_ejemplar) {
			encontrado = true;
			//cout << "\n";
		}
		else {
			turno++;
		}
	}
	
	//DEBUG
	/*
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
	
	*/
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
