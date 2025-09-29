
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

Para resolver el problema necesitamos usar 2 colas de prioridad de maximos que representen las 2 cajas de pilas (de 9 voltios y 1,5 voltios). Tras leer los
datos de entrada, necesitamos iterar "A" o "B" veces, siendo "A" el tamaño de la cola con las pilas de 9v y "B" el de la cola de 1,5v. Dependiendo del numero
de Drones que volamos (N), sumaremos en una variable sabado, las horas que proporcionan las pilas por cada N drones. Ademas tambien tenemos que almacenar las 
pilas sobrantes al final del dia para utilizarlas el siguiente sabado.

COSTE: cada push y pop tiene coste logaritmico, y omitiendo los datos de entrada, el coste en el caso peor serian las iteraciones sobre el tamaño de la cola de 
prioridad mas pequeña (porque dejamos de iterar cuando una se quede vacia), con un coste logaritmico por las operaciones push y pop de ambas colas.

O( min(A,B) log(A+B))

COSTE ADICIONAL EN ESPACIO: usamos 2 colas de prioridad con 2 tamaños distintos. A para el numero de pilas en la caja de 9v y B para el numero de pilas de la 
caja B -> O(A+B)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int N = 0, A = 0, B = 0;

	cin >> N >> A >> B;
	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	priority_queue<int> caja_9v;
	priority_queue<int> caja_1_5v;

	int pila = 0;
	//leemos las pilas de 9v
	for (int i = 0; i < A; i++) {
		cin >> pila;
		caja_9v.push(pila);
	}
	//leemos las pilas de 1,5v
	for (int i = 0; i < B; i++) {
		cin >> pila;
		caja_1_5v.push(pila);
	}
	// escribir la solución
	vector<pair<int, int>> pilas_usadas;

	while (!caja_9v.empty() && !caja_1_5v.empty()) {
		int sabado = 0;
		int i = 0;

		//usamos las pilas de caja un sabado
		while (i < N && !caja_9v.empty() && !caja_1_5v.empty()) {
			int pilaA , pilaB;
			i++;
			pilaA = caja_9v.top(); caja_9v.pop();
			pilaB = caja_1_5v.top(); caja_1_5v.pop();

			sabado += min(pilaA, pilaB);

			pilas_usadas.push_back({ pilaA - pilaB, pilaB - pilaA });		
		}
		//mostramos cuantas horas han volado ese dia
		cout << sabado << " "; 

		//volvemos a añadir las pilas que aun sirven
		while (!pilas_usadas.empty()) {
			auto pilas = pilas_usadas.back();
			if (pilas.first > 0) {
				caja_9v.push(pilas.first);
			}
			if (pilas.second > 0) {
				caja_1_5v.push(pilas.second);
			}
			pilas_usadas.pop_back();
		}

	}
	cout << "\n";

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("3_4.in");
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
