
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

Para resolver el problema necesitamos usar una cola de prioridad de maximos en funcion de la gravedad que sientan los pacientes. Añadimos 
pacientes conforme vamos leyendo la entrada, teniendo preferencia los que mas dolor sientan y en caso de igualdad, se atendera al que 
mas tiempo haya estado esperando (con una variable que tiene el turno de entrada). Una vez atendidos lo quitamos de la cola y seguimos 
leyendo los datos hasta el fin de la entrada.

COSTE: las operaciones top y pop son constantes O(1) y realizamos N interaciones en funcion del tamaño de los datos de entrada. Mientras
iteramos podemos añadir pacientes a la cola, o lo que es lo mismo, hacemos push con un coste de O(logN).

Por lo tanto el coste total es del orden -> O(NlogN)

COSTE EN ESPACIO ADICIONAL: O(N) siendo N el numero de pacientes a atender

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct paciente {
	string nombre;
	int gravedad;
	int entrada;
};

bool operator<(const paciente& a, const paciente& b ) {
	return (a.gravedad < b.gravedad)||(a.gravedad == b.gravedad && a.entrada > b.entrada);
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N = 0; cin >> N;

	if (N == 0)  // fin de la entrada
		return false;
	
	// resolver el caso posiblemente llamando a otras funciones
	char tipo;
	int gravedad = 0, entrada = 0;
	string nombre;
	priority_queue<paciente> urgencias;

	// escribir la solución
	for (int i = 0; i < N; i++) {
		cin >> tipo;
		if (tipo == 'I') {
			cin >> nombre >> gravedad;
			urgencias.push({nombre,gravedad,entrada});
			entrada++;
		}
		else if (tipo == 'A') {
			auto paciente = urgencias.top();
			urgencias.pop();
			cout << paciente.nombre <<"\n";
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
	std::ifstream in("2_4.in");
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
