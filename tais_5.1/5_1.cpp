
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

Para resolver el problema necesitamos realizar un grafo implicito que vamos rellenando en funcion de los botones que pulsemos. La funcion adyacente nos ayudara a 
devolver el valor de la cuenta realizada al aplicar el boton correspondiente al valor de entrada. Creamos un vector de un tamaño limitado por el numero de botones 
y las posibles valores que obtenemos al realizar las operaciones. Iteramos hasta encontrar el valor solicitado

 COSTE: O(10^D) siendo D el numero distinto de digitos al resolver el problema

 COSTE EN ESPACIO ADICIONAL: tenemos un max de 10000 vertices (valore de la calculadora) y 3 adyacentes por cada uno en el caso peor, el coste seria 
 O(10000+3*10000)

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

const int MAX = 10000;
const int INF = 1000000000;
const int NUM_OPERACIONES = 3;

int adyavente(int v, int i) {
    switch (i) {
    case 0: return (v + 1) % MAX; //boton +1
    case 1: return (v * 2) % MAX; //boton *2
    case 2: return (v / 3) % MAX; //boton /3
    }
}

int bfs(int origen, int destino) {
    if (origen == destino) return 0;

    vector<int> distancia(MAX, INF);
    distancia[origen] = 0;
    queue<int> cola; cola.push(origen);
    while (!cola.empty()) {
        int v = cola.front(); cola.pop();
        for (int i = 0; i < NUM_OPERACIONES; ++i) {
            int w = adyavente(v, i);
            if (distancia[w] == INF) {
                distancia[w] = distancia[v] + 1;
                if (w == destino) {
                    return distancia[w];
                }
                else {
                    cola.push(w);
                }
            }
        }
    }
}

bool resuelveCaso() {
    int origen = 0, destino = 0;
    cin >> origen >> destino;
    if (!cin) return false;

    cout << bfs(origen, destino) << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("5_1.in");
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