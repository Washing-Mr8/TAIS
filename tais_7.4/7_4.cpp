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
class Dijkstra {
private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist;
    IndexPQ<Valor> pq;

    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }
public:
    Dijkstra(DigrafoValorado<Valor> const& g, int orig, int tiempo) : origen(orig), dist(g.V(), INF), pq(g.V()){
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    int num_ratones(int limite) {
        int ratones = 0;
        //comprobamos a que distancia esta cada vertice
        for (int i = 0; i < dist.size(); i++) {
            if (dist[i] <= limite && i != origen) {
                ratones++;
            }

        }
        return ratones; 
    }
};


bool resuelveCaso() {
    int N = 0, S = 0, T = 0, P = 0; cin >> N >> S >> T >> P;
    if (!std::cin) return false;

    DigrafoValorado<int> dgv(N);
    int v1 = 0, v2 = 0, valor = 0;

    for (int i = 0; i < P; i++) {
        cin >> v1 >> v2 >> valor;
        //ponemos la arista en sentido contrario
        dgv.ponArista({ v2 - 1, v1 - 1, valor });
    }

    Dijkstra<int> laberinto(dgv, S - 1, T);

    cout << laberinto.num_ratones(T) << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("7_4.in");
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