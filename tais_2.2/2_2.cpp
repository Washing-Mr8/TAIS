
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

Para resolver el problema necesitamos crear una estructura de datos para los registros con un struct. 

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct registro {
	int momento;
	long long int id;
	int periodo;
};

bool operator <(registro const &a, registro const &b) {
	return a.momento < b.momento || (a.momento == b.momento && a.id < b.id);
}

bool operator >(registro const& a, registro const& b) {
	return b < a;
}

bool resuelveCaso() {
	// leer los datos de la entrada
	int n = 0; cin >> n;

	if (n == 0)  // fin de la entrada
		return false;
	// resolver el caso posiblemente llamando a otras funciones

	priority_queue<registro, vector<registro>, greater<registro>> cola;

	for (int i = 0; i < n; ++i) {
		long long int id_usu;
		int periodo;
		cin >> id_usu >> periodo;
		cola.push({ periodo, id_usu, periodo });
	}

	int envios; // número de envíos a mostrar
	cin >> envios;
	while (envios--) {
		auto e = cola.top(); cola.pop();
		cout << e.id << '\n';
		e.momento += e.periodo;
		cola.push(e);
	}
	cout << "---\n";

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("2_2.in");
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
