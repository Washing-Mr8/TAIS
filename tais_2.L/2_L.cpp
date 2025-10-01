/*@ <authors>
 *
 * E42 Washington Morocho Lema
 * E63 Sergio Vazquez Carbajo

 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;


/*@ <answer>

Para resolver el problema necesitamos crear una estructura instrumento que almacena el numero de musicos y el numeor de partituras que comparten. Como cada instrumento
tiene que tener como minimo 1 partitura neceseitamos recorrer la cola de prioridad P - N veces siendo 0 el minimo. mientras lo recorremos, nos quedamos con el elemento
mayor, es decir, con mas personas, y le añadimos una partitura y lo volvemos a añadir a la cola. Al final nos quedamos con el elemento mas prioritario y lo dividimos
por su numero de partituras (sumandole el resto si no es exacto)

Coste: logN al añadir e la cola, y recorremos P - N veces la cola -> O(P - N log N)

coste en espacio adicional: N siendo N el numero de instrumentos

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

struct Instrumento {
    int musicos;
    int partituras;
};

bool operator <(const Instrumento& a, const Instrumento& b) {
    int musicosA = a.musicos / a.partituras;
    if (a.musicos % a.partituras != 0) {
        musicosA++;
    }
    int musicosB = b.musicos / b.partituras;
    if (b.musicos % b.partituras != 0) {
        musicosB++;
    }
    return musicosA < musicosB;
}

bool resuelveCaso() {

    // leemos la entrada
    int P, N;
    cin >> P >> N;

    if (!cin)
        return false;

    // leer el resto del caso y resolverlo
    priority_queue<Instrumento> orquesta;
    int instrumento, part_repartidas = 0;


    for (int i = 0; i < N; i++) {
        cin >> instrumento;
        orquesta.push({instrumento, 1});
        part_repartidas++;
    }

    while (part_repartidas < P) {
        auto inst = orquesta.top();
        orquesta.pop();

        inst.partituras++;

        orquesta.push(inst);
        part_repartidas++;
    }

    auto atril = orquesta.top();

    int musicos = atril.musicos/ atril.partituras;

    if (atril.musicos % atril.partituras != 0) {
        musicos++;
    }

    cout << musicos << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open())
        cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
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
