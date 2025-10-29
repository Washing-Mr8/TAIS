/*@ <authors>
 *
 * E42 Washington Morocho Lema
 * E63 Sergio Vazquez Carbajo
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
 
 Para resolver el problema necesitamos utilizar un grafo valorado dirigido que simule las aldeas que tenemos para encontrar el punto medio entre galos y romanos.
 Para ello crearemos 2 vectores que almacenaran ambos bandos y las aristas que añadimos al grafo son birideccionales. Una vez que tenemos lista la entrada realizaremos
 2 veces el algoritmo de Dijkstra (uno por cada bando) para encontrar el camino minimo desde cada bando a las demas aldeas. Mientras recorremos el grafo, comprobamos si 
 el vertice que visitamos es de nuestro bando o no. Si lo es, su distancia pasa a ser la del vertice anterior, en otro caso, se actualizara si la distancia es mayor.
 Finalmente iteramos sobre el tamaño del grafo (N) para comparar la diferencia entre el camino de ambos bandos a un punto en comun, que sera la mediana.

 AÑADIDO: Me ha faltado verificar que la aldea mediana sea neutral, es decir, que no sea ni gales ni romana. Tambien me ha faltado poner al comienzo de cada Dijkstra
 los vertices de cada bando en el indexPQ. Como no los añadi al principio solo se realizaba la busqueda desde el primer vertice del bando y no desde cualquiera (como
 deberia ser)
 
 COSTE: utilizar el algoritmo de  dijkstra tiene un coste O(AlogV) (A:Aristas , V:Vertices) y solo necesitamos realizarlo 2 veces (una por cada bando), ademas antes de
 empezarlo necesitamos iterar G o R veces para ver que vertices son de nuestro bando. Sin contar la iteracion para mostrar la solucion el coste es -> 
 O( 2( C log N ) + G + R ) siendo C el numero de caminos, N el numero de aldeas, G el numero de aldeas de gales y R el numero de aldeas romanas

 COSTE EN ESPACIO ADICIONAL:  O(2N + C + G + R) siendo C el numero de caminos, N el numero de aldeas (uno mas por Dijkstra), G el numero de aldeas de gales y R 
 el numero de aldeas romanas

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

template <typename Valor>
class CamninosBando {
private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    vector<bool> nuestro_bando;

    std::vector<Valor> dist;
    IndexPQ<Valor> pq;

    void relajar(AristaDirigida<Valor> a) {
        
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor() && !nuestro_bando[w]) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
        else if (dist[w] >= dist[v] + a.valor() &&  nuestro_bando[w]) { // si el vertice es de nuestro bando, su distancia pasa a ser la del anterior 
            dist[w] = dist[v]; // si es de nuestro bando la distancia no se suma
        }
    }

    void dijkstra(DigrafoValorado<Valor> const& g){
        dist[origen] = 0;
        for (int i = 0; i < g.V(); i++) {
            if (nuestro_bando[i]) {
                //dist[i] = 0;
                pq.push(i, 0);
            }

        }

        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

public:
    CamninosBando(DigrafoValorado<Valor> const& g, int orig, vector<int> const& aldeas) : origen(orig),
        dist(g.V(), INF), pq(g.V()), nuestro_bando(g.V(), false) {
        //primero comprobamos que aldeas son de nuestro bando
        for (int indice : aldeas) {
            nuestro_bando[indice] = true;
            dist[indice] = 0;
        }
        dijkstra(g);
    }

    Valor distancia(int v) const { return dist[v]; }
};


bool resuelveCaso() {

    // leemos la entrada
    int N, C;
    cin >> N >> C;
    if (!cin)
        return false;

    // leer el resto del caso y resolverlo
    DigrafoValorado<int> dgv(N);

    int v1 = 0, v2 = 0, valor = 0;
    for (int i = 0; i < C; i++) {
        cin >> v1 >> v2 >> valor;
        //caminos bidireccionales
        dgv.ponArista({ v1 - 1, v2 - 1, valor });
        dgv.ponArista({ v2 - 1, v1 - 1, valor });
    }

    //guardamos los indices de los galos y los romanos y vemos que aldeas no son neutrales
    vector<bool> aldeasNeutrales(N, true);

    int g = 0, r = 0, indice = 0;
    
    cin >> g;
    vector<int> galos(g);
    for (int i = 0; i < g; i++) {
        cin >> indice;
        galos[i] = indice - 1;
        aldeasNeutrales[indice - 1] = false;
    }

    cin >> r;
    vector<int> romanos(r);
    for (int i = 0; i < r; i++) {
        cin >> indice;
        romanos[i] = indice - 1;
        aldeasNeutrales[indice - 1] = false;
    }

    CamninosBando<int> caminosGalos(dgv, galos[0], galos);
    CamninosBando<int> caminosRomanos(dgv, romanos[0], romanos);


    int minDistancia = INT16_MAX, mediana = 0;
    for (int i = 0; i < N; i++) {
        int diferencia = abs(caminosGalos.distancia(i) - caminosRomanos.distancia(i));

        if (aldeasNeutrales[i]) {
            if (diferencia < minDistancia || (diferencia == minDistancia && i + 1 < mediana)) {
                minDistancia = diferencia;
                mediana = i + 1;
            }
        }
    }

    cout << mediana << " " << minDistancia << "\n";
  
  return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
  // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
  ifstream in("casos.txt");
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
