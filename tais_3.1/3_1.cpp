
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

Para resolver el problema necesitamos utilizar una variable para saber que medio va en el medio, 2 colas de prioriad,; una de maximos en la que almacenaremos
los pajaros de la izquierda (menores que el de en medio) teniendo acceso al mayor de estos, y una cola de minimos en la que almacenaremos los pajaros de la
derecga (mayores al de en medio) teniendo acceso al menor de estos. Conforme leemos las parejas que van entrando a la bandada, comparamos los elementos mas 
prioritarios de ambas colas con el medio de en medio y realizamos los cambios necesarios para actualizar la solucion

COSTE: Realizamos N iteraciones, siendo N el numeor de pajaros, y como trabajamos con 2 colas, cada push cuesta O(logN/2), asi que juntando ambas el coste 
queda en O(logN). Coste total -> O(NlogN)

COSTE EN ESPACIO ADICIONAL: O(N)-> porque a pesar de usar 2 colas de prioridad y una variable para el medio de en medio, todas estas suman N, que es el numero 
total de pajaros

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {
	// leer los datos de la entrada
	int medio = 0, parejas = 0;

	cin >> medio >> parejas;
	if (medio == 0 && parejas == 0)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	priority_queue<int> menores;
	priority_queue<int,vector<int>, greater<int>> mayores;
	int pajaro = 0;

	// escribir la solución
	for (int i = 0; i < parejas*2; i++) {
		cin >> pajaro;
		if (pajaro < medio) {
			menores.push(pajaro);
			if (menores.size() > mayores.size()) { // si la el lado izquierdo es mayor lo equilibramos
				mayores.push(medio);
				medio = menores.top();
				menores.pop();
			}
		}
		else {
			mayores.push(pajaro);
			if (mayores.size() > menores.size()) {
				menores.push(medio);
				medio = mayores.top();
				mayores.pop();
			}
		}

		if (i % 2 == 1) {
			cout << medio << " ";
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
	std::ifstream in("3_1.in");
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
