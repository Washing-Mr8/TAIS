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

playlist(i,j) = nº de canciones que son compatibles entre la lista l1 y l2 entre las posiciones i y j -> 0 <= i <= j < max(l1.size(), l2.size())

    Casos recursivos:
        - playlist(i, j) = 1 + playlist(i + 1, j + 1)                       si l1[i] == l2[j]
        - playlist(i, j) = max( playlist(i + 1, j), playlist(i, j + 1))     si l1[i] != l2[j]
        
    Casos base:
       - playlist(i, N) = playlist(N, j) = 0

    Llamada inicial:

    Siendo: l1 la lista de canciones 1 y l2 la lista de canciones 2

 COSTE: para encontrar la solucion necesitamos recorrer una matriz de tamaño N*N con accesos de orden constante O(1)->  O(N * N) siendo N la cantidad de cubos
 
 COSTE EN ESPACIO ADICIONAL: O(N * N) siendo N la cantidad de cubos

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

vector<string> playlist(const vector<string>& l1, const vector<string>& l2) {
    int N = l1.size(); int M = l2.size();

    Matriz<int> Sol(N + 1, M + 1, 0);

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (l1[i - 1] == l2[j - 1]) {
                Sol[i][j] = 1 + Sol[i - 1][j - 1];
            }
            else {
                Sol[i][j] = max(Sol[i - 1][j], Sol[i][j - 1]);
            }
        }
    }

    //reconstruimos la solucion
    //cout << Sol;
    vector<string> lista;

    int i = N, j = M;

    while (i > 0 && j > 0) {
        if (l1[i - 1] == l2[j - 1]) {
            lista.push_back(l1[i - 1]);
            --i; --j;
        }
        else if (Sol[i - 1][j] > Sol[i][j - 1]) { //ignoramos el elemento actual de la lista 1 para obtener la mayor lista
            --i;
        }
        else {  //ignoramos el elemento actual de la lista 2 para obtener la mayor lista
            --j;
        }
    }

    return lista;
}


bool resuelveCaso() {
    // leemos la entrada
    string linea; getline(cin,linea);

    if (!std::cin) return false;

    // leer el resto del caso y resolverlo
    vector<string> l1;
    string cancion = "";
    for (auto letra : linea) {
        if (letra != ' ') {
            cancion.push_back(letra);
        }
        else {
            l1.push_back(cancion);
            cancion = "";
        }
    }
    l1.push_back(cancion);
    cancion = "";

    getline(cin, linea);

    vector<string> l2;
    for (auto letra : linea) {
        if (letra != ' ') {
            cancion.push_back(letra);
        }
        else {
            l2.push_back(cancion);
            cancion = "";
        }
    }
    l2.push_back(cancion);

    vector<string> sol = playlist(l1, l2);
    //la imprimimos al reves porque reconstruimos la solucion desde el final hasta el principio
    for (int i = sol.size() - 1; i >= 0; --i) {
        cout << sol[i] << " ";
    }
 
    cout <<  "\n";
  
  return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
  // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
  ifstream in("B_L.in");
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
