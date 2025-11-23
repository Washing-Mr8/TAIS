/*@ <authors>
 *
 * E42 Washington Morocho Lema
 * E16 Ruben Dolera Mancebo
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
#include "EnterosInf.h"

using namespace std;

/*@ <answer>

Primero veamos si es posible conseguir los puntos con los sectores dados:

    minDardos(i,j) = minimo nº de dardos para alcanzar la puntuacion j dada, con los sectores de puntuacion desde 0 a i

    Casos recursivos:
        - minDardos(i,j) = minDardos(i - 1, j)                                      si d_i > j
        - minDardos(i,j) = min( minDardos(i - 1, j), minDardos( i, j - d_i) + 1 )  si d_i <= j

    Casos base:
        - minDardos(1,j) = INF si j > 1
        - minDardos(i,1) = INF si i > 1

    Siendo:
        -> d_i el numero de dardos en la posicion i
        -> 1 <= i < 1.000 && 1<= j < 50.000

 COSTE: Para analizar las posibles soluciones necesitamos iterar D veces sobre las posibles puntuaciones hasta llegar a P (la puntuacion objetivo), y para 
 reconstruir la solucion necesitamos iterar otra vez sobre el valor maximo entre P o D. Coste: O(D * P) siendo D el numero de sectores de la diana y 
 P la puntuacion a alcanzar

 COSTE EN ESPACIO ADICIONAL: Al no utilizar una matriz de D * P, solo utilizamos un vector de tamaño P + 1 -> O(P) porque solo necesitamos ver las posibles
 soluciones de 1 <= i <= P

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

const int INF = 100000; // porque el maximo es 50.000

bool resuelveCaso() {
    // leemos la entrada
    int P, D;
    cin >> P >> D;
    if (!cin)
        return false;

    // leer el resto del caso y resolverlo
    vector<int> diana(D);

    for (int i = 0; i < D; i++) {
        cin >> diana[i];
    }

    vector<int> minDardos(P + 1, INF);
    minDardos[0] = 0;

    for (int i = 1; i <= D; i++) {
        for (int j = diana[i - 1]; j <= P; j++) {
            minDardos[j] = min(minDardos[j], minDardos[j - diana[i - 1]] + 1);
        }
    }

    int numDardos = minDardos[P];

    if (numDardos != INF) { // Si para conseguir la posicion no necesitamos dardos INF, reconstruimos la solucion
        
        cout << numDardos << ":";
        int i = D, j = P;
        while (j > 0) {
            if (diana[i - 1] <= j && minDardos[j] == minDardos[j - diana[i - 1]] + 1) {
                cout << " " << diana[i - 1];
                j = j - diana[i - 1];
            }
            else {
                i--;
            }
        }
    }
    else {
        cout << "Imposible";
    }

    cout << "\n";
  
  return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
  // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
  ifstream in("A_2.in");
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
