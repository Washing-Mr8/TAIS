
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

Para resolver el problema necesitamos una cola de prioridad de minimos ordenada por el tiempo de inicio de cada tarea. Leemos los datos de entrada, añadiendo
diferentes tipos de tarea en funcion de su numero de elmentos, N para las tareas fijas, y M para las periodicas. Tambien leemos el valor T que es el final
del intervalo que tenemos que comprobar. En el caso de las tareas periodicas tenemos que comprobar cuantas veces se va a repetir, para ello dividimos T entre su
periodo, dandonos asi el numero de veces que se va a repetir (en el caso de que sea una division con resto 0, le restamos 1 porque no va a iterar una vez se
haya acabado).
Una vez añadidas todas las tareas vamos comprobando si no hay alguna tarea que se solapa, mientras hayan tareas en la cola.

COSTE: omitiendo el coste de insertar los datos, cada operacion push y pop es del orden O(logK) siendo K el numero total de tareas. El numero de iteraciones
depende de que tan grande sea T (el tiempo a comprobar) y P (el periodo de las tareas periodicas) y el coste seria ->  O(T/P(logK)). 
Asi que en el caso peor, si todas las tareas son periodicas y tienen periodo = 1 el coste total pasa a ser -> O(TlogK)


COSTE EN ESPACIO ADICIONAL: O(N+M) siendo N las tareas fijas y M las tareas periodicas
 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer

struct tarea {
	int inicio;
	int final;
	int periodo;
	int repeticiones;
};

bool operator < (const tarea& a, const tarea& b) {
	return b.inicio < a.inicio;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N = 0, M = 0, T = 0;
	cin >> N >> M >> T;

	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	priority_queue<tarea> multitarea;
	int ini, fin, periodo;

	//primero leemos las tareas fijas
	for (int i = 0; i < N; i++) {
		cin >> ini >> fin;
		if (ini < T) {
			multitarea.push({ ini,fin,0,0 });
		}
	}

	//luego las tareas periodicas
	for (int i = 0; i < M; i++) {
		cin >> ini >> fin >> periodo;
		if (ini < T) {
			int repeticiones = (T - ini) / periodo;
			if (((T - ini) % periodo) == 0) {
				multitarea.push({ ini, fin, periodo, repeticiones - 1 });
			}
			else {
				multitarea.push({ ini, fin, periodo, repeticiones });
			}
		}
	}

	// escribir la solución
	bool conflicto = false;

	while (!conflicto && multitarea.size() > 1) {
		auto aux = multitarea.top();
		multitarea.pop();

		if (multitarea.top().inicio < aux.final) {
			conflicto = true;
		}

		if (aux.periodo > 0 && aux.repeticiones > 0) {
			multitarea.push({aux.inicio + aux.periodo, aux.final + aux.periodo, aux.periodo, aux.repeticiones - 1 });
		}

	}

	if (conflicto) {
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
	std::ifstream in("3_3.in");
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
