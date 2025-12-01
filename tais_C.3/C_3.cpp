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

minMonedas(i) = nº minimo de monedas que necesitamos para pagar una cantidad j teniendo de 1 a i monedas con una cantidad c_i por monedas

    Casos recursivos:
        -> minMonedas(i,j) = min_{ 0 <= k <= c_i* k <= j }(minMonedas(i - 1, j - k * c_i) + k )
        es decir comprobamos las posiciones de 0 a k y a j para ver cuantas monedas podemos usar
        
    Casos base:
       - minMonedas(0, j) = imposible -> INFINITO por ser imposible de pagar
       - minMonedas(i, 0) = 0 -> No tenemos nada que pagar

    Llamada inicial: minMonedas(N,P)

    Siendo : c_i la cantidad de monedas i y k un numero dentro del intervalo 0 <= k <= j


 COSTE: Necesitamos iterar sobre las N monedas que tenemos y recorrer todos los posibles precios P, y aunque hagamos comprobaciones entre iteraciones 
 con k, esto no afecta al rendimiento porque es constante : O(N * P)
 
 COSTE EN ESPACIO ADICIONAL:  Como no necesitamos reconstruir la solucion nos podemos quedar con la ultima fila simulada por un vector de tamaño P
 O(P), siendo P el precio.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

struct Moneda {
    int valor;
    int cantidad;
};

EntInf minMonedas(const vector<Moneda>& monedas, int P) {

    int N = monedas.size();

    vector<EntInf> sol(P + 1, Infinito);
    sol[0] = 0;

    for (int i = 1; i <= N; ++i) {
        for (int j = P; j > 0; --j) {
            int k = 0;
            while (k <= monedas[i - 1].cantidad && k * monedas[i - 1].valor <= j) {
                EntInf temp = sol[j - k * monedas[i - 1].valor] + k;
                if (temp < sol[j]) {
                    sol[j] = temp;
                }
                ++k;
            }
        }
    }

    //for (int i = 0; i <= P; i++) {
    //    cout  << "j = " << i << ": " << sol[i] << "\n";
    //}
    return sol[P];
}

bool resuelveCaso() {
    // leemos la entrada
    int N; cin >> N;
    if (!std::cin) return false;

    // leer el resto del caso y resolverlo

    vector<Moneda> monedas(N);
    int P = 0;

    for (int i = 0; i < N; i++) {
        cin >> monedas[i].valor;
    }

    for (int i = 0; i < N; i++) {
        cin >> monedas[i].cantidad;
    }
    
    cin >> P;

    EntInf sol = minMonedas(monedas, P);

    if (sol != Infinito) {
        cout << "SI " << sol;
    }
    else {
        cout << "NO" ;
    }

    cout << "\n";

  return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
  // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
  ifstream in("C_3.in");
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
