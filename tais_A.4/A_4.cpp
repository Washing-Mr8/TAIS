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

Necesitamos una matriz auxiliar para saber que el valor de cada casilla del tablero: 

maxCantidad(i,j) = maxima cantidad posible de la suma obtenida al movernos desde la fila i - 1, hasta la 1, de 1 a j columnas 

    Casos recursivos:
        - maxCantidad(i ,j) = maxCantidad(i - 1, j)                                                                 si i <= 1
        - maxCantidad(i ,j) = max( maxCantidad(i - 1, j - 1), maxCantidad(i - 1, j), maxCantidad(i - 1, j + 1) )    si i > 1

    Casos base:
        - Dado que la matriz es N*N, y 3 <= N < 500, los casos basicos serian buscar la solucion mediante la funcion maxCantidad(N,N)
        - maxCantidad(i ,j) = 0 si i < 1 && i > N && j < 1 && j > N 
    
 COSTE: Para resolver el problema necesitamos utilizar una matriz auxiliar te tamaño N*N para leer los datos. una vez leidos, necesitamos quedarnos con la ultima
 fila que contendra las sumas maximas de las posibles combianaciones en cada iteracion. Podemos usar un vector de tamaño N + 1 para quedarnos con dicha suma en 
 cada iteracion y usar una variable aux para quedarnos con el valor del extremo, que tras cada iteracion de j,  se solapa
 
 COSTE EN ESPACIO ADICIONAL: Sin contar la matiz de entrada (N*N), utilizamos un vector de tamaño N + 1 simulando la primera fila de la solucion -> 
 el coste adicional seria de O(N) porque solo necesitamos ver las posibles soluciones de 0 <= i <= N

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

int enCasilla( const vector<int>& v, int j) {
    int N = v.size();

    if (j < 0 || j > N) {
        return 0;
    }
    else {
        return v[j];
    }
}

bool resuelveCaso() {
    // leemos la entrada
    int N; cin >> N;
    if (!cin) return false;

    // leer el resto del caso y resolverlo
    Matriz<int> tablero(N, N, 0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> tablero[i][j];
        }
    }

    vector<int> maxCantidad(N);

    int maximo = -1, indice = -1, derecha = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = N - 1; j >= 0; --j) {

            int iz = tablero[i][j] + enCasilla(maxCantidad, j - 1);
            int arriba = tablero[i][j] + enCasilla(maxCantidad, j);
            int dr = tablero[i][j] + derecha;
            //como vamos de derecha a izquierda, el valor de la derecha se vera actualizado por el maximo de los 3, entonces tenemos que guardarlo
            derecha = maxCantidad[j];
            maxCantidad[j] = max(iz, arriba);
            maxCantidad[j] = max(maxCantidad[j], dr);

            if (i == N - 1) {
                if (maxCantidad[j] >= maximo) {
                    maximo = maxCantidad[j];
                    indice = j + 1;
                }
            }
        }
    }

    cout << maximo << ' ' << indice << "\n";
  
  return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
  // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
  ifstream in("A_4.in");
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
