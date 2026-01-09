/*@ <authors>
 *
 * E42 Washington Morocho Lema
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <numeric>
#include <queue>
#include <algorithm>
using namespace std;

#include "Matriz.h"

/*@ <answer>

Para resolver el problema necesitamos pensar en una estrategia de programacion dinamica para resolverlo eficientemente

alquiler(i,j) = coste minimo del viaje en canoa desde el poblado i al j

    - Caso recursivo: 
       alquiler(i, j) = min_{i < k <= j}(Cik + alquiler(k, j))

    - Caso base:
        alquiler(i,i) = 0 

    - Llamada inicial : alquiler(0,N-1);

    - Siendo: 
        Cik : coste de vaijar en canoa desde el poblado i al k

Coste: Utilizamos programacion dinamica ascendente. Tras leer la entrada usaremos los datos que estan por encima de la diagonal principal, que seran 0 porque son casos base.
Tras rellenar la diagonal, aplicamos la funcion recursiva apra averiguar el coste minimo para cada poblado. El coste ascenderia a O(N*N*N), siendo N el numero de poblados,
debido a que recorremos 3 veces la matriz de forma completa (por lo menos la mitad superio) par calcular el minimo coste

Coste en espacio adicional: Solo usamos la matriz de entrada y salida, por lo tanto es constante -> O(1)

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

const int INF = 1000000000;

Matriz<int> alquilerCanoas(const Matriz<int>& m, int N) {
    Matriz<int> sol(N, N, INF);

    for (int i = 0; i < N; i++) {
        sol[i][i] = 0;
    }

    for (int d = 1; d < N ; ++d) { // recorre diagonales
        for (int i = 0; i < N - d; ++i) { // recorre elementos de diagonal
            int j = i + d;

            for (int k = i+1; k <= j; ++k) {
                sol[i][j] = min(sol[i][j], m[i][k] + sol[k][j]);
            }
        }
    }
    return sol;
}


bool resuelveCaso() {
   // leer los datos de la entrada
    int N; cin >> N;
    if (!cin) return false;

    Matriz<int> m(N, N ,0 );

    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N ; j++) {
            cin >> m[i][j];
        }
    }

   // resolver el caso posiblemente llamando a otras funciones 
  
    Matriz<int> sol = alquilerCanoas(m, N);
   // escribir la solución
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            cout << sol[i][j] << " ";
        }
        cout << "\n";
    }
    cout  << "\n";
    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("R_12.in");
   if (!in.is_open())
      cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
   auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

   while (resuelveCaso());

   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   cin.rdbuf(cinbuf);
#endif
   return 0;
}
