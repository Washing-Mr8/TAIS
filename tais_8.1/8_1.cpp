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

using namespace std;

/*@ <answer>
Para resolver el problema necesitamos pensar en un estrategia voraz que nos permita resolver el problema. Para ello usaremos un vector para guardar las posiciones
en las que hay agujeros en la manguera. Antes de comenzar a iterar, ponemos un parche al primer agujero (que si o si necesita), y luego vamos comparando si la 
posicion del proximo agujero entra dentro del rango de nuestro parche puesto en la ultima posicion.

COSTE: Iteramos N veces sobre el vector para saber que agujeros necesitamos parchar -> O(N) siendo N el numero de agujeros

COSTE EN ESPACIO ADICIONAL: O(N) siendo N el numero de agujeros 

@ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    int N = 0, L = 0; cin >> N >> L;
    if (!std::cin) return false;

    vector<int> agujeros(N);
    int posicion = 0;

    for (int i = 0; i < N; i++) {
        cin >> posicion;
        agujeros[i] = posicion;
    }

    //comenzamos con el primer parche puesto en el primer elemento
    int numParches = 1, ultimaPos = agujeros[0];

    for (int i = 1; i < N; i++){
        if (agujeros[i] > ultimaPos + L) {
            ultimaPos = agujeros[i];
            numParches++;
        }
    }
   
    cout << numParches << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("8_1.in");
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