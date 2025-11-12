/*@ <authors>
 *
 * E42 Washington Morocho Lema
 * E16 Ruben Dolera Mancebo
 * 
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>
#include <numeric>

#include "DigrafoValorado.h"
#include "IndexPQ.h"
using namespace std;

/*@ <answer>
 Para resolver el problema necesitamos utilizar una estrategia voraz que nos permita encontrar el coste minimo para abastecer a todos los pueblos desde las 2 plantas.
 Para ello utilizamos un grafo valorado dirigido para calcular las distancias minimas desde cada planta a todos los pueblos. Una vez tenemos las distancias minimas
 calculamos las diferencias desde ambas plantas a cada pueblo y luego las ordenamos de mayor a menor para quedarnos con la minima diferencia, y asi quedarnos con el
 camino optimo. En caso de empate se elegira el camino de cualquiera de las plantas. la distancia total la multiplicamos por 2, porque el reparto es ida y vuelta
 
 COSTE: utilizar el algoritmo de  dijkstra tiene un coste O(AlogV) (A:Aristas , V:Vertices) y solo necesitamos realizarlo 2 veces (una por cada planta).
 Una vez con las distancias minimas, necesitamos ordenar el vector con nuestra estructura Pueblo, asi que el coste es O(N log N) siendo N el numero de pueblos 
 Como N <= M , el caso peor es M log N-> O( ( M log N ) siendo M el numero de caminos, N el numero de pueblos

 COSTE EN ESPACIO ADICIONAL:  O(3N + M) siendo M el numero de caminos, N el numero de pueblos (uno mas por Dijkstra y otro por voraz)

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

struct Pueblo {
    int d1;
    int d2;
    int diferencia;
};

//ordenar de mayor a menor por diferencia
const bool operator < (Pueblo const& a, Pueblo const& b ) {
    return a.diferencia > b.diferencia;
}


class Transporte {
private:
    const int INF = INT_MAX;

    std::vector<int> dist;
    IndexPQ<int> pq;

    void relajar(AristaDirigida<int> a) {
        
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }

public:
    Transporte(DigrafoValorado<int> const& g, int v) : dist(g.V(), INF), pq(g.V()) {
        dist[v] = 0;
        pq.push(v, 0);

        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    int distancia(int v) const { return dist[v]; }

    vector<int> distancias() const { return dist; }
};


bool resuelveCaso() {
    // leemos la entrada
    int N, M;
    cin >> N >> M;
    if (!cin)
        return false;

    // leer el resto del caso y resolverlo
    DigrafoValorado<int> dgv(N);

    int v1 = 0, v2 = 0, valor = 0;
    for (int i = 0; i < M; i++) {
        cin >> v1 >> v2 >> valor;
        //caminos bidireccionales
        dgv.ponArista({ v1 - 1, v2 - 1, valor });
        dgv.ponArista({ v2 - 1, v1 - 1, valor });
    }

    //guardamos los indices de los galos y los romanos y vemos que aldeas no son neutrales
    Transporte plantaNorte(dgv, 0);
    Transporte plantaSur(dgv, N - 1);

    vector<Pueblo> pueblos;
    for (int i = 1; i < N - 1; i++) {
        int d1 = plantaNorte.distancia(i);
        int d2 = plantaSur.distancia(i);

        pueblos.push_back({ d1, d2, abs(d1 - d2) });
    }

    sort(pueblos.begin(), pueblos.end());

    int repartoNorte = 0, repartoSur = 0, sumaFinal = 0;

    for (int i = 0; i < N - 2; i++) {
        // si la distancia es menor desde la planta norte
        if (pueblos[i].d1 < pueblos[i].d2) {
            //en caso que este lleno usamos la planta sur
            if (repartoNorte >= (N - 2) / 2) {
                sumaFinal += pueblos[i].d2;
                repartoSur++;
            }
            else {
                sumaFinal += pueblos[i].d1;
                repartoNorte++;
            }
        }
        else {// si la distancia es menor desde la planta sur

            if (repartoSur >= (N - 2) / 2) {//en caso que este lleno usamos la planta sur
                sumaFinal += pueblos[i].d1;
                repartoNorte++;
            }
            else {
                sumaFinal += pueblos[i].d2;
                repartoSur++;
            }

        }
    }
    //multiplicamos por 2 porque es ida y vuelta
    cout << sumaFinal * 2 << "\n";
  
  return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
  // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
  ifstream in("9_L.in");
  if (!in.is_open())
    cout << "Error: no se ha podido abrir el archivo de entrada." << endl;
  auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
  
  // Resolvemos
  while (resuelveCaso());
  
  // para dejar todo como estaba al principio
#ifndef DOMJUDGE
  cin.rdbuf(cinbuf);
#endif
  return 0;
}
