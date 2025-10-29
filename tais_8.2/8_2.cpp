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
Para resolver el problema necesitamos pensar en un estrategia voraz que nos permita resolver el problema. Para ello usaremos dos vectores para guardar el numero
de invasores y defensores, que usaremos para encontrar la solucion. Ordenamos ambas listas de menor a mayor, y luego comparamos desde la misma posicion, si
nuestro numero de defensores supera o iguala a la ultima ciudad invadida almacenada. En caso de que no, comparamos la siguiente tropa de defensores con el ultimo
numero de invasores de la ciudad que no pudimos abatir.

COSTE: Iteramos N veces sobre el vector para saber que ciudades podemos defender, y el coste de ordenar un vector de menor a mayor es O(NlogN) siendo N el tamaño
del vector -> O(2(N log N) + N) siendo N el numero de tropas (tanto invasores como defensores)

COSTE EN ESPACIO ADICIONAL: O(2N) siendo N el numero de tropas (tanto invasores como defensores)

@ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    int N = 0; cin >> N;
    if (!std::cin) return false;

    vector<int> invasores(N);
    int valor = 0;

    for (int i = 0; i < N; i++) {
        cin >> valor;
        invasores[i] = valor;
    }

    vector<int> defensas(N);

    for (int i = 0; i < N; i++) {
        cin >> valor;
        defensas[i] = valor;
    }


    //ordenamos ambos vectores de menor a mayor para ver cuantas ciudades se pueden defender

    sort(invasores.begin(), invasores.end());
    sort(defensas.begin(), defensas.end());

    int ultimoInvasor = 0, defendidos = 0;

    for (int i = 0; i < N; i++){
        if (defensas[i] >= invasores[ultimoInvasor]) {
            defendidos++;
            ultimoInvasor++;
        }
    }
   
    cout << defendidos << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("8_2.in");
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