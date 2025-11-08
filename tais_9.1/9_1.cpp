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
los edificios, cada uno con su comienzo y final. Para encontrar el minimo numero de tuneles que tenemos que cavar necesitamos ordenar los edificios de menor a
mayor segun donde se encuentre su final. Recorremos los edificios y comparamos si el comienzo del edificio actual es mayor o igual que el final del ultimo
edificio que necesitó un tunel, en caso de que si, aumentamos en 1 el numero de tuneles que necesitamos y marcamos este edificio como el ultimo que necesito un
tunel. Seguimos iterando hasta recorrer todos los edificios

COSTE: Iteramos N veces sobre el vector para saber cuantos tuneeles necesitamos cavar, y el coste de ordenar un vector de menor a mayor es O(NlogN) siendo N el 
tamaño del vector -> O(N log N + N) = O(N log N) siendo N el numero de edificios dados

COSTE EN ESPACIO ADICIONAL: O(N) siendo N el numero de edificios dados

@ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

using edificio = pair<int, int>;

const bool operator <(edificio const& a, edificio const& b) {
    return a.second < b.second;
}

bool resuelveCaso() {
    int N = 0; cin >> N ;

    if (N == 0) return false;

    vector<edificio> edificios(N);

    int w = 0, e = 0;

    for (int i = 0; i < N; i++) {
        cin >> w >> e;
        edificios[i] = { w,e };
    }

    sort(edificios.begin(), edificios.end());

    int tuneles = 1;
    int ultimo_final = edificios[0].second;

    for (int i = 1; i < N; i++) {
        if (edificios[i].first >= ultimo_final) {
            tuneles++;
            ultimo_final = edificios[i].second;
        }
    }

    cout << tuneles << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("9_1.in");
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