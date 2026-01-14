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

maxTrozos(i,j) = nº de dias en los que podremos disfrutar el bizocoho si los trozos tienen fruta y son iguales entra las posiciones i j

    - Caso recursivo: 
       maxTrozos(i,j) = maxTrozos(i , j)                                                                                si j - i >= 2
       maxTrozos(i,j) = MAX(maxTrozos(i + 1, j - 1) + t_i, maxTrozos(i, i + 1) + t_i, maxTrozos(j - 1, j) t_i )         si j - i > 2

    -Siendo:
        -t_i: si ambos trozos son iguales : v[i] == v[j]  && v[i] > 0 && v[j] > 0, entonces t_i = 1, en otro caso es 0
    - Caso base:
        maxTrozos(i,j) = 0 si i >= j porque nos hemos acabado los trozos

    - Llamada inicial : maxTrozos(0, N-1);


usamos progamacion dinamica descendente por recursion para obtener todas las soluciones posibles, rellenando las diagonales pares de izquierda a derecha. 
Se puede implementar con programacion dinamica ascendenete, usando una matriz y recorriendola por las diagonales pares

Coste: Recorremos la mitad de la matriz, pero igualmente no afecta al rendimiento, el coste sigue siendo cuadratico -> O(N^2) siendo N el numero de trozos de bizcocho

Coste en espacio adicional: O(N^2) porque usamos una matriz para guardar la solucion.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


// calcula la mayor cantidad de trozos iguales que podemos tomar cumpliendo las restricciones en la matriz [i][j]
int maxTrozos(vector<int> const& bizcocho, int i, int j, Matriz<int>& sol) {
    
    if (i >= j) return 0;

    if (sol[i][j] != -1) return sol[i][j];

    int iz = 0, dr = 0, ambos = 0;

    if (bizcocho[i] == bizcocho[j] && bizcocho[i] > 0 && bizcocho[j] > 0) { // cogemos un trozo de cada extremo
        ambos++;
    }

    ambos += maxTrozos(bizcocho, i + 1, j - 1, sol);

    if (bizcocho[i] == bizcocho[i + 1] && bizcocho[i] > 0 && bizcocho[i + 1] > 0) { // cogemos 2 trozos del extremo izquierdo
        iz++;
    }

    iz += maxTrozos(bizcocho, i + 2, j, sol);

    if (bizcocho[j] == bizcocho[j - 1] && bizcocho[j] > 0 && bizcocho[j - 1] > 0) { // cogemos 2 trozos del extremo derecho
        dr++;
    }

    dr += maxTrozos(bizcocho, i, j - 2, sol);

    // Nos quedamos con la mejor combinacion hasta ahora
    sol[i][j] = max({ iz,dr,ambos });

    return sol[i][j];
}


bool resuelveCaso() {
   // leer los datos de la entrada
    int N; cin >> N;
    if (!cin) return false;

    vector<int> bizcocho(N);

    for (int i = 0; i < N; i++) {
        cin >> bizcocho[i];
    }

    Matriz<int> sol(N,N,-1);
   // resolver el caso posiblemente llamando a otras funciones 
    int res = maxTrozos(bizcocho, 0, N - 1, sol);
    //cout << "\n";
    //cout << sol;
    //cout << "\n";

    cout << res << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("R_16.in");
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
