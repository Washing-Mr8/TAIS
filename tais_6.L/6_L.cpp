
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
#include <climits>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"

using namespace std;


/*@ <answer>

Para resolverel prolema necesitamos encontrar el camino minimo entre todos los vertices si es posible. Para ello utilizamos un grafo valorado en el que
realizaremos el algoritmo de Kruskal para encontrar el arbol de recubrimiento minimo. Mientras vamos comprobando las aristas, si el valor de esta es mayor
al coste de construir un aeropuerto, no la añadimos al conjunto de caminos (conjuntos disjuntos). Con esto al final nos quedamos con el presupuesto de construir
las carreteras (coste) y los aeropuertos  (num de conjuntos * coste aeropuerto )

COSTE: utilizamos el arlgoritmo de Kruskal para encontrar el Arbol de Recubrimiento Minimo -> O(MlogM) siendo M el numero de carreteras entre las ciudades

COSTE EN ESPACIO ADICIONAL: O(N + M) siendo N el numero de ciudades y M las carreteras que las conectan

@ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Aeropuertos {
private:
    int coste;
    ConjuntosDisjuntos conjuntos;
    int costeAeropuerto;
public:
    Aeropuertos(GrafoValorado<int> const& g, int u) : coste(0), conjuntos(g.V()), costeAeropuerto(u) {
        int cont = 0;
        PriorityQueue<Arista<int>> pq(g.aristas());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!conjuntos.unidos(v, w) && a.valor() < costeAeropuerto) {
                conjuntos.unir(v, w);
                cont++;
                coste += a.valor();
                if (cont == g.V()) {
                    break;
                }
            }
        }

    }

    int costeTotal() const { return coste + conjuntos.num_cjtos() * costeAeropuerto; }

    int numAeropuertos() { return conjuntos.num_cjtos(); }

};

bool resuelveCaso() {
    int N = 0, M = 0, A =0 ; cin >> N >> M >> A;
    if (!cin) return false;

    GrafoValorado<int> gv(N);
    int v1 = 0, v2 = 0, valor = 0;

    for (int i = 0; i < M; i++) {
        cin >> v1 >> v2 >> valor;

        gv.ponArista({ v1 - 1, v2 - 1, valor });
    }

    Aeropuertos aeropuertos(gv, A);
   

    cout <<aeropuertos.costeTotal() << " " << aeropuertos.numAeropuertos() << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("6_L.in");
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