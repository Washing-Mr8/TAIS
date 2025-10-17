
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
using namespace std;


/*@ <answer>
Para resolver el problema necesitamos usar un grafo valorado para saber por que camino los camiones de reparto pueden pasar. Leemos la entrada e insertamos 
cada arista en el grafo para saber que anchura tiene cada camino. Para cada consulta realizamos un recorrido en profundidad DFS para ver si el el grafo es 
conexo, es decir que se puede ir desde el origen hasta el final; y ademas cada vez que llegamos a un vertice no visitado nos aseguramos que la anchura del
camino sea lo suficientemente grande para que el camion pueda pasar.

COSTE: Realizamos un recorrido en profundidad para buscar si el destino es alcanzable ->  O(V + E) siendo V el numero de intersecciones y E las calles entre ellas 

COSTE EN ESPACIO ADICIONAL: O(V + E) ssiendo V el numero de intersecciones y E las calles entre ellas 

@ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Reparto {
private:
    vector<bool> visit;
    bool hayCamino;
    
    void dfs(GrafoValorado<int> const& G, int v, int destino, int umbral) {
        visit[v] = true;
        for (auto a : G.ady(v)) {
            if (a.valor() >= umbral) {
                int w = a.otro(v);
                if (w == destino) {
                    hayCamino = true;
                }
                else {
                    if (!visit[w])
                        dfs(G, w, destino, umbral);
                }
            }
        }
    } 

public:
    Reparto(GrafoValorado<int> const& gv, int origen, int destino, int ancho) : visit(gv.V(),false), hayCamino(false) {
        dfs(gv, origen, destino, ancho);
    }

    bool posible() { return hayCamino; }
};

bool resuelveCaso() {
    int V = 0, A = 0; cin >> V >> A;
    if (!cin) return false;

    GrafoValorado<int> gv(V);
    int v1 = 0, v2 = 0, valor = 0;

    for (int i = 0; i < A; i++) {
        cin >> v1 >> v2 >> valor;

        gv.ponArista({ v1 - 1, v2 - 1, valor });
    }

    int K = 0, origen = 0, destino = 0;
    cin >> K;

    for (int i = 0; i < K; i++) {
        cin >> origen >> destino >> valor;
        Reparto sol(gv, origen - 1, destino - 1, valor);
        if (sol.posible()) {
            cout << "SI\n";
        }
        else {
            cout << "NO\n";
        }
    }

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("6_2.in");
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