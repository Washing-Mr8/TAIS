
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
#include "Digrafo.h"
using namespace std;


/*@ <answer>

Para resolver el problema necesitamos realizar varios recorridos en anchura  sobre un grafo dirigido , desde el origen hasta todos los  vertices (para ver
cuales son alcanzables) y desde el destino hacia los demas (usamos el grafo inverso para saber que vertices son alcanzables desde el final).
Una vez tengamos nuestros vectores de visitados (uno desde el origen y otro hacia el destino, que es inverso), comparamos cuantos vertices tienen en comun,
siendo estos los restaurantes que deberian preparar paella. En caso de que no haya una distancia o camino desde el origen hacia el destino, sera IMPOSIBLE llegar

 COSTE: Realizamos 2 busquedas en anchura por cada Q consultas que leemos ->  O(Q(V + A)) siendo V el numero de restaurantes y A el numero de calles

 COSTE EN ESPACIO ADICIONAL: O(V + A) siendo V el numero de restaurantes y A el numero de calles

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class PaellaJuevesBFS {
private:
    Digrafo const& g;
    vector<bool> visitOrigen;
    vector<bool> visitDestino;
    int origen, destino;
    int restaurantes;

    void bfsDesde(int origen) {
        queue<int> q;
        visitOrigen[origen] = true;
        q.push(origen);

        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : g.ady(v)) {
                if (!visitOrigen[w]) {
                    visitOrigen[w] = true;
                    q.push(w);
                }
            }
        }
    }

    void bfsHacia(int destino) {
        queue<int> q;
        visitDestino[destino] = true;
        q.push(destino);

        Digrafo inverso = g.inverso();

        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : inverso.ady(v)) {
                if (!visitDestino[w]) {
                    visitDestino[w] = true;
                    q.push(w);
                }
            }
        }
    }

public:
    PaellaJuevesBFS(Digrafo const& grafo, int origen, int destino) : g(grafo), visitOrigen(g.V(),false),visitDestino(g.V(), false), origen(origen), destino(destino) {
        bfsDesde(origen);// BFS desde origen
        bfsHacia(destino);// BFS hacia destino (en grafo inverso)

        // contar nodos en la intersección (excluyendo origen y destino)
        int cont = 0;
        if (visitOrigen[destino]) { //si no se puede alcanzar el destino desde el origen
            for (int v = 0; v < g.V(); ++v) {
                if (v != origen && v != destino && visitOrigen[v] && visitDestino[v]) {
                    cont++;
                }
            }
        }
        else {
            cont = -1;// IMPOSIBLE
        }
        restaurantes = cont;
    }

    int restaurantesEnCamino() {
        if (origen == destino) {
            restaurantes = 0;
        }

        return restaurantes;
    }
};


bool resuelveCaso() {
    int V = 0, A = 0;
    cin >> V >> A;
    if (!cin) return false;

    Digrafo dg(V); //inicializamos el grafo dirigido

    int v1 = 0, v2 = 0;
    for (int i = 0; i < A; i++) {
        cin >> v1 >> v2;
        dg.ponArista(--v1, --v2);
    }

    int Q = 0; cin >> Q;

    int origen = 0, destino = 0;
    for (int i = 0; i < Q; i++) {
        cin >> origen >> destino;
        PaellaJuevesBFS sol(dg, --origen, --destino);

        int restaurantes = sol.restaurantesEnCamino();
        if (restaurantes == -1) {
            cout << "IMPOSIBLE\n";
        }
        else {
            cout << restaurantes << "\n";
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
    std::ifstream in("5_2.in");
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