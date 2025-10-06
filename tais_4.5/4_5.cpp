
/*@ <authors>
 *
 * E42 Washington Morocho Lema
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
using namespace std;


/*@ <answer>

 El problema se resuelve modelando las relaciones entre actores y peliculas como un grafo bipartito. Los nodos representan actores y peliculas. 
 Un actor esta conectado a todas las peliculas en las que ha participado, y viceversa. Para calcular el numero de Bacon de cada actor, realizamos 
 un BFS desde Kevin Bacon. El numero de Bacon es la mitad de la distancia en el grafo (ya que pasamos por peliculas y actores alternadamente).

 COSTE: O(V + A) donde V es el número total de actores y películas, y A son las conexiones entre ellos.

 COSTE EN ESPACIO ADICIONAL: O(V + A) donde V es el número total de actores y películas, y A son las conexiones entre ellos.

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class NumerosBacon {
private:
    unordered_map<string, vector<string>> grafo;
    unordered_map<string, int> distancias;

    void bfs(const string& inicio) {
        if (grafo.find(inicio) == grafo.end()) return;

        queue<string> q;
        q.push(inicio);
        distancias[inicio] = 0;

        while (!q.empty()) {
            string actual = q.front();
            q.pop();
            int dist_actual = distancias[actual];

            for (const string& vecino : grafo[actual]) {
                if (distancias.find(vecino) == distancias.end()) {
                    distancias[vecino] = dist_actual + 1;
                    q.push(vecino);
                }
            }
        }
    }

public:
    void agregarPelicula(const string& pelicula, const vector<string>& actores) {
        for (const string& actor : actores) {
            grafo[pelicula].push_back(actor);
            grafo[actor].push_back(pelicula);
        }
    }

    void calcularDistancias() {
        distancias.clear();
        bfs("KevinBacon");
    }

    int obtenerNumeroBacon(const string& actor) {
        if (distancias.find(actor) == distancias.end()) {
            return -1; // INF
        }
        return distancias[actor] / 2;
    }
};

bool resuelveCaso() {
    int P; cin >> P;
    if (!cin) return false;

    NumerosBacon calculadora;

    // leemos las  peliculas y la añadimos al grafo
    for (int i = 0; i < P; ++i) {
        string pelicula;
        int numActores;
        cin >> pelicula >> numActores;

        vector<string> actores(numActores);
        for (int j = 0; j < numActores; ++j) {
            cin >> actores[j];
        }

        calculadora.agregarPelicula(pelicula, actores);
    }

    calculadora.calcularDistancias(); //calculamos las distancias con bfs

    int N;
    cin >> N;
    vector<string> consultas(N);
    for (int i = 0; i < N; ++i) {
        cin >> consultas[i];
    }

    // procesamos consultas
    for (const string& actor : consultas) {

        int bacon = calculadora.obtenerNumeroBacon(actor);

        if (bacon == -1) {
            cout << actor << " " << "INF\n";
        }
        else {
            cout << actor << " " << bacon << "\n";
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
	std::ifstream in("4_5.in");
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