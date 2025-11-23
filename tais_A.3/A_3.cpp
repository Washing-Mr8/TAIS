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

Necesitamos una matriza auxiliar para saber que intersecciones estan en obras: 

minCaminos(i,j) = minimo nº de caminos para llegar al extremo sureste de la ciudad dada, con calles de este a oeste de 1 a i y calles de norte a sur de 1 a j

    Casos recursivos:
        - minCaminos(i,j) = 0                                               si calles[i][j] == 'X'
        - minCaminos(i,j) =  minCaminos(i - 1, j) + minCaminos(i, j - 1)    si calles[i][j] == '.'

    Casos base:
        - minCaminos(i,j) = 1 si i = 1 && j = 1 -> la interseccion inicial
        - minCaminos(i,j) = 0 si i < 1 && i > N && j < 1 && j > M 

    Siendo:
        -> calles[i][j] las intersecciones de la ciudad
        -> 1 <= i < N && 1 <= j < 50

 COSTE: Una vez leido los datos, para construir la solucion solo nos interesa quedarnos con el ultimo tramo de las calles de norte a sur j. Para ello 
 necesitamos iterar sobre todas las intersecciones para ver si estan en obras ('X') o no ('.'). En caso de que este en obras no se podra pasar por ahi (0). 
 El coste seria de O(N*M) 
 
 COSTE EN ESPACIO ADICIONAL: Sin contar la matiz de entrada (N*M), utilizamos un vector de tamaño M + 1 simulando la ultima calle de norte a sur -> 
 el coste adicional seria de O(M) porque solo necesitamos ver las posibles soluciones de 0 <= i <= M

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

bool resuelveCaso() {
    // leemos la entrada
    int N,M;
    cin >> N >> M;
    if (!cin)
        return false;

    // leer el resto del caso y resolverlo
    Matriz<char> calles(N, M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> calles[i][j];
        }
    }

    //buscamos el mejor camino en la ultima calle de norte a sur
    vector <int> minCamino(M + 1, 0);
    minCamino[1] = 1;

    for (int i = 0; i < N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (calles[i][j - 1] != 'X') {
                minCamino[j] = minCamino[j] + minCamino[j-1];
            }
            else {
                minCamino[j] = 0;
            }
        }
    }

    int minimo = minCamino[M];

    cout<< minimo << "\n";
  
  return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
  // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
  ifstream in("A_3.in");
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
