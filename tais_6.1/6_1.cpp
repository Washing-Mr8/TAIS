
/*@ <authors>
 *
 * E42 Washington Morocho Lema
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

#include "ConjuntosDisjuntos.h"
using namespace std;

/*@ <answer>



COSTE: recorrido en profundidad de cada pixel (matriz) con C columnas y F filas -> O(F*C)

COSTE EN ESPACIO ADICIONAL: el tamaño de la matric con C columnas y F filas -> O(F+C)

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

using Fotografia = vector<string>;
using dir = pair<int, int>;
using elem = pair<int, int>;


class MaxConjuntos {
private:
	int F, C;
	vector<vector<bool>> visit; //se ha visitado visit[i][j] = se ha visistado el pixel <i,j>?
	Fotografia f;
	ConjuntosDisjuntos mar;
	int tamMax;

	const vector<pair<int, int>> dirs = { {1,0},{0,1},{-1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1} }; //direcciones : derecha, arriba, izquierda, abajo

	bool correcta(int i, int j) const {
		return 0 <= i && i < F && 0 <= j && j < C;
	}

	int num_elem(int i, int j) {
		return i * C + j;
	}

	void comprobarUniones(int i, int j) {
		pair<int, int> sig;
		for (auto d : dirs) {
			sig.first = i + d.first;
			sig.second = j + d.second;
			if (correcta(sig.first, sig.second) && f[sig.first][sig.second] == '#'&& !mar.unidos(num_elem(i,j), num_elem(sig.first, sig.second))) {
				mar.unir(num_elem(i, j), num_elem(sig.first, sig.second));
			}
		}
		tamMax = max(tamMax, mar.cardinal(num_elem(i, j)));
	}

public:
	MaxConjuntos(int F, int C, Fotografia const& f) : F(F), C(C), f(f), tamMax(0), mar(ConjuntosDisjuntos(F*C)) {
		for (int i = 0; i < F; i++) {
			for (int j = 0; j < C; j++) {
				if (f[i][j] == '#'){
					comprobarUniones(i, j);
				}
			}
		}
	}

	void addMancha(pair<int,int> mancha) {
		f[mancha.first][mancha.second] = '#';
		comprobarUniones(mancha.first, mancha.second);
	}
	
	int maximo() { return tamMax; }
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int F = 0, C = 0;
	cin >> F >> C;

	if (!std::cin)  return false;

	Fotografia foto(F);
	//leemos la imagen
	for (string& linea : foto) {
		cin >> linea;
	}
	//la analizamos
	MaxConjuntos sol(F, C, foto);

	cout << sol.maximo();

	int N = 0, x = 0, y = 0; cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> x >> y;
		sol.addMancha({ x - 1,y - 1 });
		cout << " " << sol.maximo();
	}

	cout << "\n";
	
	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("6_1.in");
	if (!in.is_open())
		cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
	auto cinbuf = cin.rdbuf(in.rdbuf());
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

