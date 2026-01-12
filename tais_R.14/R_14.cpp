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

maxBeneficio(i) = maximo valor obtenido al sumar los beneficios de los locales de 0 a i con una separacion s

    - Caso recursivo: 
       maxBeneficio(i) = maxBeneficio(i - 1)                                si D_ki < S
       maxBeneficio(i) = MAX(maxBeneficio(i - 1), maxBeneficio(k) + Bi)     si D_ki >= S

    - Caso base:
        maxBeneficio(0) = 0, porque no existe un local en esa posicion

    - Llamada inicial : maxBeneficio(N);

    - Siendo: 
        D_ki la distancia desde el local k hasta el local i
        Bi: el beneficio del local i

Leemos los datos y utilizamos una estructura Local que nos ayudara a encontrar el maximo beneficio posible. Iteramos sobre el vector empezando de izquierda  a derecha y
segun vamos avanzando, recorremos las k : 0 <= k < i : posiciones anteriores para buscar el primer local que cumple con la restriccion D_ki >= S (es decir que todos los
locales tienen que estar a una distancia mayor o igual a S). 
Finalmente para reconstruirla realizamos el mismo proceso empezando por el final, ordenando el vector resultante en orden creciente para que coincida con la salida solicitada.

Coste: En el caso peor recorremos N veces el vector por completo otras N veces-> O(N*N) siendo N el numero de locales

Coste en espacio adicional: O(N) porque usamos un vector para guardar y reconstruir la solucion.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


struct Local {
    int posicion;
    int beneficio;
};

pair<int,vector<int>> maxBeneficio(const vector<Local> &locales, int s ) {
    int N = locales.size();
    vector<int> sol(N + 1, 0);

    for (int i = 1; i <= N; i++) {
        int k = i - 2;
        int temp = locales[i- 1].beneficio;
        bool primero = false;
        while (k >= 0 && !primero) {
            if (locales[i - 1].posicion - locales[k].posicion >= s) {
                temp += sol[k+1];
                primero = true;
            }
            --k;
        }

        sol[i] = max(sol[i - 1], temp); // la solucion actual es el mejor valor entre 
    }

    //reconstruimos
    int i = N;
    vector<int> posiciones;
    while (i > 0) {
        int elijo = locales[i - 1].beneficio;
        int indice = 0;

        int k = i - 2;
        bool elegido = false;
        while (k >= 0 && ! elegido) {
            if (locales[i - 1].posicion - locales[k].posicion >= s) {
                indice = k + 1;
                elijo += sol[indice];
                elegido = true;
            }
            --k;
        }

        if (sol[i] == elijo) {
            posiciones.push_back(locales[i - 1].posicion);
            i = indice;
        }
        else {
            --i;
        }
    }

    sort(posiciones.begin(), posiciones.end());

    return { sol[N], posiciones};
}


bool resuelveCaso() {
   // leer los datos de la entrada
    int N, S; cin >> N >> S;
    if (!cin) return false;

    vector<Local> locales(N);

    for (int i = 0; i < N; i++) {
        cin >> locales[i].posicion;
    }

    for (int i = 0; i < N; i++) {
        cin >> locales[i].beneficio;
    }

   // resolver el caso posiblemente llamando a otras funciones 
    auto sol = maxBeneficio(locales, S);

    //falta reconstruir
    vector<int> posiciones;

    cout << sol.first << ": ";

    for (int pos : sol.second) {
        cout << pos << " ";
    }

    cout << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("R_14.in");
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
