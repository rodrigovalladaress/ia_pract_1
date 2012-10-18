#include "ia_p1.cc"
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int main(void)
{
  int opcion = -1, nodo_inicial = -1, nodo_final = -1;
  char adyacencia[] = "MatrizAdyacencia.txt";
  char costos[] = "MatrizCostos.txt";
  char heuristica[] = "MatrizEvaluacionHeuristica.txt";
  char opcion_cola = '0';
  cout << "#################################################################" << endl;
  cout << "#           Búsqueda en amplitud, en profundidad y A*           #" << endl;
  cout << "#################################################################" << endl;
  cout << endl;
  cout << "-----------------------------------------------------------------" << endl;
  cout << " 1) Ficheros y nodos por defecto                               " << endl;
  cout << " 2) Ficheros por defecto, introducir nodos                     " << endl;
  cout << " 3) Introducir nodos y nombre de ficheros                      " << endl;
  cout << " 0) Salir                                                      " << endl;
  cout << "-----------------------------------------------------------------" << endl;
  while((opcion < 0)||(opcion > 3)) {
    cout << endl;
    cout << "Opción: ";
    cin >> opcion;
  }
  if(opcion != 0) {
    if(opcion == 3) {
      cout << "Fichero de la matriz de adyacencia = ";
      cin >> adyacencia;
      cout << "Fichero de la matriz de costos = ";
      cin >> costos;
      cout << "Fichero de la matriz de costos heurísticos =";
      cin >> heuristica;
    }
    GRAFO grafo(adyacencia, costos, heuristica);
    if(opcion == 1) {
      nodo_inicial = 0;
      //nodo_final = grafo.get_num_nodos() - 1;
      nodo_final = 13;
    }
    else {
      while((nodo_inicial < 0)||(nodo_inicial > grafo.get_num_nodos() - 1)) {
	cout << "Nodo inicial = ";
	cin >> nodo_inicial;
	nodo_inicial -= 1;
      }
      while((nodo_final < 0)||(nodo_final > grafo.get_num_nodos() - 1)) {
	cout << "Nodo final = ";
	cin >> nodo_final;
	nodo_final -= 1;
      }
    }
    cout << endl;
    if(grafo.exito()) {
      while((opcion_cola != 'S')&&(opcion_cola != 'n')&&(opcion_cola != 's')&&(opcion_cola != 'N')) {
	cout << "¿Imprimir cola? [S/n] ";
	cin >> opcion_cola;
      }
      system("clear");
      grafo.imprimir();
      cout << endl;
      ARBOL arbol(nodo_inicial, nodo_final, &grafo);
      arbol.set_imprimir_cola(((opcion_cola == 'S')||(opcion_cola == 's')) ? true : false);
      system("clear");      
      cout << "Nodo inicial = " << nodo_inicial + 1 << endl;
      cout << "------------" << endl;
      cout << "Nodo final =   " << nodo_final + 1 << endl;
      cout << "----------" << endl;
      cout << endl;
      cout << "#################################################################" << endl;
      cout << "#                      Búsqueda en amplitud                     #" << endl;
      cout << "#################################################################" << endl;
      arbol.BFS();
      cout << endl;
      cout << "#################################################################" << endl;
      cout << "#                     Búsqueda en profundidad                   #" << endl;
      cout << "#################################################################" << endl;
      arbol.DFS();
      cout << endl;
      cout << "#################################################################" << endl;
      cout << "#                          Búsqueda A*                          #" << endl;
      cout << "#################################################################" << endl;
      arbol.Busqueda_Heuristica();
    }
    else
      cout << "No se ha encontrado el fichero. Se cerrará el programa." << endl;
  }
}