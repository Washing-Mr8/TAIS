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

#include "Grafo.h"

/*@ <answer>

Para resolver el problema necesitamos utilizar un grafo simple para ver si es posible repartir los equipos de manera correcta. Tras leer la entrada, realizaremos
una busqueda en profundidad para recorrer todos los vertices y ver si podemos asignarles un equipo diferente a cada uno, cumpliendo las restricciones de las 
rivalidades. Usaremos un vector con el color del equipo de cada persona y una variable que nos permita saber si es posible formar los equipos o no

Coste: Sin contar la entrada, el coste seria el recorrido en profundidad -> O(V + A), siendo V el numero de personas, y A el numero de rivalidades entre ellas

Coste en espacio adicional: sin contar al entrada, el tamaño del vector O(V + A) 
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Equipos {
private:
    vector<int> color;
    bool posible;

    void dfs(Grafo const& G, int v, int c) {
        color[v] = c;
        for (int w : G.ady(v)) {
            if (color[w] == 0) {
                dfs(G, w,0 - c);
            }
            else if(color[v] == color[w]) {
                posible = false;
            }
        }
    }

public:

    Equipos(Grafo const& g) : posible(true), color(vector<int>(g.V(), 0)) {
        for (int i = 0; i < g.V(); i++) {
            if (color[i] == 0) { // si no esta pintado
                dfs(g,i, 1);
            }
        }
    }

    bool esPosible() {
        return posible;
    }

};

bool resuelveCaso() {
   // leer los datos de la entrada
    int V, A; cin >> V >> A;

   if (!std::cin) return false; // fin de la entrada

   Grafo g(V);

   int v1, v2;
   for (int i = 0; i < A; i++) {
       cin >> v1 >> v2;
       g.ponArista(v1 - 1, v2 - 1);
   }

   // resolver el caso posiblemente llamando a otras funciones
   Equipos paintball(g);

   // escribir la solución
   if (paintball.esPosible()) {
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
   ifstream in("R_2.in");
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
