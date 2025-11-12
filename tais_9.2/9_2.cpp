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
Para resolver el ejercicio necesitamos pensar una estrategia voraz que nos permita resolver el problema. Para ello utilizaremos un vector de pares que simularan
los intervalos, cada uno con su comienzo y final. Para encontrar el minimo numero de trabajos a realizar comprobaremos que los intervalos de trabajo cubran el
intervalo [C,F) especificado. Mientras iteramos comprobamos si el trabajo actual tiene un comienzo menor o igual al ultimo trabajo y si su final tambien es 
mayor. 

COSTE: Iteramos N veces sobre el vector para recorrer todos los trabajos y ver si cumplen con el intervalo, y el coste de ordenar un vector de menor a mayor 
es O(NlogN) siendo N el tamaño del vector -> O(N log N + N) = O(N log N) siendo N el numero de trabajos dados

COSTE EN ESPACIO ADICIONAL: O(N) siendo N el numero de trabajos dados

@ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

using intervalo = pair<int, int>;

const bool operator <(intervalo const& a, intervalo const& b) {
    return a.first < b.first;
}

bool resuelveCaso() {
    int N = 0, C = 0, F = 0; cin>> C >> F >> N;

    if (N == 0 && C == 0 && F == 0) return false;

    vector<intervalo> intervalos(N);

    int c = 0, f = 0;

    for (int i = 0; i < N; i++) {
        cin >> c >> f;
        intervalos[i] = { c,f };
    }

    sort(intervalos.begin(), intervalos.end());

    int trabajos = 0, i = 0, ultimoTrabajo = C;
    bool haySol = true;

    while (haySol && ultimoTrabajo < F) {
        int mejorFinal = -1;

        if (i >= intervalos.size() || intervalos[i].first > ultimoTrabajo) {
            haySol = false;
        }
        while (haySol && i < intervalos.size() && intervalos[i].first <= ultimoTrabajo) {
            if (intervalos[i].second > ultimoTrabajo && intervalos[i].second > mejorFinal) {
                mejorFinal = intervalos[i].second;
            }
            i++;
        }
        if (mejorFinal == -1) { // no se cubre el intervalo
            haySol = false;
        }

        ultimoTrabajo = mejorFinal;
        trabajos++;
    }

    if (haySol) {
        cout << trabajos << "\n";
    }
    else {
        cout << "Imposible\n";
    }

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("9_2.in");
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