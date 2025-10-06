
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
#include "Grafo.h"
using namespace std;


/*@ <answer>


 COSTE: O(V + A) donde V es el número total de personas, y A son las conexiones entre ellos.

 COSTE EN ESPACIO ADICIONAL: O(V + A) donde V es el número total de personas, y A son las conexiones entre ellos.

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class ComponentesConexas {
private:
    vector<bool> visit; //visit[v] = se ha visitado el vertice v?
    vector<int> componente; //componente[v] = num de componente a la que pertenece el vertice v
    vector<int> tam_comp; // tam_comp[i] = tamaño de la componetne conexa i


    int dfs(Grafo const& g, int v) {
        visit[v] = true;
        componente[v] = tam_comp.size();
        int tam = 1;
        for (int w : g.ady(v)) {
            if (!visit[w]) {
                tam += dfs(g, w);
            }
        }
        return tam;
    }

public:
    ComponentesConexas(Grafo const& g):visit(g.V(),false), componente(g.V()) {
        for (auto v = 0; v < g.V(); v++) {
            if (!visit[v]) { //se recorre la nueva componente conexa
                int tam = dfs(g, v);
                tam_comp.push_back(tam);
            }
        }
    }

    int tam_comp_v(int v) { // tamaño de la componente a la que pertence v
        return tam_comp[componente[v]];
    }

};

bool resuelveCaso() {
    int N = 0, M = 0; cin >> N >> M;
    if (!cin) return false;

    Grafo g(N);

    for (int i = 0; i < M; i++) {
        int T; cin >> T;
        if (T > 0) {
            int uno;
            cin >> uno;
            int otro;
            for (int j = 1; j < T; j++){
                cin >> otro;
                g.ponArista(uno - 1, otro - 1);
                uno = otro;
            }
        }
    }

    ComponentesConexas cg(g);

    cout << cg.tam_comp_v(0);
    for (int i = 1; i < N; i++) {
        cout << ' ' << cg.tam_comp_v(i) ;
    }
    cout << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("4_6.in");
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