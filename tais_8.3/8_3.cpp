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
de jugadores y equipaciones, que usaremos para encontrar la solucion. Ordenamos ambas listas de menor a mayor, y luego comparamos desde la misma posicion, si
nuestra talla seleccionada le queda al jugador actual. En caso de que no, comparamos al siguiente jugador con la ultima equipacion no usada.

COSTE: Iteramos N veces sobre el vector para saber que ciudades podemos defender, y el coste de ordenar un vector de menor a mayor es O(NlogN) siendo N el tamaño
del vector -> O(N log N + M log M + max(M,N)) siendo N el numero de jugadores y M el numero de equipaciones disponibles

COSTE EN ESPACIO ADICIONAL: O(M + N) siendo N el numero de jugadores y M el numero de equipaciones disponibles

@ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    int N = 0, M = 0; cin >> N >> M;
    if (!std::cin) return false;

    vector<int> jugadores(N);
    int valor = 0;

    for (int i = 0; i < N; i++) {
        cin >> valor;
        jugadores[i] = valor;
    }

    vector<int> equipaciones(M);

    for (int i = 0; i < M; i++) {
        cin >> valor;
        equipaciones[i] = valor;
    }


    //ordenamos ambos vectores de menor a mayor para ver cuantas equipaciones les pueden quedar a los jugadores

    sort(jugadores.begin(), jugadores.end());
    sort(equipaciones.begin(), equipaciones.end());

    int num_pedidos = 0, ultimaEquipacion = 0;
    int i = 0, j = 0;

    while (i < N && j < M) {
        //si la equipacion actual le queda al jugador actual pasamos a la siguiente equipacion y jugador
        if (equipaciones[j] == jugadores[i] || equipaciones[j] == jugadores[i] + 1) {
            num_pedidos++;
            i++;
            j++;
        }
        else if(equipaciones[j] < jugadores[i]){ // si la esquipacion es menor que el jugador actual, pasamos a la siguiente equipacion
            j++;
        }
        else if (equipaciones[j] > jugadores[i]) { // si la equipacion es mayor que el jugador, probamos con el siguiente jugador
            i++;
        }
    }
  
    cout << N - num_pedidos << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("8_3.in");
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