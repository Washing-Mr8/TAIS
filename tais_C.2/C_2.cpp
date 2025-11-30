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

using namespace std;

/*@ <answer>

Para resolver el ejercicio necesitamos aplicar una estrategia de programacion dinamica para encontrar la solucion mas eficiente al problema.

maxPeliculas(i) = nº de peliculas que podemos ver si hay 1 a i peliculas

    Casos recursivos:
        -> maxPeliculas(i) = max( maxPeliculas(i + 1), d_i + maxPeliculas(j))              
        
    Casos base:
       - maxPeliculas(N + 1) = 0

    Llamada inicial: maxPeliculas(0)

    donde d_i es la duración de la película i y maxPelicula(j) la primera película disponible


 COSTE: para encontrar la solucion necesitamos ordenar la lista en funcion del comienzo de las peliculas y tiene coste O(N log N). 
 Como tambien necesitamos recorrer toda la lista O(N)y ademas en cada iteracion necesitamos realizar una busqueda bianria apra encontrar 
 la primera pelicula j que no se solapa O(log N) -> El coste total entraria dentro del orden O(N log N)
 
 COSTE EN ESPACIO ADICIONAL: Como no necesitamos reconstruir la solucion, podemos utilizar simplemente un vector: O(N) siendo N la cantidad de peliculas

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

const int DESCANSO = 10;

struct Pelicula {
    int comienzo;
    int fin;
    int duracion;
};

const bool operator <(const Pelicula& a, const Pelicula& b) {
    return a.comienzo < b.comienzo;
}

int maxPeliculas(const vector<Pelicula>& peliculas) {
    int N = peliculas.size();
    vector<int> sol(N + 1, 0);

    for (int i = N - 1; i >=0; --i) {
        /*
        int j = i;
        while (j > 0) { //buscamos la primera pelicula que empiece despues de la actual
            --j;
            if (peliculas[j].comienzo <= peliculas[i].fin + DESCANSO) {
                break;
            }
        }
        */

        int j = lower_bound(peliculas.begin() + i, peliculas.end(), Pelicula{ peliculas[i].fin + DESCANSO, 0, 0 }) - peliculas.begin();

        sol[i] = max(sol[i + 1], sol[j] + peliculas[i].duracion);
    }

    return sol[0];
}

bool resuelveCaso() {
    // leemos la entrada
    int N; cin >> N;
    if (N == 0) return false;

    // leer el resto del caso y resolverlo
    vector<Pelicula> peliculas(N);
    int dia, hora, minuto, duracion;
    char aux = ' ';

    for (int i = 0; i < N; ++i) {
        cin >> dia >> hora >> aux >> minuto >> duracion;
        int comienzo = 24 * 60 * dia + 60 * hora + minuto;
        int fin = comienzo + duracion;
        peliculas[i] = { comienzo, fin, duracion };
    }

    //ordenamos laa peliculas en funcion de cuando comienzan
    sort(peliculas.begin(), peliculas.end());

    int maxDuracion = maxPeliculas(peliculas);

    cout << maxDuracion << "\n";
  
  return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
  // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
  ifstream in("C_2.in");
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
