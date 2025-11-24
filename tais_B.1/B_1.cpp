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

Necesitamos un vector auxiliar para saber que el valor de cada tesoro hundido: 

tesoro(i,j) = maximo valor que podemos recoger en el barco con tiempo limite j considerando los objetos de 1 a i

    Casos recursivos:
        - tesoro(i, j) = tesoro(i - 1, j)                                        si t_i > j
        - tesoro(i, j) = max( tesoro(i - 1, j), tesoro(i - 1, j - t_i) + v_i)    si t_i <= j

    Casos base:
        - tesoro(0, j) = 0 si 0 <= j <= T -> es decir no hay ningun tesoro que buscar
        - tesoro(i, 0) = 0 si 0 <=i <= N -> es decir no tenemos bombonas de oxigeno para bucear
    Llamada inicial:
        tesoro(N,T)
    Siendo:
        - t_i: el tiempo que se tarda en alcanzar el objeto i y volver al barco (aprox 3 * p_i)
        - p_i: la profundidad a la que esta el objeto i
        - v_i: el valor en oro del objeto i
    
 COSTE: Para resolver el problema necesitamos utilizar una matriz auxliar para realizar un recorrido ascendente (de derecha a izquierda) al buscar la solucion.
 Leemos los cofres cada uno con u cantidad de oro y profundidad, y una matriz definida por el numero N de cofres y T del tiempo que podemos estar bajo el agua.
 En la funcion recursiva, necesitamos comparar la solucion con cada posible cofre y a que profundidad se encuentra, cuyo tiempo de recoleccion sera de 3 por su
 profundidad (ya que se tarda p en bajr y 2 p en subir). Finalmente reconstruimos las soluciones recorriendo toda la matriz en el caso peor.
 El coste seria de O(N * T) -> Siendo N el numero de cofres y T el tiempo de oxigeno que tenemos
 
 COSTE EN ESPACIO ADICIONAL: utilizamos una matriz auxiliar y un vector de cofres para reconstruir la solucion : O(N*T) ->  Siendo N el numero de cofres y T el 
 tiempo de oxigeno que tenemos

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

struct Cofre {
    int profundidad;
    int cantidad;
};

int tesoro_rec(const vector<Cofre>& objetos, int i, int j, Matriz<int> & tesoro ) {

    if (tesoro[i][j] != -1) { //subproblema ya resuelto
        return tesoro[i][j];
    }

    if (i == 0) {
        tesoro[i][j] = 0;
    }
    else if (objetos[i - 1].profundidad * 3 > j) {
        tesoro[i][j] = tesoro_rec(objetos, i - 1, j, tesoro);
    }
    else {
        tesoro[i][j] = max(tesoro_rec(objetos, i - 1, j, tesoro), tesoro_rec(objetos, i - 1, j - (objetos[i-1].profundidad *  3), tesoro) + objetos[i-1].cantidad);
    }

    return tesoro[i][j];
}

bool resuelveCaso() {
    // leemos la entrada
    int T, N; cin >> T >> N;
    if (!cin) return false;

    // leer el resto del caso y resolverlo
    vector<Cofre> tesoros(N);

    for (int i = 0; i < N; i++) {
        cin >> tesoros[i].profundidad >> tesoros[i].cantidad;
    }

    Matriz <int> tesoro(N + 1, T + 1, -1);
    
    int cantidad = tesoro_rec(tesoros, N, T, tesoro);
   
    vector<Cofre> sol;

    //reconstruimos la solucion
    int i = N, j = T, aux = 0;
    while (i > 0 && j > 0 && aux < cantidad) {
        if (tesoro[i][j] != tesoro[i - 1][j]) {
            sol.push_back(tesoros[i - 1]);
            aux += tesoros[i - 1].cantidad;
            j -= (tesoros[i - 1].profundidad * 3);
        }
        --i;
    }
    cout << cantidad<< "\n";
    cout << sol.size() << "\n";

    for (int i = 0; i < sol.size(); i++) {
        cout << sol[i].profundidad << " " << sol[i].cantidad << "\n";
    }

    cout << "---\n";
  
  return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
  // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
  ifstream in("B_1.in");
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
