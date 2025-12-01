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
#include "EnterosInf.h"

using namespace std;

/*@ <answer>

Para resolver el ejercicio necesitamos aplicar una estrategia de programacion dinamica para encontrar la solucion mas eficiente al problema.

formas(i) = nº de maneras en las que se pueden saltar desde el pivote i al N

    Casos recursivos:
        -> formas(i) =  2 <= k <= F + 1 <= i + k <= N : (formas(i + k) )
        
    Casos base:
       - formas(N) = 1 -> es decir se salta ese pivote
¡
    Llamada inicial: formas(1)

 COSTE: usamos programacion dinamica ascendente, y al tener solo un parametro iteramos sobre un vector del tamaño N siendo este el nº de pivotes,
 en cada iteracion comprobamos las diferentes formas de llegar al final con F posibles saltos: O(N^F) con 0 < F < 10 
 
 COSTE EN ESPACIO ADICIONAL:  Como no necesitamos reconstruir la solucion nos podemos quedar con la ultima fila simulada por un vector de tamaño N
 O(N), siendo N el nº de pivotes.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

long long int formas(int N, int F) {
    vector<long long int> sol(N + 1, 0);
    sol[N] = 1;

    for (int i = N - 1; i >= 0; --i) {
        int k = 1;
        while (k <= F + 1 && i + k <= N) {
            sol[i] = (sol[i] + sol[i + k]) % 1000000007;
            ++k;
        }
    }

    return sol[1]; //posibles saltos desde el pivote 1
}

bool resuelveCaso() {
    // leemos la entrada
    int N, F; cin >> N >> F;
    if (N == 0 && F == 0) return false;

    // leer el resto del caso y resolverlo
    auto sol = formas(N, F);

    cout << sol << "\n";

  return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
  // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
  ifstream in("C_4.in");
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
