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
Para resolver el ejercicio necesitamos pensar una estrategia voraz que nos permita resolver el problema. Para ello ordenaremos a las personas en orden creciente
en funcion de su peso, y las organizaremos en parejas si su peso total no supera el limite. En caso de que no añadiremos una silla y eliminamos ambas personas,
si supera el peso, entonces añadimos una silla y nos quedamos con el que tenga menor peso.

COSTE: Iteramos N veces sobre el vector para recorrer todos los trabajos y ver si cumplen con el intervalo, y el coste de ordenar un vector de menor a mayor 
es O(NlogN) siendo N el tamaño del vector -> O(N log N + N) = O(N log N) siendo N el numero de personas 

COSTE EN ESPACIO ADICIONAL: O(N) siendo N el numero de personas trabajos 

@ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
    int P = 0, N = 0; cin >> P >> N;

    if (P == 0 && N == 0) return false;

    vector<int> personas(N);

    int peso = 0;

    for (int i = 0; i < N; i++) {
        cin >> peso;
        personas[i] = peso;
    }

    sort(personas.begin(), personas.end());

    int i = 0, j = N - 1, sillas = 0;

    while (i <= j) {
        if (personas[i] + personas[j] <= P) {
            i++;
        }
        j--;
        sillas++;
    }

    cout << sillas << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("9_4.in");
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