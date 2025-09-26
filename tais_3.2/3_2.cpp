
/*@ <authors>
 *
 * E42 Washington Morocho Lema
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include "IndexPQ.h"

using namespace std;

/*@ <answer>

Para resolver el problema necesitamos modificar el TAD de colas de priopridad con prioridad variable. En indexPQ modificamos el elemento elem para hacerlo 
generico añadiendo el typenamde K en la plantilla. Al hacerlo un generico K, necesitamos cambiar el array de posiciones a un unordered_map para que almacene
cualquier elemento de tipo K. Una vez modificada declaramos un indexPQ con un string y una estructura que almacena los votos y el nombre del pais, para 
compararlos y que en caso de igualdad haya desempate por los strings. A su vez le pasamos el comparador con la estructura anterior, y con ello solo quedaria
leer los datos para que en cada iteracion y lectura actualicemos la cola atendiendo a los diferentes elementos (si ya esta insertado o no) y actualizando
o insertando los datos

COSTE: el coste de cada push o update es de O(logN), e iteramos para leer los datos E veces, siendo E el numero de eventos, y la cola tiene una tamaño de 
P paises, asi que en el caso peor el coste total ascenderia a -> O(ElogP)

COSTE EN ESPACIO ADICIONAL: O(P), siendo P el numero de paises

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Pais {
	string nombre;
	int votos;
};

class ComparadorPaises {
public:
	bool operator()(const Pais& a, const Pais& b){
		if (a.votos != b.votos) {
			return a.votos > b.votos;
		}
		else {
			return a.nombre < b.nombre;
		}
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int N = 0;
	cin >> N;
	if (!cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	IndexPQ<string, Pais, ComparadorPaises> eurovision;
	Pais pais;
	// escribir la solución

	for(int i = 0 ; i < N; i++){
		cin >> pais.nombre;

		if (pais.nombre == "?") {
			auto pais = eurovision.top().prioridad;
			cout << pais.nombre << " " << pais.votos << "\n";
		}
		else {
			cin >> pais.votos;
			//si el pais ya esta en la cola lo actualizamos
			try {
				auto aux = eurovision.priority(pais.nombre);
				aux.votos += pais.votos;

				eurovision.update(pais.nombre, aux);
			}
			catch (exception e) {
				//cout << e.what();
				eurovision.push(pais.nombre, pais);
			}
		}
	}

	cout << "---\n";
	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("3_2.in");
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
