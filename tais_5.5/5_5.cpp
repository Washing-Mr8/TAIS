
/*@ <authors>
 *
 * E42 Washington Morocho Lema
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <climits>
using namespace std;


/*@ <answer>

Para resolver el problema necesitamos realizar un grafo implicito que vamos rellenando en funcion de las operaciones que tengamos y el valor actual de la x. 
Creamos un vector de un tamaño modulo para averiguar las distancias de cada operacion realizada para llegar a ese resultado. Iteramos hasta llegar a la solucion esperada,
en caso de no llegar (ninguna operacion puede dar ese resultado) devolvemos menos -1

 COSTE: Debido a que tenemos que realizar N operaciones, en caso de que no lleguemos al valor esperado, ademas de que en el caso peor, toque realizar N operaciones una 
cantidad de M veces (M es el valor del modulo) ya que ningun valor supera a este, el coste sería O(M*N)

 COSTE EN ESPACIO ADICIONAL: tenemos N operaciones que pueden realizarse cada M (valor del modulo) veces, el tamaño depende del valor mayor -> O(max(M,N))

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


int bfs(int modulo,int origen, int destino, vector<pair<int,int>> operaciones) {
    if (origen == destino) return 0;

    vector<int> distancia(modulo, -1);
    distancia[origen] = 0;
    queue<int> cola; 
    cola.push(origen);
    while (!cola.empty()) {
        int actual = cola.front(); cola.pop();

        for (auto op : operaciones) {
            int siguiente = (op.first * actual + op.second) % modulo;
            if (distancia[siguiente] == -1) {
                distancia[siguiente] = distancia[actual] + 1;
                if (siguiente == destino) {
                    return distancia[siguiente];
                }
                else {
                    cola.push(siguiente);
                }
            }
        }
    }
    //en caso de que no se haya llegado al valor objetivo devolvemos -1
    return -1;
}

bool resuelveCaso() {
    int M = 0, S = 0, T = 0;
    cin >> M >> S >> T;
    if (!cin) return false;

    int N = 0, a = 0, b = 0;
    cin >> N;
    vector<pair<int,int>> operaciones;

    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        operaciones.push_back({a,b});
    }

    cout << bfs(M, S, T, operaciones) << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("5_5.in");
    if (!in.is_open())
        std::cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout << "Pulsa Intro para salir..." << std::flush;
    std::cin.get();
#endif
    return 0;
}