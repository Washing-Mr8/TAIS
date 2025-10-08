
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
topologico ->  O(2 * (V + A)) -> O(V + A) siendo V el numero de tareas y A el numero de relaciones directas entre ellas

 COSTE EN ESPACIO ADICIONAL: O(V + A) siendo V el numero de tareas y A el numero de relaciones directas entre ellas

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class CicloDirigido {
private:
    vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs?
    vector<int> ant; // ant[v] = vértice anterior en el camino a v
    vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
    deque<int> _orden; // ordenación topológica
    bool hayciclo;

    void dfs(Digrafo const& g, int v) {
        apilado[v] = true;
        visit[v] = true;
        for (int w : g.ady(v)) {
            if (hayciclo) // si hemos encontrado un ciclo terminamos
                return;
            if (!visit[w]) { // encontrado un nuevo vértice, seguimos
                ant[w] = v; dfs(g, w);
            }
            else if (apilado[w]) { // hemos detectado un ciclo
                // se recupera retrocediendo
                hayciclo = true;
            }
        }
        _orden.push_front(v + 1);
        apilado[v] = false;
    }
public:
    CicloDirigido(Digrafo const& g) : visit(g.V(), false), ant(g.V()),
        apilado(g.V(), false), hayciclo(false) {
        for (int v = 0; v < g.V(); ++v)
            if (!visit[v])
                dfs(g, v);
    }
    bool hayCiclo() const { return hayciclo; }

    // devuelve la ordenación topológica
    deque<int> const& orden() const {
        return _orden;
    }
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

    CicloDirigido topologico(dg);

    if (!topologico.hayCiclo()) { //si no hay ciclos el grafo es DAG
        deque<int> orden = topologico.orden();
        while (!orden.empty()) {
            cout << orden.front() << " ";
            orden.pop_front();
        }
    }
    else{
        cout << "Imposible";
    }

    cout << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("5_3.in");
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