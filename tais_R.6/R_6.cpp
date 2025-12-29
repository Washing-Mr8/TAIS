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

#include "Grafo.h"

/*@ <answer>

Para resolver el ejercicio necesitamos usar un grafo para simular las conexiones entre los distintos personajes del juego. Una vez leida la entrada, usamos un vector para
alamcenar cuanto oro quiere cada personaje y obtenemos las aristas de los personajes que son amigos. Realizaremos una busqueda en profundidad sobre cada vertice, ya que
el grafo no tiene porque ser conexo. En cada iteracion nos quedaremos con el menor coste de oro sobre una relacion de amigos ya que el coste de esparcirlo sobre esta red es
gratis. Para cada vertice individual sin arista la funcion devolvera su coste en oro. Finalmente nos quedamos con la suma acumulada al recorrer todos los vertices no visitados 

Coste: sin contar la lectura de la entrada, utilizamos la busqueda en profundidad DFS que tiene un coste O(A+V),siendo A el numero de personajes y V las conexiones entre ellos

Coste en espacio adicional: el tamaño del vector O(A + V) siendo A el numero de personajes y V las conexiones entre ellos
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class CaminosDFS {
private:
    std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    vector<int> oro;
    int coste;

    int dfs(Grafo const& G, int v) {
        visit[v] = true;
        int precio = oro[v];

        for (int w : G.ady(v)) {
            if (!visit[w]) {
                precio = min(precio, dfs(G, w));
            }
        }

        return precio;
    }
public:
    CaminosDFS(Grafo const& g, const vector<int>& oro) : visit(g.V(), false), coste(0), oro(oro){
        
        for (int i = 0; i < g.V(); i++) {
            int precio = 0;
            if (!visit[i]) {
                precio = dfs(g, i);
                coste += precio;
            }

        }
    }

    int costeMinimo() const { return coste; }
};

bool resuelveCaso() {
   // leer los datos de la entrada
    int V, A; cin >> V >> A;

   if (!std::cin) return false; // fin de la entrada

   vector<int> oro(V);
   Grafo g(V);

   for (int i = 0; i < V; i++) {
       cin >> oro[i];
   }

   int v1 = 0, v2 = 0;

   for (int i = 0; i < A; i++) {
       cin >> v1 >> v2;
       g.ponArista(v1 - 1, v2 - 1);
   }
   // resolver el caso posiblemente llamando a otras funciones
   CaminosDFS sol(g, oro);

   // escribir la solución
   cout << sol.costeMinimo() <<"\n";

   return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("R_6.in");
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
