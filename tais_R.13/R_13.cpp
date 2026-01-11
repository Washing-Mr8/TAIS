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

producto(i,j) = conjunto de letras {a,b y c} que es posible obtener multiplicando los caracteres i y j

    - Caso recursivo: 
       producto(i, j) = min_{i < k <= j}(Pik + producto(k + 1, j))

    - Caso base:
        producto(i,i) = cadena[i] , es decir la letra en esa posicion

    - Llamada inicial : producto(0,N-1);

    - Siendo: 
        Pik : letra obtenida al multiplicar el caracter i y el k

    Es decir, probamos todos los puntos de corte k donde podemos dividir la cadena en dos partes: s[i..k] y s[k+1..j]. Para cada combinacion de caracteres posibles 
    en la parte izquierda (x) y derecha (y), aplicamos la tabla de multiplicación y añadimos el resultado al conjunto sol(i,j).

Coste: Utilizamos programacion dinamica ascendente. Tras leer la entrada usaremos los datos que estan por encima de la diagonal principal, que seran la letra correspondiente
de la cadena porque son casos base. Tras rellenar la diagonal, aplicamos la funcion recursiva para averiguar las posibles letras que podemos obtener al multiplicar los 
productos ya calculados anteriormente usando la tabla de referencia. El coste ascenderia a O(N^3) * (X^2), siendo N el tamaño de la cadena y X el numero de letras disponibles,
debido a que recorremos 3 veces la matriz de forma completa (por lo menos la mitad superio) para calcular todas las posibles combinaciones multiplicando por x caracteres 
2 veces -> aprox O(N^3)

Coste en espacio adicional:  O(N*N) para la matriz de strings. Cada string puede contener hasta 3 caracteres, por lo que el espacio total es O(N*N * 3) = O(N*N).

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


/*
bool producto(const string& p, const vector<vector<char>>& mult) {
    int N = p.size();
    Matriz<char> sol(N, N, 'd');

    for (int i = 0; i < N; i++) {
        sol[i][i] = 0;
    }

    for (int d = 1; d < N ; ++d) { // recorre diagonales
        for (int i = 0; i < N - d; ++i) { // recorre elementos de diagonal
            int j = i + d;

            for (int k = i; k <= j-1; ++k) {
                //sol[i][j] = min(sol[i][j], m[i][k] + sol[k][j]);
            }
        }
    }
    return sol[0][N-1] == 'a';
}
*/
char indice(char x) {
    switch (x) {
    case 'a': { return 0; } break;
    case 'b': { return 1; } break;
    case 'c': { return 2; } break;
    default:break;
    }
}

bool contiene(const string& cadena, char x) {
    for (int i = 0; i < cadena.size(); ++i) {
        if (cadena[i] == x) {
            return true;
        }
    }
    return false;
}

bool producto(const string& cadena, const vector<vector<char>>& tabla) {
    int N = cadena.size();
    Matriz<string> sol(N, N, "");

    // caso base: rellenamos la diagonal principal
    for (int i = 0; i < N; i++) {
        sol[i][i] = string(1, cadena[i]);
    }

    for (int d = 1; d < N; ++d) { 
        for (int i = 0; i < N - d; ++i) {
            int j = i + d;

            for (int k = i; k < j; ++k) {
                // Recuperamos los POSIBLES caracteres de la izquierda y la derecha
                string izquierda = sol[i][k];
                string derecha = sol[k + 1][j];

                // aplicamos el producto cartesiano y probamos todas las multiplicaciones
                for (char c1 : izquierda) {
                    for (char c2 : derecha) {
                        char temp = tabla[indice(c1)][indice(c2)];
                        if (!contiene(sol[i][j], temp)) {
                            sol[i][j].push_back(temp);
                        }
                    }
                }
            }
        }
    }
    
    return contiene(sol[0][N-1], 'a');
}

bool resuelveCaso() {
   // leer los datos de la entrada
    string cadena; cin >> cadena;
    if (!cin) return false;

    vector<vector<char>> mult;

    mult.push_back({ 'b', 'b', 'a' });
    mult.push_back({ 'c', 'b', 'a' });
    mult.push_back({ 'a', 'c', 'c' });

   // resolver el caso posiblemente llamando a otras funciones 
  
    bool posible = producto(cadena, mult);
    if (posible) {
        cout << "SI\n";
    }
    else {
        cout << "NO\n";
    }

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("R_13.in");
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
