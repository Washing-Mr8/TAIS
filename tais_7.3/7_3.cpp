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
#include "DigrafoValorado.h"
#include "IndexPQ.h"
#include <numeric>

using namespace std;

/*@ <answer>

Para resolver el problema necesitamos utilizar un grafo valorado dirigido que simule las calles e intersecciones que recorre Lucas para poder encontrar los
posibles caminos minimo con el algoritmo de Dijsktra. Leemos la entrada e insertamos las aristas en ambas direcciones (de v1 a v2 y de v2 a v1). Una vez 
tenemos el digrafo preparado lo recorremos utilizando Dijkstram, pero mientras relajamos cada arista, comprobamos si la distancia de ese vertice coincide con 
la del otro vertice. En caso de que coincida entonces sumamos 1 posible forma de lleagar hasta ese vertice, y repetimos el preceso hasta llegar al cole (N -1)

COSTE: Realizar la busqueda del camino de Dijkstra tiene un coste de  O(AlogV) (A:aristas, V:vertices). Como las calles son birideccionales el coste seria:
O(N log 2C) -> siendo N el numero de intersecciones, C el numero de calles (*2 por ser bidireccionales)

COSTE EN ESPACIO ADICIONAL: O(N + 2C) siendo N el numero de intersecciones, C el numero de calles (*2 por ser bidireccionales)

@ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Dijkstra {
private:
    const int INF = INT_MAX;
    int origen;
    vector<int> posiblesC;
    std::vector<int> dist;
    IndexPQ<int> pq;

    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
            posiblesC[w] = posiblesC[v];
        }
        else if (dist[w] == dist[v] + a.valor()) {
            posiblesC[w] += posiblesC[v];
        }


    }
public:
    Dijkstra(DigrafoValorado<int> const& g, int orig) : origen(orig), dist(g.V(), INF), pq(g.V()), posiblesC(g.V(),0) {
        dist[origen] = 0;
        posiblesC[origen] = 1;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    bool hayCamino(int v) const { return dist[v] != INF; }

    int distancia(int v) const { return dist[v]; }    

    int podiblesCaminos(int v) { return posiblesC[v]; }
};

bool resuelveCaso() {
    int N = 0; cin >> N;
    if (N == 0) return false;

    int C = 0; cin >> C;
    DigrafoValorado<int> dgv(N);
    int v1 = 0, v2 = 0, valor = 0;

    for (int i = 0; i < C; i++) {
        cin >> v1 >> v2 >> valor;

        dgv.ponArista({ v1 - 1, v2 - 1, valor });
        dgv.ponArista({ v2 - 1, v1 - 1, valor });
    }

    Dijkstra solucion(dgv,0);

    cout << solucion.podiblesCaminos(N - 1) << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("7_3.in");
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