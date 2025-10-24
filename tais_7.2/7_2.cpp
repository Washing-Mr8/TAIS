
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

Para resolver el problema necesitamos utilizar un grafo dirifido valorado para poder encontrar los caminos minimos desde un vertice a otro. Tras inicializar
el grafo, tenemos que añadir aristas birideccionales, ya que son calles y se puede de un sitio a otro y viceversa. Leemos las K consultas en las que en cada
iteracion realizamos el algoritmo de DijKstra para encontrar el camino minimo (si es posible) desde un origen y destino dado. En caso de que sea posible,
usamos nuestra funcion Camino para reconstruir el trayecto entre ese par de vertices, usando un cola doble que usaremos para almacenar los vertices visitados
retrocediendo desde el destino hasta llegar al origen.

COSTE: Realizar la busqueda del camino de Dijkstra tiene un coste de  O(AlogV) (A:aristas, V:vertices), y la fucion para recorrer el camino tiene un coste
lineal O(V) en el caso peor (en caso de recorrer todos los vertices). Como realizamos ambas operaciones un numero K de consultas, el coste total seria:
O(K ((2*C log N) + N)) siendo N el numero de intersecciones, C el numero de calles (*2 por ser bidireccionales) y K el numero de consultas a realizar

COSTE EN ESPACIO ADICIONAL: O(2N + 2C) siendo N el numero de intersecciones (y una N mas por Dijkstra), C el numero de calles (*2 por ser bidireccionales)

@ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Dijkstra {
private:
    const int INF = INT_MAX;
    int origen;
    vector<int> t_carga;
    std::vector<int> dist;
    std::vector<AristaDirigida<int>> ulti;
    IndexPQ<int> pq;

    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor() + t_carga[w]) {
            dist[w] = dist[v] + a.valor() + t_carga[w]; ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }
public:
    Dijkstra(DigrafoValorado<int> const& g, int orig, vector<int> const& t_carga) : origen(orig), dist(g.V(), INF), ulti(g.V()), pq(g.V()), t_carga(t_carga) {
        dist[origen] = t_carga[0];
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    bool hayCamino(int v) const { return dist[v] != INF; }

    int distancia(int v) const { return dist[v]; }    
};

bool resuelveCaso() {
    int N = 0; cin >> N;
    if (N == 0) return false;

    int tiempo = 0;
    vector<int> t_carga(N);
    for (int i = 0; i < N; i++) {
        cin >> tiempo;
        t_carga[i] = tiempo;
    }

    int C = 0; cin >> C;
    DigrafoValorado<int> dgv(N);
    int v1 = 0, v2 = 0, valor = 0;

    for (int i = 0; i < C; i++) {
        cin >> v1 >> v2 >> valor;

        dgv.ponArista({ v1 - 1, v2 - 1, valor });
    }

    Dijkstra solucion(dgv,0, t_carga);

    if (solucion.hayCamino(N-1)) {

        cout << solucion.distancia(N-1)  << "\n";
    }
    else {
        cout << "IMPOSIBLE\n";
    }


    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("7_2.in");
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