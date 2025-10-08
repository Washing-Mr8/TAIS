
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
#include "Grafo.h"
using namespace std;


/*@ <answer>

Para resolver el problema necesitamos encontrar la distancia minima entre los 3 vertices interesados, en este caso Alex, Lucas y el trabajo.
Leemos los datos de entrada y creamos el grafo, para posteriormente realizar un recorrido en profundidad por cada vertice interesado (los 3 de antes).
Una vez que tenemos las distancias desde esos vertices a todos, nos quedamos con la menor distancia recorrida entra la que ya tenemos y la suma de los 
3 caminos al vertice intermedio


 COSTE: O(V + A) por el recorrido en anchura bfs, donde V es el numero total de intersecciones, y A los caminos entre ellos.

 COSTE EN ESPACIO ADICIONAL: O(V + A) donde V es el numero total de intersecciones, y A los caminos entre ellos.

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CaminoMasCorto {
private:
    vector<bool> visit; //visit[v] = se ha visitado el vertice v?
    vector<int> dist;
    int s;

    void bfs(Grafo const& g) {
        std::queue<int> q;
        dist[s] = 0; visit[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    dist[w] = dist[v] + 1;
                    visit[w] = true;
                    q.push(w);
                }
            }
        }
    }

public:
    CaminoMasCorto(Grafo const& g, int s) :visit(g.V(), false), dist(g.V()), s(s) {
        bfs(g);
    }

    // número de aristas entre s y v
    int distancia(int v) const {
        return dist[v];
    }
};

bool resuelveCaso() {
    int N = 0, C = 0, A = 0, L = 0, T = 0;
    cin >> N >> C >> A >> L >> T;
    if (!cin) return false;

    Grafo g(N);
    int v1 = 0, v2 = 0;
    for (int i = 0; i < C; i++) {
        cin >> v1 >> v2;
        g.ponArista(--v1, --v2);
    }

    CaminoMasCorto alex(g, --A);
    CaminoMasCorto lucas(g, --L);
    CaminoMasCorto trabajo(g, --T);

    int min_rec = INT_MAX;
    //buscamos el vertice en el que los 3 vertices intersectan con la menor distancia entre todos
    for (int i = 0; i < N; i++) {
        int d1 = alex.distancia(i);
        int d2 = lucas.distancia(i);
        int d3 = trabajo.distancia(i);

        min_rec = min((d1 + d2 + d3), min_rec);
    }
 
    cout << min_rec << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("4_L.in");
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