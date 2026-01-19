/*@ <authors>
 *
 * Washington Morocho Lema E42
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <climits>
#include <numeric>
#include <unordered_map>
#include <iomanip>
#include <vector>

using namespace std;

#include "IndexPQ.h"

/*@ <answer>
 
 Sustituye este párrafo por un comentario general sobre la solución,
 incluyendo su coste.

 Para resolver el problema necesitamos usar 2 colas de prioridad indexadas, una en la que almacenaremos el stock de frutas que tenemos, y otra con el historial de las frutas mas vendidas.
 Ambas colas tendran una prioridad creciente para saber en cada momento cual es la furta con mayor cantidad en ambas consultas. En caso de empate elegiremos a la furta con el menor nombre
 lexicografico. Vamos leyendo las consultas: si es una compra (C), restamos las frutas compradas al stock, y si compran mas de las que hay se queda en 0. A su vez añadimos estos valores 
 vendidos al historial de ventas. Si el caso es una P, sumamos la cantidad de fruta de los proveedores al stock. Y si la consulta es Q, mostramos la fruta mas prioritaria en ambas colas,
 siempre que su cantidad no sea 0

 Pd: usamos un unordeered_map para tener los indices de los nombres de las frutas

 Coste: Sin contar la entrada y la salida, iteramos sobre E consultas, sobre 2 colas de prioridad indexada  de tamaño N. cada top, es constante O(1) , pero cada update es O(logN)
 El coste total ascenderia a O(E log N)

 Coste en espacio adicional: las 2 colas de prioridad indexadas de tamaño N, siendo N la fruta -> O(N)

 
 @ </answer> */


// ===========================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>


struct Fruta {
    string nombre;
    int cantidad;
};


const bool operator <(const Fruta& a, const Fruta& b) {
    return (a.cantidad > b.cantidad || (a.cantidad == b.cantidad) && (a.nombre < b.nombre));
}

bool resuelveCaso() {
  
  // leemos la entrada
  int N; cin >> N;
  if (N == 0)
    return false;

  IndexPQ<Fruta> almacen(N );
  IndexPQ<Fruta> ventas(N);

  unordered_map<string, int> indice_fruta;

  for (int i = 0; i < N; i++) {
      Fruta f;
      cin >> f.nombre >> f.cantidad;
      indice_fruta.insert({ f.nombre,i });
      almacen.push(i,f);
      ventas.push(i, { f.nombre,0 });
  }

  // leer el resto del caso y resolverlo
  int E = 0; cin >> E;

  for (int i = 0; i < E; i++) {
      string accion = "";
      Fruta fruta = { "", 0 };

      cin >> accion;

      if (accion == "C") {
          cin >> fruta.nombre >> fruta.cantidad;

          Fruta stock = almacen.priority(indice_fruta[fruta.nombre]);//buscamos la fruta a consultar en el almacen
          Fruta vendida = ventas.priority(indice_fruta[fruta.nombre]);//buscamos las ventas de la fruta a consultar
          
          if (fruta.cantidad > stock.cantidad) { // si compran mas cantidad que el stock
              vendida.cantidad += stock.cantidad;
              stock.cantidad = 0;
          }
          else { // si nos queda stock
              vendida.cantidad = vendida.cantidad +  fruta.cantidad;
              stock.cantidad = stock.cantidad - fruta.cantidad;

          }
          almacen.update(indice_fruta[fruta.nombre], stock);
          ventas.update(indice_fruta[fruta.nombre], vendida);

      }
      else if (accion == "P") { // si llega el proveedor, aumantamos el stock de la fruta seleccionada
          cin >> fruta.nombre >> fruta.cantidad;

          Fruta stock = almacen.priority(indice_fruta[fruta.nombre]);//buscamos la fruta a consultar en el almacen

          stock.cantidad += fruta.cantidad;
          almacen.update(indice_fruta[fruta.nombre], stock);
      }
      else { // si es la consulta Q
          Fruta stock = almacen.top().prioridad;//Miramos cual es la fruta mas abundante
          Fruta vendida = ventas.top().prioridad;//Miramos cual es la fruta mas vendida
          
          if (stock.cantidad > 0) {
              cout << stock.nombre << " " << stock.cantidad; 
          }
          else {
              cout << "NO HAY";

          }

          cout << "; ";

          if (vendida.cantidad > 0) {
              cout << vendida.nombre << " " << vendida.cantidad;
          }
          else {
              cout << "NO HAY";
          }
          cout << "\n";

      }

  }

  cout << "---\n";
  
  return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.
// ===========================================================================

int main() {
  // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
  ifstream in("casos1.in");
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
