#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <stdio.h>
#define INF 4500
using namespace std;
class GRAFO;
class NODO_ARBOL;
/* Guardar los nodos en un array (NODO* = new). Cada nodo tiene asociado dos arrays de NODO* donde
 * uno indica su padre y otro su hijo.*/
class COLA
{
private:
  vector<NODO_ARBOL*> cola;
  vector<int> coste_heuristico;
  GRAFO* grafo;
  int nodo_final;
public:
  inline void push(NODO_ARBOL*); //introduce nodos al final de la cola
  inline void push_front(NODO_ARBOL*); //introduce nodos al principio de la cola
  inline void push_heuristica(NODO_ARBOL*, int); //introduce nodos y su coste heurístico
  inline NODO_ARBOL* pop(void); //saca nodos del principio de la cola
  inline NODO_ARBOL* pop_back(void); //saca nodos del final de la cola
  inline NODO_ARBOL* pop_heuristica(void); //saca el nodo con menor coste heurístico
  inline NODO_ARBOL* operator[](int);
  inline bool vacia(void);
  inline void imprimir(void);
  COLA(GRAFO*, int);
  COLA(void);
  ~COLA(void);
};
class NODO_ARBOL
{
private:
  int numero_nodo; //numero dentro del nodo
  NODO_ARBOL* padre;
  vector<NODO_ARBOL*> hijo; //array de hijos
public:
  inline void add_hijo(NODO_ARBOL*);
  inline void set_padre(NODO_ARBOL*);
  inline int get_id_nodo(void); //devuelve numero_nodo
  inline int get_num_hijos(void);
  inline NODO_ARBOL* get_padre(void);
  inline NODO_ARBOL* get_hijo(int);
  NODO_ARBOL(int); //constructor con el numero_nodo
  NODO_ARBOL(int, NODO_ARBOL*); //numero_nodo, padre
  ~NODO_ARBOL(void);
};
class ARBOL
{
private:
  bool imprimir_cola; //booleano que indica si se imprime la cola en cada iteración
  NODO_ARBOL* raiz;
  int nodo_final;
  GRAFO* grafo; //puntero a grafo para acceder a sus métodos
  void eliminar_arbol(NODO_ARBOL*); //elimina completamente el árbol
  void limpiar_arbol(void); //elimina los nodos del arbol y vuelve a introducir la raíz
  bool esta_en_el_camino(int, NODO_ARBOL*); //comprueba si un nodo está en el camino al nodo inicial
  void mostrar_camino(NODO_ARBOL*, int&);
  int get_coste_camino(NODO_ARBOL*); 
public:
  void Busqueda_Heuristica(int i = -1, int f = -1);
  void BFS(int i = -1, int f = -1);
  void DFS(int i = -1, int f = -1);
  inline NODO_ARBOL* get_raiz(void);
  inline void set_nodo_inicial(int);
  inline void set_nodo_final(int);
  inline void set_grafo(GRAFO*);
  inline void set_imprimir_cola(bool); //indica si se imprime la cola en cada iteración o no
  ARBOL(int, int, GRAFO*); //se añade el nodo raíz y el final, puntero grafo
  ARBOL(GRAFO*);
  ARBOL(void);
  ~ARBOL(void);
};
class NODO
{
private:
  int num_hijos;
  int hijos_agregados; //posición para añadir más hjos
  int* hijo;
public:
  inline void mostrar_hijos(bool);
  inline void set_num_hijos(int);
  inline void set_hijo(int); //hijo, coste
  inline int get_num_hijos(void);
  inline int get_hijo(int);
  NODO(int, int*, int*); //num_hijos, hijos*, coste*
  NODO(void);
  ~NODO(void);
};
class GRAFO
{
private:
  int num_nodos;
  NODO* nodo; //Array de nodos.
  bool encontrado_archivo; //Si es false indica que no se ha encontrado el archivo
  int** matriz_heuristica;
  int** matriz_costos;
public:
  void imprimir(bool sumar_uno = true);
  inline bool exito(void); //Devuelve encontrado_archivo
  inline NODO* get_nodo(int);
  inline int get_coste(int, int);
  inline int get_coste_heuristica(int, int);
  inline int get_num_nodos(void);
  GRAFO(void);
  GRAFO(char[], char[], char[]);
  ~GRAFO(void);
};