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

Para resolver el problema necesitamos utilizar un grafo valorado dirigido que simule el laberinto en el que se realizara la busqueda del camino minimo desde 
la salida hasta los posibles ratones alcanzables. Al leer la entrada tenemos que poner las aristas al reves para usar el grafo inverso y ver que vertices son
alcanzables desde el origen (salida S) cumpliendo el limite de tiempo T. Una vez que tenemos el digrafo contruido, usamos el algoritmo de Dijkstra para 
encontrar el camino minimo desde la salida y contamos el numero de ratones que cumplen la condicion de entrar a tiempo (en el vector dist).

COSTE: Realizar la busqueda del camino de Dijkstra tiene un coste de  O(AlogV) (A:aristas, V:vertices). El coste seria: O(N log P) siendo N el numero de 
ratones y P el numero de pasadizos 

COSTE EN ESPACIO ADICIONAL: O(2N + P) siendo N el numero de ratones (un N mas por Dijkstra) y P el numero de pasadizos 

@ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

template <typename Valor>
class MejorCamino {
private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    bool alcanzable;
    bool camMin;
    std::vector<Valor> dist;
    IndexPQ<Valor> pq;
    vector<int> aristas;

    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            aristas[w] = aristas[v] + 1;
            pq.update(w, dist[w]);
        }
        else if (dist[w] == dist[v]+ a.valor() && aristas[v] + 1 < aristas[w]) {
            aristas[w] = aristas[v] + 1;
        }
    }

    void dijkstra(DigrafoValorado<Valor> const& g) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    int bfs(DigrafoValorado<Valor> const& g, int s, int  dest){
        vector<bool> visit(g.V(), false);
        queue<int> q;
        vector<int> d(g.V());
        d[s] = 0;
        visit[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            int cont = 0;
            while (!alcanzable && cont < g.ady(v).size()) {
                int w = g.ady(v)[cont].hasta();

                if (!visit[w]) {
                    d[w] = d[v] + 1; visit[w] = true;
                    q.push(w);
                    if (w == dest) {
                        alcanzable = true;
                    }
                }

                cont++;
            }
            
        }
        return d[dest];
    }


public:
    MejorCamino(DigrafoValorado<Valor> const& g, int orig, int dest) : origen(orig), dist(g.V(), INF), pq(g.V()), aristas(g.V(), 0), alcanzable(false), camMin(false) {
        int minAristas = bfs(g, orig, dest);

        if (alcanzable) {
            dijkstra(g);
            if (minAristas == aristas[dest]) {
                camMin = true;
            }
        }
    }

    bool hayCamino() const { return alcanzable; }

    bool minCamino() const { return camMin; }

    Valor distancia(int v) const { return dist[v]; }
};


bool resuelveCaso() {
    int N = 0, C = 0; cin >> N >> C;
    if (!std::cin) return false;

    DigrafoValorado<int> dgv(N);
    int v1 = 0, v2 = 0, valor = 0;

    for (int i = 0; i < C; i++) {
        cin >> v1 >> v2 >> valor;
        dgv.ponArista({ v1 - 1, v2 - 1, valor });
        dgv.ponArista({ v2 - 1, v1 - 1, valor });
    }

    int K = 0, origen = 0, destino = 0; ; cin >> K;

    for (int i = 0; i < K; i++) {
        cin >> origen >> destino;
        MejorCamino<int> camino(dgv, origen - 1, destino - 1);

        if (camino.hayCamino()) {
            cout << camino.distancia(destino - 1);

            if (camino.minCamino()) {
                cout << " SI\n";
            }
            else {
                cout << " NO\n";
            }
        }
        else {
            cout << "SIN CAMINO\n";
        }
    }

    cout << "---\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("7_5.in");
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