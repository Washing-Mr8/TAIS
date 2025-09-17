
/*@ <authors>
 *
 * Washington Morocho Lema E42
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;


/*@ <answer>

 Para resolver el problema necesitamos utilizar una cola de prioridad creaciente para tener los 2 valores mas pequeños al principio de la cola.
 Una vez hecho esto iremos sumando los dos primeros valores, borrandolos de la cola y posteriormente añadiendo el resultado de nuevo a la cola.
 Esto hace que el coste del problema a resolver sea lineal debido a que recorremos N-1 veces la cola (se quita uno porque la suma de los 2 valores
 sustituye a esos 2 valores al final de la cola)

 COSTE: las operaciones pop y top son constantes O(1), pero push es O(logN). Debido a que recorremos N - 1 veces la cola, y en cada iteracion
 añadimos el resultado de la suma con push, el coste total sería del orden -> O(NlogN) siendo N el numero de valores a sumar;

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>



bool resuelveCaso() {
	// leer los datos de la entrada
	int n; 
	cin >> n;

	if (n == 0)
		return false;
	// resolver el caso posiblemente llamando a otras funciones
	priority_queue<long long int, vector<long long int>, greater<long long int>> sumas;

	for (int i = 0; i < n; i++) {
		int value;
		cin >> value;

		sumas.push(value);
	}
	// Hay que sumar los dos primeros valores de la cola y luego añadirlo al final, no hace falta una funcion externa
	long long int esfuerzo = 0, resultado = 0;

	for (int i = 0; i < n - 1; i++) {
		long long int primero = sumas.top();
		sumas.pop();
		long long int segundo = sumas.top();
		sumas.pop();
		esfuerzo += primero + segundo;
		sumas.push(esfuerzo);
		resultado += esfuerzo;
		esfuerzo = 0;
	}

	cout << resultado << "\n";

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("2_1.in");
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
