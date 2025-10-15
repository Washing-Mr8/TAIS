
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

Para resolver el problema necesitamos realizar una unica busqueda en profundidad de un grafo dirigido, para detectar si hay ciclos y si el nodo final es
alcanzable. Vamos leyendo los datos de entrada y añadimos aristas en funcion de la operacion, para ello inicializamos un grafo dirigido de tamaño L + 1 para
simular el nodo final como la ultima posible instruccion. En funcion de las operaciones (A o C) añadimos aristas desde la instruccion actual a la siguiente
y en caso de ser C o J, añadimos un arista a un nodo dado. Para determinar el estado del programa necesitamos saber si es posible recorrerlo desde el origen 
hasta el destino, para ello realizamos un recorrido en profundidad una unica vez para ver si es alcanzable y si contiene ciclos.

 COSTE: Realizamos un recorrido en profundidad para buscar si el grafo contiene ciclos y si es alcanzable -> O(L + A) siendo L el numero de instrucciones y A las
 conexiones que hay entre ellas

 COSTE EN ESPACIO ADICIONAL: O(L + A) siendo L el numero de instrucciones y A las conexiones que hay entre ellas

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

class Necronomicon {
private:
    vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs?
    vector<int> ant; // ant[v] = vértice anterior en el camino a v
    vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
    bool alcanzable;
    bool hayciclo;

    void dfs(Digrafo const& g, int s, int destino) {
        apilado[s] = true;
        visit[s] = true;
        for (int w : g.ady(s)) { // es un recorrido dfs, pero no terminamos el recorrido si se detecta un ciclo
            if (w == destino) {
                alcanzable = true;
            }
            if (!visit[w]) { // encontrado un nuevo vértice, seguimos
                ant[w] = s; 
                dfs(g, w, g.V() - 1);
            }
            else if (apilado[w]) { // hemos detectado un ciclo
                hayciclo = true;
            }
        }
        apilado[s] = false;
    }
public:
    Necronomicon(Digrafo const& g) : visit(g.V(), false), ant(g.V()), apilado(g.V(), false), hayciclo(false), alcanzable(false) {
        dfs(g, 0, g.V() - 1);
    }

    bool hayCiclo() const { return hayciclo; }

    bool termina() { return alcanzable; }
};

bool resuelveCaso() {
    int L = 0; cin >> L;
    if (!cin) return false;

    Digrafo dg(L+1); //inicializamos el grafo dirigido con un nodo extra
    string op;

    for (int i = 0; i < L; i++) {
        cin >> op;
        int v;
        if (op == "A") {
            dg.ponArista(i, i + 1);
        }
        else if (op == "C") {
            cin >> v;
            dg.ponArista(i, v - 1);
            dg.ponArista(i, i + 1);
        }
        else if (op == "J") {
            cin >> v;
            dg.ponArista(i, v - 1);
        }

    }
    Necronomicon programa(dg);

    if (!programa.termina()) {
        cout << "NUNCA";
    }
    else if (programa.hayCiclo()) {
        cout << "A VECES";
    }
    else {
        cout << "SIEMPRE";
    }

    cout << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("5_L.in");
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