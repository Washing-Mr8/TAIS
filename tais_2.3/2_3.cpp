
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

Para resolver el problema necesitamos crear una estructura "caja" que almacena el numero de su caja (hasta N) y el tiempo de espera que lleva
esa caja; y una cola de prioridad de minimos de la estructura caja. Se ordenara de menor a mayor en funcion del tiempo de espera y en caso
de que sean iguales se elegira el que tenga menor numero de caja. 
Inicializaremos las cajas con tiempo 0 para luego añadir los tiempos de los clientes a la cola en el momento que leamos los valores. Una vez 
hayamos terminado con todos los clientes podremos obtener como solucion la caja mas prioitaria (con menor tiempo de espera) 

COSTE: el coste de realizar pop() y top() es lineal O(1),e insertar un elemento en una cola de prioridad es de O(logN), por ello como iteramos
C veces (C es el numero de clientes) el coste total es de ->O(C logN) 

En realidad es O(N log N + C log N)

Coste en espacio adicional : O(N) por el tamaño de la cola de prioridad

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct caja {
	int num_caja; //numero de la caja de tamaño N
	int espera; //tiempo de espera de la caja
};

//comparador < para nuestra estructura caja. 
bool operator <(const caja &c1, const caja &c2) {
	return c2.espera < c1.espera || c2.espera == c1.espera && c2.num_caja < c1.num_caja;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int N = 0, C = 0;

	cin >> N >> C;
	if (N == 0 && C == 0)  // fin de la entrada
		return false;
	// resolver el caso posiblemente llamando a otras funciones

	priority_queue<caja> tienda;
	
	for (int i = 0 ; i < N; i++) { //inicializamos las cajas
		tienda.push({i + 1, 0});
	}
	// escribir la solución
	int  segundos = 0;
	for (int i = 0; i < C; i++) {
		cin >> segundos;
		caja caja = tienda.top();
		tienda.pop();
		caja.espera += segundos;
		tienda.push(caja);
	}

	int sol = tienda.top().num_caja;

	cout << sol << "\n";
	
	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("2_3.in");
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
