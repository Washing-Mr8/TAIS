
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

Para resolver el problema necesitamos buscar el arbol de recubrimiento minimo en un grafo valorado para encontrar el camino con coste minimo entre todas las 
ciudades y asi quedarnos con el la autonomia del mayor tramo. Tras leer los datos de entrada, utilizamos el algortimo de Kruskal para encontrar el arbol ARM 
con el coste minimo y de paso comprobar si el grafo es conexo, es decir, que todas las ciudades sean accesibles desde cualquier otra. En caso de que no sea
conexo, entonces el coche no tendra una autonomia optima (imposible)

COSTE: utilizamos el arlgoritmo de Kruskal para encontrar el Arbol de Recubrimiento Minimo y quedarnos con la arista con mayor valor en caso de ser conexo.
O(MlogM) siendo M el numero de carreteras entre las ciudades

COSTE EN ESPACIO ADICIONAL: O(N + M) siendo N el numero de ciudades y M las carreteras entre ellas

@ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class ARM_Kruskal {
private:
    int coste;
    bool conexo;
public:
    ARM_Kruskal(GrafoValorado<int> const& g) : coste(0), conexo(false) {
        int cont = 0;
        PriorityQueue<Arista<int>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                cont++;
                coste = max(coste, a.valor());
                if (cont == g.V()) { //miramos el ultimo 
                    break;
                }
            }
        }

        if (cjtos.cardinal(0) == g.V()) { //si el arbol tiene todos los nodos
            conexo = true;
        }


    }

    int costeARM() const { return coste; }

    bool esConexo() { return conexo; }
};

bool resuelveCaso() {
    int N = 0, M = 0; cin >> N >> M;
    if (!cin) return false;

    GrafoValorado<int> gv(N);
    int v1 = 0, v2 = 0, valor = 0;

    for (int i = 0; i < M; i++) {
        cin >> v1 >> v2 >> valor;

        gv.ponArista({ v1 - 1, v2 - 1, valor });
    }

    ARM_Kruskal autonomia(gv);

    if (autonomia.esConexo()) {
        cout << autonomia.costeARM();
    }
    else {
        cout << "Imposible";
    }

    cout << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("6_4.in");
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