
/*@ <authors>
 *
 * E42 Washington Morocho Lema
 * E63 Sergio Vazquez Carbajo
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include "IndexPQ.h"

using namespace std;

/*@ <answer>

Para resolver el problema necesitamos usar 2 colas de prioridad indexadas, una de ellas almacenara los canales siendo mas prioritarios los que tengan mas minutos
de emision, y otra en la que tambien almacenamos los canales, siendo mas prioritarios los que tengan mayor cantidad de audiencia. Mientras vamos iterando, tras
leer el minuto de emision, nos quedamos con el elemento con mayor audiencia y añadimos el intervalo de tiempo que ha tenido en es momento a la otra cola.
Al finalizar, mostraremos los canales con mayor tiempo de emision (este no puede superar D) y en caso de empate los mostraremos de menor a mayor indice

COSTE: cada operacion de las indexPQ son del orden O(logC) siendo C el numero de canales, y tenemos que iterar N veces para ver si algun elemento de la cola se
actualiza, por lo tanto el coste en el caso peor pasa a ser -> O(N log C)

COSTE EN ESPACIO ADICIONAL: O(C) siendo C el numero de canales

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Canal {
	int numero;
	int minutos;
};

class ComparadorCanales{
public:
	bool operator()(const Canal& a, const Canal& b) { 
		return (a.minutos > b.minutos) || (a.minutos == b.minutos && a.numero < b.numero) ;
	}
};

struct Emision {
	int numero;
	int audiencia;
	int hora_emision;
};

class ComparadorEmision {
public:
	bool operator()(const Emision& a, const Emision& b) {
		return (a.audiencia > b.audiencia) || (a.audiencia== b.audiencia && a.numero < b.numero);
	}
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int D = 0, C = 0, N = 0;
	cin >> D >> C >> N;
	if (!cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	IndexPQ<int, Canal, ComparadorCanales> canales;
	IndexPQ<int, Emision, ComparadorEmision> emision;
	Emision em;
	//incializamos los canales
	for (int i = 0; i < C; i++) {
		cin >> em.audiencia;
		em.hora_emision = 0;
		em.numero = i + 1;
		emision.push(em.numero,em);
		canales.push(em.numero,{em.numero,0});
	}
	
	// escribir la solución
	int minuto_anterior = 0;
	for (int i = 0; i < N; i++) {
		int minuto = 0; cin >> minuto;

		int num_canal = 0, audiencia = 0;

		auto prime = emision.top().prioridad;
		auto canal_prime = canales.priority(prime.numero);
		int minutos = canal_prime.minutos + (minuto - minuto_anterior);
		canales.update(prime.numero, { prime.numero, minutos });


		while (num_canal != -1) {
			cin >> num_canal;

			if (num_canal != -1) { // si no es el fin de la entrada actualizamos el canal con la nueva audiencia
				cin >> audiencia;
				
				emision.update(num_canal, {num_canal, audiencia, minuto});
			}
		}
		minuto_anterior = minuto;
	}

	auto ultimo = emision.top().prioridad;

	if (D > ultimo.hora_emision) {
		auto canal = canales.priority(ultimo.numero);
		int ultimos_minutos = canal.minutos + (D - ultimo.hora_emision);
		canales.update(ultimo.numero, { ultimo.numero, ultimos_minutos });
	}


	while (D > 0 && !canales.empty()) {
		auto canal = canales.top().prioridad; 
		canales.pop();
		D -= canal.minutos;
		cout << canal.numero << " " << canal.minutos << "\n";
	}

	cout << "---\n";
	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("1.in");
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
