/*@ <authors>
 *
 * E42 Washington Morocho Lema
 * E16 Ruben Dolera Mancebo
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <climits>
#include <numeric>
#include <algorithm>

using namespace std;

/*@ <answer>

Para resolver el problema necesitamos pensar en un estrategia voraz que nos permita resolver el problema. Para ellos usaremos una estructura conferencia que 
almacenara su horario (inicio y fin) y su id, tambien usaremos una estructura sala que guardara la hora de finalizacion de la conferencia que tiene asignada y
su numero de sala. Las conferencias estan ordenadas cronologicamente por hora de inicio y las salas se añaden a una cola de prioridad ordenada en funcion de 
la hora a la que acaba esa conferencia en orden decreciente, y en caso de empate se devuelve la sala que tenga menor id. Recorremos todas las conferencias para
ver si tenemos que usar una sala nueva o una que ya esta disponible.

COSTE: Iteramos N veces sobre el vector de conferencias para saber que salas podemos usar, y el coste de ordenar un vector de menor a mayor es O(NlogN) 
siendo N el tamaño del vector. Cada push y pop es O(logM) siendo M el tamaño de la cola  -> O(N log N + N (log R)) siendo N el numero de Conferencias disponibles
y R el numero de salas disponibles

COSTE EN ESPACIO ADICIONAL: O(N +  R) siendo N el numero de Conferencias disponibles y R el numero de salas disponibles

@ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


struct Conferencia {
    long long int inicio;
    long long int fin; 
    int id;
};

struct Sala {
    int id;
    long long int ultimo_fin;
};

const bool operator <(Conferencia const& a, Conferencia const& b) {
    return a.inicio < b.inicio;
}

const bool operator <(Sala const& a, Sala const& b) {
    return ((a.ultimo_fin > b.ultimo_fin) || (a.ultimo_fin ==  b.ultimo_fin && a.id < b.id));
}

bool resuelveCaso() {
    int N = 0; cin >> N;
    if (N == 0) return false;

    vector<Conferencia> conferencias(N);
    long long int inicio = 0, fin = 0, duracion = 0;

    for (int i = 0; i < N; i++) {
        cin >> inicio >> fin;

        conferencias[i] = { inicio,fin, i };
    }

    //ordenamos las conferencias en funcion de cuanto terminan

    sort(conferencias.begin(), conferencias.end());

    priority_queue<Sala> salas_ocupadas;

    int num_salas = 0;
    int siguiente_sala = 1;

    vector<int> salas(N);

    for (int i = 0; i < N; i++) {

        Conferencia actual = conferencias[i];

        if (!salas_ocupadas.empty() && salas_ocupadas.top().ultimo_fin <= actual.inicio) {
            Sala sala_reusada = salas_ocupadas.top();
            salas_ocupadas.pop();

            sala_reusada.ultimo_fin = actual.fin;
            salas_ocupadas.push(sala_reusada);
            salas[actual.id] = sala_reusada.id;
        }
        else {
            Sala nueva_sala = {siguiente_sala, actual.fin};

            salas_ocupadas.push(nueva_sala);
            salas[actual.id] = siguiente_sala;

            siguiente_sala++;
            num_salas++;
        }

    }

    cout << num_salas << "\n";

    for (int i = 0; i < N; i++) {
        cout <<salas[i] << " ";
    }
    cout << "\n";

    return true;

}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("8_L.in");
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