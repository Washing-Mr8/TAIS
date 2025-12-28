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

maxGanancia(i,j) = maxima ganancia obtenida al hornear bollos con chorizos de 1 a i tipos con una maxima masa j

    Casos recursivos:
        maxGanancia(i,j) = maxGanancia(i - 1, j)                                                    si k * Mi > j
        maxGanancia(i,j) = max(maxGanancia(i - 1, j), maxGanancia(i - 1, j - Mi) + k * Pi )         si k * Mi < j

    Caso base:
        maxGanancia(0,j) = 0 -> es decir no tenemos ningun chorizo para hacer el bollo
        maxGanancia(i,0) = 0 -> es decir no nos queda masa para hacer el bollo
        

    llamada inicial: maxGanancia(N,M) siendo N el numero de chorizos y M la cantidad de masa

    siendo:
        - Mi: la cantidad de masa que necesita el chorizo i
        - Pi: El precio que genera el bollo hecho con chorizo i
        - k: la cantidad de chorizo -> 1 <= k <= i

Coste: Necesitamos iterar sobre los N tipos de chorizo para ver todas las posibles combinaciones sobre los M gramos de masa que tenemos, y aunque hagamos iteraciones con
k esto no afecta al rendimiento -> O(N * M) siendo N los tipos de chorizos y M la cantidad de masa que tenemos

Coste en espacio adicional: podemos ahorrar en espacio quedandonos solo con la ultima fila de la matriz N*M, ya que solo necesitamos saber el valor de la fila anterior
que podemos obtener usando solo un vector -> O(M) siendo M la cantidad de masa que tenemos
 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


struct Chorizo {
    int disponible;
    int necesario;
    int masa;
    int precio;
};

int ganancias(const vector<Chorizo>& embutidos,int N, int M) {

    vector<int> maxGanancia(M + 1, 0);

    for (int i = 0; i < N; i++) {
        for (int j = M; j > 0; j--) {
            int k = 0;

            while (k * embutidos[i].necesario <= embutidos[i].disponible && k * embutidos[i].masa <= j) {
                int temp = maxGanancia[j - k * embutidos[i].masa ] + k * embutidos[i].precio;

                if (temp > maxGanancia[j]) {
                    maxGanancia[j] = temp;
                }
                k++;
            }
        }
    }

    return maxGanancia[M];
}

bool resuelveCaso() {
   // leer los datos de la entrada
    int N, M; cin >> N >> M;

   if (!std::cin) return false; // fin de la entrada

   vector<Chorizo> chorizos(N);

   for (int i = 0; i < N; i++) {
       cin >> chorizos[i].disponible >> chorizos[i].necesario >> chorizos[i].masa >> chorizos[i].precio;
   }

   // resolver el caso posiblemente llamando a otras funciones
   int sol = ganancias(chorizos, N, M);

   // escribir la solución
   cout << sol << "\n";
  
   return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("R_3.in");
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
