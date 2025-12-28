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
using namespace std;

/*@ <answer>

Para resolver el problema necesitamos usar programacion dinamica para emplear la funcion recursiva eficientemente

maneras(i,j) = numero de formas posibles de obtener la suma j con un dado de i caras

    Casos recursivos:
        maneras(i,j) = maneras(i - 1, j)                                si Vi > j
        maneras(i,j) = maneras(i - 1, j) + maneras(i - 1, j - Vi)        si Vi <= j

    Caso base:
        maneras(0,j) = 0 -> es decir no tenemos ningun dado que tirar
        maneras(i,0) = 1 -> es decir solo hay una manera de obtener 0

    llamada inicial: maneras(k,s) siendo K el numero de caras del dado y S el valor la suma que queremos obtener

    siendo:
        - Vi: el valor de la cara i del dado

Coste: Necesitamos iterar sobre los K caras del dado para ver todas las posibles combinaciones sobre la suma S dada -> O(K * S) siendo K el numero de caras del dado y 
S el valor la suma que queremos obtener

Coste en espacio adicional: podemos ahorrar en espacio quedandonos solo con la ultima fila de la matriz K*S, ya que solo necesitamos saber el valor de la fila anterior
que podemos obtener usando solo un vector -> O(S) siendo S el valor de la suma que queremos obtener
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int numManeras(int caras, int suma) {

    vector<int> maneras(suma + 1, 0);
    maneras[0] = 1; //caso base

    for (int i = 1; i <= caras; i++) {
        for (int j = i; j <= suma; j++) {
            if (i <= j) {
                maneras[j] = maneras[j] + maneras[j - i];
            }
        }
    }

    return maneras[suma];
}

void resuelveCaso() {
   // leer los datos de la entrada
    int K, S; cin >> K >> S;

   // resolver el caso posiblemente llamando a otras funciones 
    int sol = numManeras(K, S);

   // escribir la solución
   cout  << sol << "\n";
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("R_5.in");
   if (!in.is_open())
      cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
   auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

   int numCasos;
   cin >> numCasos;
   for (int i = 0; i < numCasos; ++i)
       resuelveCaso();

   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   cin.rdbuf(cinbuf);
#endif
   return 0;
}
