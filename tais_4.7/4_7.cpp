
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

Para resolver el problema necesitamos crear un grafo de V vertices y añadir sus C conexiones como aristas. Tras leer el numero de iteraciones que 
haremos, recorremos en anchura el grafo para saber la distancia que hay desde el nodo consultado (w), si la distancia es menor o igual a la leida anteriormente
entonces sumamos en 1 a los nodos alcanzados. Tras recorrer todo el grafo devolvemos los nodos totales menos los visitados, dandonos los que no estan visitados

 COSTE: O(V + A) por el recorrido en anchura bfs, donde V es el numero total de nodos de la red, y A son las conexiones entre ellos.

 COSTE EN ESPACIO ADICIONAL: O(V + A) donde V es el numero total de nodos de la red, y A son las conexiones entre ellos.

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CaminoMasCorto {
private:
    vector<bool> visit; //visit[v] = se ha visitado el vertice v?
    vector<int> dist;
    int noVisitados;
    int s;
    int d;


    int bfs(Grafo const& g) {
        int cont = 1;
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
                    if (dist[w] <= d) {
                        ++cont;
                    }
                }
            }
        }
        return cont;
    }

public:
    CaminoMasCorto(Grafo const& g, int s, int d) :visit(g.V(), false), dist(g.V()), s(s), d(d) {
        int visitados = bfs(g);
        noVisitados = g.V() - visitados;
    }
   
    int nodosInalcanzables() {
        return noVisitados;
    }
};

bool resuelveCaso() {
    int N = 0, C = 0;
    cin >> N >> C;
    if (!cin) return false;

    Grafo g(N);
    int v1 = 0, v2 = 0;
    for (int i = 0; i < C; i++) {
        cin >> v1 >> v2;
        g.ponArista(--v1, --v2);
    }

    int K = 0; cin >> K;
    //el vertice origen y la distancia permitida
    int s = 0, d = 0;
    for (int i = 0; i < K; i++) {
        cin >> s >> d;
        CaminoMasCorto cmc(g, --s, d); //inicializamos el grafo con la busqueda en anchura para nuestro vertice origen

        cout << cmc.nodosInalcanzables() << "\n";
    }

    cout << "---\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("4_7.in");
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