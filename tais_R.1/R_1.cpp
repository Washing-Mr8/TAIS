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

#include "DigrafoValorado.h"
#include "IndexPQ.h"

/*@ <answer>

Para resolver el ejercicio necesitamos encontrar si hay un camino minimo desde donde se encuentra Palencia Jones hasta la camara del tesoro. Para ello usaremos el 
algoritmo de Dijkstra para encontrar ese camino. Mientras recorremos el grafo, en vez de sumar la respiracion total desde donde venimos, nos quedamos con el maximo
entre el tiempo que aguanta en este pasillo, y el que mas ha aguantado antes. Si no es posible llegar entonces mostraremos IMPOSIBLE

Coste: sin contar la lectura de la entrada, utilizamos el algoritmo de Dijkstra que tiene como coste O(A log V), siendo A el numero de pasillos y V el numero de camaras

Coste en espacio adicional: el tamaño del vector O(A+V) + el esapcio adicional usado por Dijkstra O(V) -> O(A+V)
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


class MaxRespiracion {

private:
    const int INF = INT_MAX;
    int origen;
    int destino;
    vector<int> dist;
    IndexPQ<int> pq;
    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();

        if (dist[w] > max(dist[v], a.valor())) {
            dist[w] = max( dist[v], a.valor());
            pq.update(w, dist[w]);
        }
    }

public:
    MaxRespiracion(DigrafoValorado<int> const& g, int orig, int dest) : origen(orig),destino(dest), dist(g.V(), INF), pq(g.V()) {
        dist[origen] = 0;
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
   // leer los datos de la entrada
    int V, A; cin >> V >> A;

   if (!std::cin) return false; // fin de la entrada

   DigrafoValorado<int> dgv(V);

   int v1 = 0, v2 = 0, valor = 0;

   for (int i = 0; i < A; i++) {
       cin >> v1 >> v2 >> valor;
       dgv.ponArista({ v1 - 1, v2 - 1, valor }); // camino bidireccional
       dgv.ponArista({ v2 - 1, v1 - 1, valor });
   }
   int origen = 0, destino = 0;
   cin >> origen >> destino;
   
   // resolver el caso posiblemente llamando a otras funciones
   MaxRespiracion sol(dgv, origen - 1, destino - 1);

   // escribir la solución
   if (sol.hayCamino(destino - 1 )) {
       cout << sol.distancia(destino - 1);
   }
   else {
       cout << "IMPOSIBLE";

   }
   cout <<"\n";

   return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("R_1.in");
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
