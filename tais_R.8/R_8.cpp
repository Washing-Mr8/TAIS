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

Para resolver el eljercicio necesitamos pensar en un estrategia voraz que nos permita encontrar las posibles solucionesal problema. Ordenamos las actividades
en orden cronologico en funcion de cuando comienzan y usamos una cola de prioridad  de las actividades que asisten nuestros acompañantes ordenada de forma 
decreciente en funcion de cuando acaba la actividad. Recorremos todas las actividades y añadimos acompañantes si el final de la actividad asisitida mas prioritaria 
no solapa con el comienzo de la actividad actual a la que queremos ir.

Coste: Ordenar el vector y realizar pop y back en la cola de prioridad tienen un coste de O(log N) siendo N el tamaño del vector. Como iteramos sobre todas las
actividades para ver si podemos asistir el coste seria -> O(A log A) siendo A el numero de actividades

Coste en espacio adicional: sin contar la entrada, el coste total usaria el vector de datos, la cola de prioridad y una variable para la solucion:
-> O(A) siendo A el numero de actividades


 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

struct Actividad {
    int inicio;
    int final;
};

const bool operator<(const Actividad& a, const Actividad& b) {
    return a.inicio < b.inicio;
}

class Orden {
public:
    bool operator ()(const Actividad& a, const Actividad& b) {
        return a.final > b.final;
    }
};


int organizar(vector<Actividad>& planificacion) {
    int sol = 0;

    //ordenamos las actividades en orden ascendente en funcion de su hora de inicio
    sort(planificacion.begin(), planificacion.end());
    
    priority_queue<Actividad, vector<Actividad>, Orden> asistido;
    
    for (int i = 0; i < planificacion.size(); i++) {

        if (!asistido.empty() && planificacion[i].inicio >= asistido.top().final) {
            asistido.pop();
            asistido.push(planificacion[i]);
        }
        else {
            asistido.push(planificacion[i]);
            ++sol;
        }

    }
    //devolvemos numero de acompañantes sin contarnos a nosotros
    return sol - 1;
}


bool resuelveCaso() {
   // leer los datos de la entrada
    int N; cin >> N;
    if (N == 0) return false;

    vector<Actividad> planificacion(N);

    for (int i = 0; i < N; i++) {
        cin >> planificacion[i].inicio >> planificacion[i].final;
    }

   // resolver el caso posiblemente llamando a otras funciones 
    int sol = organizar(planificacion);
   // escribir la solución
    cout << sol << "\n";
    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("R_8.in");
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
