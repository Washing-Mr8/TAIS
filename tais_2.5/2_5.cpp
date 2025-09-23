/*@ <authors>
 *
 * E42 Washington Morocho Lema
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

/*@ <answer>
* 
    Para resolver el problema necesitamos varias colas de prioridad de minimos ordenadas en funcion del orden en el que estan colocados los comics. Cada
    comic tiene un id que tomaremos en cuenta para saber cual elegir en caso de que tengan el mismo orden. Aprovechamos la lectura de datos de entrada para
    averiguar de una vez cual es el mejor comic , que es el que tenga menor id (esto puede suponer un coste de O(M log N) debido a que M colas y ademas
    tenemos que insertar N comics en cada cola con su respectiva prioridad).

    Una vez tenemos todas las colas ordenadas, miraremos el elemento mas priotario de las M colas y nos quedaremos con el menor, eliminandolo y aumentando en 1
    el turno que nos toca esperar. Seguiremos haciendo esto hasta que encontremos el mejor ejemplar dando por finalizado el problema

    COSTE: los datos de entrada como dijimos anteriormente escalan a O(M log N), y como tenemos que obtener el top de cada cola para saber cual tenemos que elegir,
    recorremos M veces la cola de tama�o N, que como no siempre la recorremos al completo el coste es logN.

    En resumen el coste de resolver el problema omitiendo la entrada es de -> O(M log N)

    COSTE EN ESPACIO ADICIONAL: O(M log N) siendo M el numero de colas y N la cantidad de comics en cada cola

@ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Comic {
    int id;
    int pila;
};

bool operator <(const Comic& a, const Comic& b) {
    return b.id < a.id;
}

bool resuelveCaso() {
    int N;
    cin >> N;

    if (!cin) return false;

    vector<vector<int>> pilas(N);
    int mejor_ejemplar = 1000000000;

    // leemos las pilas (del fondo a la cima)
    for (int i = 0; i < N; i++) {
        int K;
        cin >> K;
        pilas[i].resize(K);
        for (int j = 0; j < K; j++) {
            cin >> pilas[i][j];
            if (pilas[i][j] < mejor_ejemplar) {
                mejor_ejemplar = pilas[i][j];
            }
        }
    }

    // si el mejor comic esta en la cima de alguna pila, lo compramos en el turno 1
    for (int i = 0; i < N; i++) {
        if (!pilas[i].empty() && pilas[i].back() == mejor_ejemplar) {
            cout << "1\n";
            return true;
        }
    }

    vector<int> indices(N, 0);

    priority_queue<Comic> comics;

    // Inicializar con las cimas actuales
    for (int i = 0; i < N; i++) {
        if (!pilas[i].empty()) {
            comics.push({ pilas[i].back(), i });
        }
    }

    int turno = 0;
    bool encontrado = false;

    while (!comics.empty() && !encontrado) {
        turno++;

        Comic mejor_actual = comics.top();
        comics.pop();

        int pila_comprada = mejor_actual.pila;
        int comic_comprado = mejor_actual.id;

        if (comic_comprado == mejor_ejemplar) {
            encontrado = true;
            cout << turno << "\n";
        }

        indices[pila_comprada]++;

        if (indices[pila_comprada] < pilas[pila_comprada].size()) {
            int nuevo_comic = pilas[pila_comprada][pilas[pila_comprada].size() - 1 - indices[pila_comprada]];
            comics.push({ nuevo_comic, pila_comprada });
        }
    }

    return true;
}

//@ </answer>

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("2_5.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif
    return 0;
}