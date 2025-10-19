
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

Para resolver el problema necesitamos buscar el arbol de recubrimiento minimo en un grafo valorado para encontrar el camino con coste minimo para los puentes.
Tras leer los datos de entrada, utilizamos el algortimo de Kruskal para encontrar el arbol ARM con el coste minimo y de paso comprobar si el grafo es conexo, 
es decir, que todas las islas sean accesibles desde cualquier otra. 

COSTE: utilizamos el arlgoritmo de Kruskal para encontrar el Arbol de Recubrimiento Minimo -> O(PlogP) siendo P el numero de puentes entre las islas

COSTE EN ESPACIO ADICIONAL: O(I + P) siendo I el numero de islas y P los posibles puentes entre ellas

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
                coste += a.valor();
                if (cont == g.V()) { 
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
    int I = 0, P = 0; cin >> I >> P;
    if (!cin) return false;

    GrafoValorado<int> gv(I);
    int v1 = 0, v2 = 0, valor = 0;

    for (int i = 0; i < P; i++) {
        cin >> v1 >> v2 >> valor;

        gv.ponArista({ v1 - 1, v2 - 1, valor });
    }

    ARM_Kruskal puentes(gv);

    if (puentes.esConexo()) {
        cout << puentes.costeARM(); 
    }
    else {
        cout << "No hay puentes suficientes";
    }

    cout << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("6_3.in");
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