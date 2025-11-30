/*@ <authors>
 *
 * E42 Washington Morocho Lema
 * 
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <climits>
#include <numeric>
#include <string>

#include "Matriz.h"

using namespace std;

/*@ <answer>

Para resolver el ejercicio necesitamos aplicar una estrategia de programacion dinamica para encontrar la solucion mas eficiente al problema.

minCortes(i,j) = nº de canciones que son compatibles entre la lista l1 y l2 entre las posiciones i y j -> 0 <= i <= j < max(l1.size(), l2.size())

    Casos recursivos:
        ->  i < j-1 : minCortes(i, j) = i < k < j min( 2 * ( M[j] - M[i] ) + f(i, k) + f(k, j))                 
        
    Casos base:
       - minCortes(i, i + 1) = 0

    Llamada inicial: minCortes(0, N + 1)


 COSTE: para encontrar la solucion necesitamos recorrer una matriz de tamaño N*N con accesos de orden constante O(1)->  O(N * N) siendo N la cantidad de cubos
 
 COSTE EN ESPACIO ADICIONAL: O(N * N) siendo N la cantidad de cubos

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

const int INF = 1000000000;

int minCortes(const vector<int>& cortes) {
    int N = cortes.size();
    Matriz<int> M(N + 1, N + 1, 0);

    for (int d = 2; d <= N - 1; ++d) {
        for (int i = 0; i < N - d; ++i) {
            int j = d + i;
            M[i][j] = INF;
            for (int k = i + 1; k < j; ++k) {
                int temp = M[i][k] + M[k][j] + 2 * (cortes[j] - cortes[i]);
                if (temp < M[i][j]) {
                    M[i][j] = temp;
                }
            }
        }
    }
    //cout << M;
    return M[0][N - 1];
}

bool resuelveCaso() {
    // leemos la entrada
    int L, N; cin >> L >> N;
    if (L == 0 && N == 0) return false;

    // leer el resto del caso y resolverlo
    vector<int> cortes(N + 2);

    cortes[0] = 0;
    cortes[N + 1] = L;
    for (int i = 1; i <= N; ++i) {
        cin >> cortes[i];
    }
 
    int minimo = minCortes(cortes);

    cout << minimo << "\n";
  
  return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
  // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
  ifstream in("C_1.in");
  if (!in.is_open())
    cout << "Error: no se ha podido abrir el archivo de entrada." << endl;
  auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
  
  // Resolvemos
  while (resuelveCaso());
  
  // para dejar todo como estaba al principio
#ifndef DOMJUDGE
  cin.rdbuf(cinbuf);
#endif
  return 0;
}
