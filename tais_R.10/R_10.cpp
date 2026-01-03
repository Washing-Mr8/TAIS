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


/*@ <answer>

Para resolver el eljercicio necesitamos utilizar una cola de prioridad en el que almacenaremos en orden creciente el numero de espectadores por partido. Una vez ordenados
sumamos los aficionados que estaran en ese partido, e independientemente de quien gane, añadimos toda esa gente de vuelta a la cola (sumada obviamente) para sumarala en 
posteriores partidos. Para que se repartan gorras el numero de equipos tiene que ser mayor que 1

Coste: Utilizamos operaciones como push y pop que tienen coste O(log N) y otras como top con coste constante O(1) -> Total : O(log N) siendo N el numero de partidos

Coste en espacio adicional: sin contar la entrada, el coste total usaria una cola de prioridad y una variable para la solucion: -> O(N) siendo N el numero de partidos

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


bool resuelveCaso() {
   // leer los datos de la entrada
    int N; cin >> N;
    if (N == 0) return false;

    priority_queue<long long int,vector<long long int>,greater<long long int>> partidos;

    int valor = 0;
    for (int i = 0; i < N; i++) {
        cin >> valor;
        partidos.push(valor);
    }
   // resolver el caso posiblemente llamando a otras funciones 
    long long int sol = 0;
    while (partidos.size() > 1) {
        long long int p1 = partidos.top();
        partidos.pop();
        long long int p2 = partidos.top();
        partidos.pop();

        partidos.push(p1 + p2);
        sol += p1 + p2;
    }

   // escribir la solución
    cout << sol << "\n";
    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("R_10.in");
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
