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

Necesitamos un vector auxiliar para saber que el valor de cada aibofobia hundido: 

aibofobia(i,j) = minimo nº de letras que hay que añadir a la palabra con rango de [i,j] para que sea un palindromo
    Casos recursivos:
        - aibofobia(i, j) = aibofobia(i + 1, j - 1) + 2                            si palabra[i] == palabra[j]
        - aibofobia(i, j) = min( aibofobia(i + 1, j), aibofobia(i, j - 1) ) + 1    si palabra[i] != palabra[j]

    Casos base:
        - aibofobia(i, i) = 1 si j == i-> es decir es la misma letra y por lo tanto palindromo
        - aibofobia(i, j) = 0 si i > j -> es decir que la letra de i ha pasado a la letra j

    Llamada inicial: aibofobia(0, N - 1) siendo: 0 <= i <= j < N
    
 COSTE: 
 
 COSTE EN ESPACIO ADICIONAL: 

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>


string reconstruir(string palabra, const Matriz<int> &aibo, int i, int j) {
    
    if (i > j) 
        return "";
    else if (i == j) 
        return { palabra[i] };
    else 
        if (palabra[i] == palabra[j]) {
            return palabra[i] + reconstruir(palabra, aibo, i + 1, j - 1) + palabra[j];
        }
        else if (aibo[i][j] == aibo[i][j-1] + 1) { //quitar la j consigue un mejor resultado
            return palabra[j] + reconstruir(palabra, aibo, i, j - 1) + palabra[j];

        }
        else { //quitar la i consigue un mejor resultado
            return palabra[i] + reconstruir(palabra, aibo, i + 1, j) + palabra[i];
        }
}


int aibofobia(string palabra, Matriz<int> aibo) {
    int N = palabra.size();
    for (int i = N - 2; i >= 0; --i) {
        for (int j = i + 1; j < N; ++j) {
            if (palabra[i] == palabra[j]) {
                aibo[i][j] = aibo[i + 1][j - 1];
            }
            else {
                aibo[i][j] = min(aibo[i + 1][j], aibo[i][j-1]) + 1;
            }
        }
    }
    return aibo[0][N - 1];
}

bool resuelveCaso() {
    // leemos la entrada
    string palabra; cin >> palabra;
    if (!cin) return false;

    // leer el resto del caso y resolverlo
    int N = palabra.size();

    Matriz<int> aibo(N, N, 0);

    int minimo = aibofobia(palabra, aibo);
    string sol = palabra;

    if (minimo != 0)
        sol = reconstruir(palabra, aibo, 0, N - 1); //reconstruimos la solucion
    
    cout << minimo << " " << sol << "\n";
  
  return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
  // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
  ifstream in("B_2.in");
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
