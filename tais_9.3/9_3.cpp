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
#include <numeric>
#include <algorithm>

using namespace std;

/*@ <answer>


COSTE: Iteramos N veces sobre el vector para ssaber que peliculas podemos ver, y el coste de ordenar un vector de menor a mayor es O(NlogN) siendo N el tamaño
del vector -> O(N log N + N) siendo N el numero de peliculas disponibles

COSTE EN ESPACIO ADICIONAL: O(N) siendo N el numero de peliculas disponibles

@ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool resuelveCaso() {
    int N = 0, V = 0; cin >> N >> V;

    deque<long int> pilas;

    long int valor = 0;

    for (int i = 0; i < N; i++) {
        cin >> valor;
        pilas.push_back(valor);
    }

    //ordenamos las pilas de menor a mayor
    sort(pilas.begin(), pilas.end());
   
    int coches = 0;

    while (pilas.size() > 1) {
        if (pilas.front() + pilas.back() >= V) {
            pilas.pop_front();
            pilas.pop_back();
            coches++;

        }else{
            pilas.pop_front();
        }

    }

    cout << coches << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("9_3.in");
    if (!in.is_open())
        std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout << "Pulsa Intro para salir..." << std::flush;
    std::cin.get();
#endif
    return 0;
}