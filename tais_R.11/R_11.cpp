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

struct Bateria {
    int id; 
    long long duracion;
    long long duracion_inicial;
    long long tiempo_fin;

};

const bool operator <(const Bateria& a, const Bateria& b) {
    return (a.tiempo_fin > b.tiempo_fin) || (a.tiempo_fin == b.tiempo_fin && a.id < b.id);
}


bool resuelveCaso() {
   // leer los datos de la entrada
    int B; cin >> B;
    if (!cin) return false;

    vector<Bateria> baterias(B);
    for (int i = 0; i < B; i++) {
        baterias[i].id = i + 1;
        cin >> baterias[i].duracion;
        baterias[i].duracion_inicial = baterias[i].duracion;
        baterias[i].tiempo_fin = baterias[i].duracion;
    }

    int R; cin >> R;

    queue<Bateria> reserva;
    for (int i = 0; i < R; i++) {
        int id = B + 1;
        long long duracion = 0;
        cin >> duracion;
        reserva.push({ id, duracion,duracion,duracion });
    }

    int Z, T; cin >> Z >> T;
   // resolver el caso posiblemente llamando a otras funciones 

    priority_queue<Bateria> activas;
    for (int i = 0; i < B; i++) {
        activas.push(baterias[i]);
    }

    long long t_Actual = 0;

    while (t_Actual < T && !activas.empty()) {
        Bateria bat = activas.top();
        activas.pop();

        t_Actual = bat.tiempo_fin;

        if (t_Actual >= T) {
            bat.tiempo_fin = T;
            activas.push(bat);
        }

        if (bat.duracion > Z) {
            // Recargar
            bat.duracion -= Z;
            bat.tiempo_fin = t_Actual + bat.duracion;
            activas.push(bat);
        }
        else {
            // No se puede recargar, usar repuesto si hay
            if (!reserva.empty()) {
                Bateria nueva = reserva.front();
                reserva.pop();
                nueva.tiempo_fin = t_Actual + nueva.duracion;
                activas.push(nueva);
            }
        }
    }

    vector<Bateria> resultado;
    while (!activas.empty()) {
        Bateria bat = activas.top();
        activas.pop();

        // Ajustar tiempos para la salida
        if (bat.tiempo_fin > T) {
            bat.tiempo_fin = T;
        }
        resultado.push_back(bat);
    }

    // Ordenar por tiempo_fin (para mostrar en orden de recarga)
    sort(resultado.begin(), resultado.end(),
        [](const Bateria& a, const Bateria& b) {
            if (a.tiempo_fin != b.tiempo_fin)
                return a.tiempo_fin < b.tiempo_fin;
            return a.id < b.id;
        });

    // Mostrar estado
    if (resultado.empty()) {
        cout << "ABANDONEN INMEDIATAMENTE LA BASE\n";
    }
    else if (resultado.size() < B) {
        cout << "FALLO EN EL SISTEMA\n";
    }
    else {
        cout << "CORRECTO\n";
    }

    // Mostrar baterías activas
    for (const auto& bat : resultado) {
        cout << bat.id << " " << bat.tiempo_fin << "\n";
    }

    cout << "---\n";
    return true;

}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("R_11.in");
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
