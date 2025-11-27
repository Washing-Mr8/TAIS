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

#include "Matriz.h"

using namespace std;

/*@ <answer>

Para resolver el ejercicio necesitamos aplicar una estrategia de programacion dinamica para encontrar la solucion mas eficiente al problema.


maxComida = maxima cantidad de comida que puede comer una vaca ante Devoradora teniendo que elegir entre los cubos del 1 a j

    Casos recursivos:
        - maxComida(i, j) = c_i + maxComida(i + 1, j)       si c_i + 1 > c_j
        - maxComida(i, j) = c_i + maxComida(i + 1, j - 1)   si c_i + 1 < c_j
        - maxComida(i, j) = c_j + maxComida(i, j - 1)       si c_i < c_j - 1
        - maxComida(i, j) = c_j + maxComida(i + 1, j - 1)   si c_i > c_j - 1
  
    Casos base:
        - maxComida(i, j) = c_i si i == j
        - maxComida(i, j) =  0  si i < j

    Llamada inicial: maxComida(0, N - 1)

    Siendo: c_i la cantidad del cubo i y c_j la cantidad del cubo j

 COSTE: para encontrar la solucion necesitamos recorrer una matriz de tamaño N*N con accesos de orden constante O(1)->  O(N * N) siendo N la cantidad de cubos
 
 COSTE EN ESPACIO ADICIONAL: O(N * N) siendo N la cantidad de cubos

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

int raciones(const vector<int> &cubos) {
    int N = cubos.size();

    Matriz<int> cantidad(N, N, 0);

    for (int i = 0; i < N; i++) { //caso base de i == j es decir rellenamos la diagonal
        cantidad[i][i] = cubos[i];
    }

    int c_i = 0, c_j = 0;

    for (int i = N; i >= 0; --i) {
        for (int j = i + 1; j < N; ++j) {
            if (cubos[i + 1] > cubos[j]) {
                c_i = cantidad[i + 2][j];
            }
            else {
                c_i = cantidad[i + 1][j - 1];
            }
            if (cubos[i] < cubos[j - 1]) {
                c_j = cantidad[i][j - 2];
            }
            else {
                c_j = cantidad[i + 1][j - 1];
            }
            cantidad[i][j] = max(cubos[i] + c_i, cubos[j] + c_j);
        }
    }

    return cantidad[0][N - 1];
}


bool resuelveCaso() {
    // leemos la entrada
    int N; cin >> N;

    if (N == 0) return false;

    // leer el resto del caso y resolverlo
    vector<int> cubos(N);

    for (int i = 0; i < N; i++) {
        cin >> cubos[i];
    }

    int maxCantidad = raciones(cubos);
 
    cout << maxCantidad <<  "\n";
  
  return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
  // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
  ifstream in("B_4.in");
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
