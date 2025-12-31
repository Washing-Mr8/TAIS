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
using namespace std;

#include "Matriz.h"

/*@ <answer>

Para resolver el problema necesitamos usar programacion dinamica para emplear la funcion recursiva eficientemente

maneras(i,j) = numero de formas posibles de llegar a la casilla [i][j] del tablero

    Casos recursivos:
        maneras(i,j) = maneras(i - 1, j)                                                    si i < 1 && j < 1
        maneras(i,j) = maneras(i - 1 + casilla_ij, j) + maneras(i - 1, j + casilla_ij)          si i > 1 && j > 1

    Caso base:
        maneras(i,j) = 1 si i == N - 1 y j == M - 1 -> es decir siempre hay una forma de llegar a la casilla final

    llamada inicial: maneras(0,0) siendo N el numero de filas y M el numero de columnas

    siendo:
        - casilla_ij: el valor de la casilla en la fila i y columna j

Coste: Necesitamos utilizar programacion dinamica ascendente para recorrer la matriz desde el final de derecha a izquierda para quedarnos con todas las posibles formas
de llegar a la casilla final en la primera posicion de la matriz -> O(N * M) siendo N el numero de filas y M el numero de columnas

Coste en espacio adicional: en este caso no podemos ahorrar en espacio adicional, porque necesitamos plantear saltos verticales y horizontales. O(N * M) siendo N el 
numero de filas y M el numero de columnas


 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int numManeras(const Matriz<int>& matriz, int N, int M) {
    
    Matriz<int> sol(N, M, 0);
    sol[N - 1][M - 1] = 1; // caso base: hemos llegado al final

    for (int i = N - 1; i >= 0; i--) {
        for (int j = M - 1; j >= 0; j--) {
            int salto = matriz[i][j];

            if (i + salto < N) {
                sol[i][j] += sol[i + salto][j];
            }

            if (j + salto < M) {
                sol[i][j] += sol[i][j + salto];
            }
        }
    }

    return sol[0][0];
}

bool resuelveCaso() {
   // leer los datos de la entrada
    int N, M; cin >> N >> M;
    if (!cin) return false;

    Matriz<int> matriz(N, M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> matriz[i][j];
        }
    }

   // resolver el caso posiblemente llamando a otras funciones 
    int sol = numManeras(matriz, N, M);

   // escribir la solución
    cout << sol << "\n";
    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("R_7.in");
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
