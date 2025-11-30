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
#include <numeric>
#include <algorithm>

using namespace std;

/*@ <answer>
Para resolver el problema necesitamos pensar en un estrategia voraz que nos permita resolver el problema. Para ello usaremos un vector para guardar la hora y 
duracion de las peliculas, que suaremos para resolver el ejercicio. Ordenaremos las peliculas de menor a mayor en funcion de cuando terminan, asi podremos 
comparar si lo  que dura la pelicula actual, mas el tiempo de descanso; no se solapa con la siguiente pelicula. Mostraremos el numero de peliculas que no 
se solapen.

COSTE: Iteramos N veces sobre el vector para ssaber que peliculas podemos ver, y el coste de ordenar un vector de menor a mayor es O(NlogN) siendo N el tamaño
del vector -> O(N log N + N) siendo N el numero de peliculas disponibles

COSTE EN ESPACIO ADICIONAL: O(N) siendo N el numero de peliculas disponibles

@ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

const int TIEMPO_LIBRE = 10;

struct Pelicula {
    int inicio;
    int fin;
};

const bool operator <(Pelicula const & a, Pelicula const& b) {
    return a.fin < b.fin;
}

bool resuelveCaso() {
    int N = 0; cin >> N ;
    if (N == 0) return false;

    vector<Pelicula> cartelera(N);
    int dia = 0, hora = 0, minuto = 0, duracion = 0;
    char aux = ' ';

    for (int i = 0; i < N; i++) {
        cin >> dia >> hora >> aux >> minuto >> duracion;
        int inicio = dia * 24 * 60 + hora * 60 + minuto;
        int fin = inicio + duracion;

        cartelera[i] = { inicio,fin };
    }

    //ordenamos las peliculas en funcion de cuanto terminan

    sort(cartelera.begin(), cartelera.end());

    int num_vistas = 0;
    int ultimo_fin = 0;

    for (int i = 0; i < N; i++) {
        if (cartelera[i].inicio >= ultimo_fin) {
            num_vistas++;
            ultimo_fin = cartelera[i].fin + TIEMPO_LIBRE;
        }
       
    }

    cout << num_vistas << "\n";

    return true;
}


//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("8_4.in");
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