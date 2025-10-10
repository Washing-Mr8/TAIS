
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

Para resolver el problema necesitamos utilizar un grafo dirigido para poder realizar una ordenacion topologica y asi quedarnos con el post orden inverso, que
sera la secuencia en el que las tareas seran realizadas. Para poder realizar esta ordenacion necesitamos que el grafo sea un DAG, es decir, que no tenga ciclos

 COSTE: Realizamos un recorrido en profundidad para buscar si el grafo contiene ciclos, ademas de que necesitamos hacer otro recorrido para hallar el orden
topologico ->  O(2 * (V + A)) -> O(V + A) siendo V el numero de variables y A el numero de inecuaciones

 COSTE EN ESPACIO ADICIONAL: O(V + A) siendo V el numero de variables y A el numero de inecuaciones

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class OrdenTopologico {
private:
    vector<bool> visit;
    vector<bool> apilado;
    deque<int> _orden;
    vector<int> valores;
    bool hayCiclo;

    void dfs(Digrafo const& g, int v) {
        visit[v] = true;
        apilado[v] = true;
        for (int w : g.ady(v)) {
            if (hayCiclo) return;
            if (!visit[w]) {
                dfs(g, w);
            }
            else if (apilado[w]) {
                hayCiclo = true;
            }
        }
        apilado[v] = false;
        _orden.push_front(v);
    }

    void calcularValores() {
        int valorActual = 1;
        for (int v : _orden) {
            valores[v] = valorActual++;
        }
    }

public:
    OrdenTopologico(Digrafo const& g) : visit(g.V(), false), apilado(g.V(), false), hayCiclo(false), valores(g.V(),0) {
        for (int v = 0; v < g.V(); ++v)
            if (!visit[v])
                dfs(g, v);

        if (!hayCiclo) {
            calcularValores();
        }
    }

    bool tieneCiclo() const { return hayCiclo; }
    deque<int> const& orden() const { return _orden; }
    vector<int> const& getValores() const { return valores; } 
};

bool resuelveCaso() {
    int N = 0, M = 0;
    cin >> N >> M;
    if (!cin) return false;

    Digrafo dg(N); //inicializamos el grafo dirigido

    int v1 = 0, v2 = 0;
    for (int i = 0; i < M; i++) {
        cin >> v1 >> v2;
        dg.ponArista(--v1, --v2);
    }

    OrdenTopologico sistema(dg);

    if (!sistema.tieneCiclo()) {
        cout << "SI";
        auto valores = sistema.getValores();
        for (int i = 0; i < N; ++i) {
            cout << " " << valores[i];
        }
    }
    else {
        cout << "NO";
    }
    cout << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("5_4.in");
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