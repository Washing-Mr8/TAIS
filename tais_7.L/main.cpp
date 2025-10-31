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

 SOLUCION: Para resolver correctamente el problema de manera eficiente habian 2 posibles caminos. Usar 2 superaldeas, es decir 2 vertices adicionales con distancia 0 
 a su propio bando y luego realizar Dijkstra para cada super vertice. La otra es modificar levenmente el Dijkstra para añadir los origenes de un bando con distancia 0
 y asi cada bando tiene sus caminos minimos a los demas vertices (luego se comprueba cuando se hace la diferencia y ademas la aldea tiene que ser neutral)

 AUNQUE DE WRONG ANSWER LA SOLUCION ES ASI
 
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
class CaminosBando {
private:
    const Valor INF = std::numeric_limits<Valor>::max();

    std::vector<Valor> dist;
    IndexPQ<Valor> pq;

    void relajar(AristaDirigida<Valor> a) {
        
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }

public:
    CaminosBando(DigrafoValorado<Valor> const& g, vector<int> const& aldeas) : dist(g.V(), INF), pq(g.V()) {
        for (int aldea : aldeas) {
            dist[aldea] = 0;
            pq.push(aldea, 0);
        }

        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
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

    CaminosBando<int> caminosGalos(dgv, galos);
    CaminosBando<int> caminosRomanos(dgv, romanos);

    int minDistancia = INT16_MAX, mediana = 0;

    for (int i = 0; i < N; i++) {
        int diferencia = abs(caminosGalos.distancia(i) - caminosRomanos.distancia(i));

        if (aldeasNeutrales[i] && diferencia < minDistancia) {
            minDistancia = diferencia;
            mediana = i + 1;
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
