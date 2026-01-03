/*@ <authors>
 *
 * E42 Washington Morocho Lema
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <numeric>
#include <queue>
using namespace std;

#include "PriorityQueue.h"
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"

/*@ <answer>

Para resolver el ejercicio necesitamos usar un grafo valorado para encontrar los posibles caminos entre intersecciones. Necesitamos sumar todas las aristas que formen
el arbol de recubrimiento minimo (ARM) utilizando el algoritmo de kruskal. Si el arbol ARM es de tamaño N - 1, entonces el grafo es conexo y se pueden llegar a todos 
los pueblos por lo que nos quedaremos con la ultima arista que sera la de mayor duracion. En caso de que no sea conexo, entonces la solucion es imposible.

Coste: sin contar la lectura de la entrada, utilizamos el algoritmo de kruskal que tiene como coste O(A log A), siendo A el numero de calles

Coste en espacio adicional: el tamaño del grafo O(A + V) + el espacio adicional usado por Kruskal O(A) -> O(A + V) siendo V el numero de intersecciones y A el numero de calles
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Kruskal_ARM {
private:
    std::vector<Arista<int>> _ARM;
    int coste;
    bool posible;

public:

    Kruskal_ARM(GrafoValorado<int> const& g) : coste(0), posible(false) {
        PriorityQueue<Arista<int>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
                _ARM.push_back(a); 
                coste += a.valor();

                if (_ARM.size() == g.V() - 1) { 
                    posible = true;
                    break; 
                }
            }
        }
    }

    int costeARM() const {
        return coste;
    }


    std::vector<Arista<int>> const& ARM() const {
        return _ARM;
    }
    bool esPosible() {
        return posible;
    }
};


bool resuelveCaso() {
   // leer los datos de la entrada
    int N, M; cin >> N >> M;

    if (!cin) return false;

   GrafoValorado<int> gv(N);

   int v1 = 0, v2 = 0, valor = 0;

   for (int i = 0; i < M; i++) {
       cin >> v1 >> v2 >> valor;
       gv.ponArista({ v1 - 1, v2 - 1, valor }); // camino bidireccional
   }
   
   // resolver el caso posiblemente llamando a otras funciones
   Kruskal_ARM sol(gv);

   // escribir la solución
   if (N == 1) {
       cout << 0;
   }
   else {
       if (sol.esPosible()) {
           cout << sol.costeARM();
       }
       else {
           cout << "Imposible";

       }
   }
   cout <<"\n";
   return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("R_9.in");
   if (!in.is_open())
      cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
   auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

   while (resuelveCaso());

   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   cin.rdbuf(cinbuf);
#endif
   return 0;
}
