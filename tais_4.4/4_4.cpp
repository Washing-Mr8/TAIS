
/*@ <authors>
 *
 * E42 Washington Morocho Lema
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*@ <answer>



COSTE: recorrido en profundidad de cada pixel (matriz) con C columnas y F filas -> O(F*C)

COSTE EN ESPACIO ADICIONAL: el tamaño de la matric con C columnas y F filas -> O(F+C)

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

using Mapa = vector<string>;

class Manchas {
private:
	int F, C;
	vector<vector<bool>> visit; //se ha visitado visit[i][j] = se ha visistado el pixel <i,j>?
	int num;
	int maxim;

	const vector<pair<int, int>> dirs = { {1,0},{0,1},{-1,0},{0,-1} }; //direcciones : derecha, arriba, izquierda, abajo

	bool correcta(int i, int j) const {
		return 0 <= i && i < F && 0 <= j && j < C;
	}

	int dfs(Mapa const& M, int i, int j) {
		visit[i][j] = true;
		int tam = 1;
		for (auto d : dirs) {
			int ni = i + d.first, nj = j + d.second;
			if (correcta(ni, nj) && M[ni][nj] == '#' && !visit[ni][nj]) {
				tam += dfs(M, ni, nj);
			}
		}
		return tam;
	}

public:
	Manchas(Mapa const& M) : F(M.size()), C(M[0].size()), visit(F, vector<bool>(C, false)), num(0), maxim(0) {
		for (int i = 0; i < F; i++) {
			for (int j = 0; j < C; j++) {
				if (!visit[i][j] && M[i][j] == '#') {
					++num;
					int cont = dfs(M, i, j);
					maxim = max(maxim, cont);
				}

			}
		}
	}

	int numero() { return num; }

	int maximo() { return maxim; }
};

bool resuelveCaso() {
	// leer los datos de la entrada
	int F = 0, C = 0;
	cin >> F >> C;

	if (!std::cin)  return false;
	
	Mapa mapa(F);
	//leemos la imagen
	for (string& linea : mapa) {
		cin >> linea; 
	}
	//la analizamos
	Manchas manchas(mapa);
	cout << manchas.numero() << " " << manchas.maximo() << "\n";
	
	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	ifstream in("4_4.in");
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

