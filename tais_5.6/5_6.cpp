
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

Para resolver el problema necesitamso realizar un recorrido en anchura bfs para encontrar la menor distancia hasta la casilla final del tablero. Leemos los
datos de entrada en el que tenemos escaleras que las usaremos como aristas para atajar hasta la casilla final, y serpientes, que tambien usaremos como
aristas que penalizan haciendo que no sea un camino viable. Para hallar el camino minimo tendremos que asignarle una arista a cada casilla desde esa misma
casilla(origen) hasta las posiblea casillas alcanczables por el tiro de dado(destino), que estaran limitados a un tamaño K

 COSTE: Debido a que realizamos un recorrido bfs, su coste es del orden O(V + A), pero antes de realizarlo tenemos que añadir (N*N) - 1 * K aristas.
 Como ahora sabemos el numero de aristas en el caso peor, el coste pasaria a ser -> O(M + ((M-1)*K)) siendo M el tamaño del tablero (N * N filas) y 
 K el tamaño del dado (numeros de 1 a K)

 COSTE EN ESPACIO ADICIONAL: En el caso peor tenemos un grafo con M vertices, siendo M  el tamaño del tablero (100 como maximo), y M-1 (99 como maximo) por 
 cada valor del dado posible (K) -> O(M + ((M-1)*K))

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Tablero {
private:
    vector<int> visit;
    vector<int> dist;
    int s;

    void bfs(Digrafo const& g) {
        std::queue<int> q;
        dist[s] = 0; visit[s] = true;
        q.push(s);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    dist[w] = dist[v] + 1; visit[w] = true;
                    q.push(w);
                }
            }
        }
    }

public:
    Tablero(Digrafo const& g, int s) :dist(g.V(), 0), visit(g.V(), false), s(s) {
        bfs(g);
    }

    int distancia(int v) {
        return dist[v];
    }
};

bool resuelveCaso() {
    int N = 0, K = 0, S = 0, E = 0;
    cin >> N >> K >> S >> E;
    if (N == 0 && K == 0 && S == 0 && E == 0) 
        return false;

    int casillas = N * N;
    
    vector<int> atajos(casillas, -1);

    //leemos las casillas de serpientes
    int origen = 0, destino = 0;
    for (int i = 0; i < S; i++) {
        cin >> origen >> destino;
        atajos[--origen] = --destino;
    }
    //leemos las casillas de escaleras
    for (int i = 0; i < E; i++) {
        cin >> origen >> destino;
        atajos[--origen] = --destino;
    }

    Digrafo dg(casillas);

    for (int i = 1; i <= casillas; i++) {
        for (int j = 1; j <= K; j++) {
            destino = i + j;
            if (destino <= casillas) {
                if (atajos[destino - 1] == -1) {
                    dg.ponArista(i - 1, --destino);
                }
                else {
                    dg.ponArista(i - 1, atajos[--destino]);
                }
            }

        }
    }

    Tablero sol(dg,0);

    cout << sol.distancia(--casillas) << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("5_6.in");
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