
/*@ <authors>
 *
 * Washington Morocho Lema E42
 *
 *@ </authors> */

#include <iostream>
#include <fstream>

using namespace std;

#include "bintree.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Para poder verficar si un arbol binario es AVL, necesitamos recorrer todos los nodos del arbol
 comprobando si los nodos hijos cumplen con la condicion de ser AVL o de si su valor es menor que la raiz,
 en caso de ser el hijo izquierdo; o mayor, en caso de ser el hijo derecho. Realizaremos un unico recorrido
 y en este tambien comprobaremos las alturas entre los nodos hijos. 

 Usamos la plantilla con typename T para que la funcion esArbolAvl sea generica y funcione tanto para int como string

 Coste: O(N) lineal con N siendo el numero de nodos que tenga el arbol binario
 
 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template<typename T>
struct tSolucion {
	int altura;
	bool esAvl;
	T min;
	T max;
};

template<typename T>
tSolucion<T> esArbolAvl(const BinTree<T> &arb) {
	// caso base en el que un nodo es vacio
	if (arb.empty()) {
		return { 0,true, T(),T() };
	}

	// recorremos los nodos hijos (tantos los de la izquierda como los de la derecha)
	auto solIzq = esArbolAvl(arb.left());
	auto solDer = esArbolAvl(arb.right());

	// si ninguno de los hijos es avl, entonces el arbol no cumple la condicion avl
	if (!solIzq.esAvl || !solDer.esAvl) {
		return { 0, false, T(), T() };
	}

	// verificamos que la altura no sea mayor que 1
	int difAltura = abs(solIzq.altura - solDer.altura);
	if (difAltura > 1) {
		return { 0, false, T(), T() };
	}

	T raiz = arb.root();
	// si alguno de los valores de los hijos izquierdos es mayor, o alguno de lso valores de los hijos derechos es menor no cumple la condicion
	if ((!arb.left().empty() && solIzq.max >= raiz) || (!arb.right().empty() && solDer.min <= raiz)) {
		return { 0, false, T(), T() };
	}

	// calculamos min y max del subarbol actual
	T minActual = arb.left().empty() ? raiz : min(raiz, solIzq.min);
	T maxActual = arb.right().empty() ? raiz : max(raiz, solDer.max);

	// altura actual
	int alturaActual = 1 + max(solIzq.altura, solDer.altura);

	return { alturaActual, true, minActual, maxActual };
}

bool resuelveCaso() {
	// leer los datos de la entrada
	char type;
	cin >> type;

	if (!std::cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	bool esAvl = false;

	if (type == 'N') {
		auto arb = read_tree<int>(cin);
		auto sol = esArbolAvl(arb);
		esAvl = sol.esAvl;
	}
	else if (type == 'P') {
		auto arb = read_tree<string>(cin);
		auto sol = esArbolAvl(arb);
		esAvl = sol.esAvl;
	}
	else {
		return 0;
	}

	// escribir la solución
	if (esAvl) {
		cout << "SI\n";
	}
	else {
		cout << "NO\n";
	}

	return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("1.in");
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
