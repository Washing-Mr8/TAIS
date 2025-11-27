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

Necesitamos un vector auxiliar para saber a cuantos conciertos podemos asistir como maximo segun nuestro presupuesto: 

grupos(i,j) = nº de grupos a los que podremos ver teniendo un presupuesto j, con una cantidad de 1 a i conciertos con un precio p_i

    Casos recursivos:
        - grupos (i, j) = grupos (i - 1, j)                                             si  p_i > j
        - grupos (i, j) = max (grupos (i - 1, j), grupos(i - 1, j - p_i ) + g_i)        si  p_i <= j

    Casos base:
        - grupos(0,j) = 0 si j > 0  -> es decir no hay ningun concierto por lo tanto no podemos ver a ningun grupo 
        - grupos(i,0) = 0 si i > 0  -> es decir no tenemos presupuesto para ningun concierto y por lo tanto no podemos ver a ningun grupo 

    Llamada inicial: grupos (N, P)

    Siendo:
        - N: nº de conciertos
        - P: presupuesto para los conciertos
        - p_i: precio del concierto i
        - g_i: nº de grupos del concierto i
    
 COSTE: para resolver el ejercicio necesitamos utilizar un vector auxiliar para analiar las posibles soluciones al problema. Necesitamos ver las
 posibles combianaciones entre eel maximo nmero de grupos que podemos ver con nuestro presupuesto y para ello necesitamos recorrer todo el vector:
 O(N * P) siendo N el numero de conciertos y P el presupuesto para pagar.
 
 COSTE EN ESPACIO ADICIONAL: O(P) siendo P el presupuesto que tenemos

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>



struct concierto {
    int grupos;
    int precio;
};

int grupos_rec(const vector<concierto>& conciertos, int P) {
    int N = conciertos.size();

    vector<int> grupos(P + 1, 0);
    int coste = 0;

    for (int i = 1; i <= N; ++i) {
        for (int j = P; j >= 0 ; --j) {
            if (conciertos[i - 1].precio <= j) {
                grupos[j] = max(grupos[j], grupos[j - conciertos[i - 1].precio] + conciertos[i - 1].grupos);
                //cout << "SOLUCION: " << grupos[j] << " y " << j - conciertos[i].precio << "\n";
                //cout << "INDICES: " << i << " y " << j << "\n";
            }
        }
    }

    return grupos[P];
}

bool resuelveCaso() {
    // leemos la entrada
    int N, P; cin >> P >> N;

    if (!cin) return false;

    // leer el resto del caso y resolverlo
    vector<concierto> conciertos(N);

    for (int i = 0; i < N; i++) {
        cin >> conciertos[i].grupos >> conciertos[i].precio;
    }
    
    int grupos = grupos_rec(conciertos, P);

    cout << grupos << "\n";
  
  return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
  // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
  ifstream in("B_3.in");
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
