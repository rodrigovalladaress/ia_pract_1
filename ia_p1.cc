#include "ia_p1.h"
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         COLA  //
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////  public  //
///////////////////////////////////////////////////////////////////////////////////////////////////
void COLA::push(NODO_ARBOL* p)
{
  cola.push_back(p);
}
void COLA::push_front(NODO_ARBOL* p)
{
  cola.insert(cola.begin(), p);
}
void COLA::push_heuristica(NODO_ARBOL* p, int coste)
{
  cola.push_back(p);
  coste_heuristico.push_back(coste);
}
NODO_ARBOL* COLA::pop(void)
{
  NODO_ARBOL* p = cola.front();
  cola.erase(cola.begin());
  return p;
}
NODO_ARBOL* COLA::pop_back(void)
{
  NODO_ARBOL* p = cola.back();
  cola.erase(cola.end() - 1);
  return p;
}
NODO_ARBOL* COLA::pop_heuristica(void)
{
  int min_coste = INF, pos = -1;
  NODO_ARBOL* p;
  for(unsigned i = 0; i < cola.size(); i++) 
  {
    if(coste_heuristico[i] < min_coste) { //No es el nodo raíz
      min_coste = coste_heuristico[i];
      pos = i;
    }
  }
  p = cola[pos];
  cola.erase(cola.begin() + pos);
  coste_heuristico.erase(coste_heuristico.begin() + pos);
  return p;
}
NODO_ARBOL* COLA::operator[](int i)
{
  return cola[i];
}
bool COLA::vacia(void)
{
  return cola.empty();
}
void  COLA::imprimir(void)
{
  cout << "{";  
  for(unsigned int i = 0; i < cola.size(); i++) 
  { 
    cout << cola[i]->get_id_nodo() + 1;
    if(i != cola.size() - 1)
      cout << ", ";
  }
  cout << "}" << endl;
}
COLA::COLA(GRAFO* grf, int f)
{
  grafo = grf;
  nodo_final = f;
}
COLA::COLA(void) {}
COLA::~COLA(void)
{
  while(cola.size() != 0)
    cola.pop_back();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                   NODO_ARBOL  //
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////  public  //
///////////////////////////////////////////////////////////////////////////////////////////////////
void  NODO_ARBOL::add_hijo(NODO_ARBOL* h)
{
  hijo.push_back(h);
}
void  NODO_ARBOL::set_padre(NODO_ARBOL* p)
{
  padre = p;
}
int  NODO_ARBOL::get_id_nodo(void)
{
  return numero_nodo;
}
int  NODO_ARBOL::get_num_hijos(void)
{
  return hijo.size();
}
NODO_ARBOL*  NODO_ARBOL::get_padre(void)
{
  return padre;
}
NODO_ARBOL*  NODO_ARBOL::get_hijo(int i)
{
  return hijo[i];
}
NODO_ARBOL::NODO_ARBOL(int n)
{
  numero_nodo = n;
  padre = NULL;
}
NODO_ARBOL::NODO_ARBOL(int n, NODO_ARBOL* p)
{
  numero_nodo = n;
  padre = p;
}
NODO_ARBOL::~NODO_ARBOL(void)
{
  hijo.clear();
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                        ARBOL  //
///////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////  private  //
///////////////////////////////////////////////////////////////////////////////////////////////////
void ARBOL::eliminar_arbol(NODO_ARBOL* p)
{
  int i = 0;
  while(i < p->get_num_hijos()) {
    eliminar_arbol(p->get_hijo(i));
    i++;
  }
  delete p;
}
void ARBOL::limpiar_arbol(void)
{
  int i = raiz->get_id_nodo();
  eliminar_arbol(raiz);
  raiz = NULL;
  set_nodo_inicial(i);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////  public  //
///////////////////////////////////////////////////////////////////////////////////////////////////
void ARBOL::mostrar_camino(NODO_ARBOL* p, int& coste)
{
  if(p != NULL) {
    mostrar_camino(p->get_padre(), coste);
    cout << p->get_id_nodo() + 1;
    if(p->get_num_hijos() != 0)
      cout << " -> ";
    if(p->get_padre() != NULL)
      coste += grafo->get_coste(p->get_padre()->get_id_nodo(), p->get_id_nodo());
  }
}
int ARBOL::get_coste_camino(NODO_ARBOL* p)
{
  if(p != NULL) {
    if(p->get_padre() != NULL)
      return grafo->get_coste(p->get_padre()->get_id_nodo(), p->get_id_nodo()) + 
	     get_coste_camino(p->get_padre());
    else
      return 0;
  }
  //else
    //return 0;
}
bool ARBOL::esta_en_el_camino(int n, NODO_ARBOL* p)
{
  if(p == NULL)
    return false;
  else if(p->get_id_nodo() == n)
    return true;
  else
    return esta_en_el_camino(n, p->get_padre());
}
NODO_ARBOL*  ARBOL::get_raiz(void)
{
  return raiz;
}
void ARBOL::Busqueda_Heuristica(int i/*= - 1*/, int f/*= -1*/)
{
  COLA cola;
  NODO_ARBOL *p_nodo_actual, *p_nodo_a_anadir;
  int nodo_actual, nodo_a_anadir;
  int nodos_generados = 1, nodos_analizados = 0, coste = 0;
  int coste_heuristico;
  bool camino_encontrado = false;
  if((i != -1)&&(f != -1)) { //Pasamos el parámetro de los nodos iniciales y finales
    set_nodo_inicial(i);
    set_nodo_final(f);
  }
  cola.push_heuristica(raiz, 0); //la raíz es siempre el primer nodo que se analiza
  while((cola.vacia() == false)&&(nodo_actual != nodo_final)) {
    if(imprimir_cola == true)
      cola.imprimir();
    p_nodo_actual = cola.pop_heuristica(); //nodo actual
    nodos_analizados++;
    nodo_actual = p_nodo_actual->get_id_nodo();
    if(nodo_actual != nodo_final) {
      for(int i = 0; i < ((grafo->get_nodo(nodo_actual)->get_num_hijos())); i++) //iterar hijos nodo actual
      {
	nodo_a_anadir = grafo->get_nodo(nodo_actual)->get_hijo(i);
	if(esta_en_el_camino(nodo_a_anadir, p_nodo_actual) == false) {
	  p_nodo_a_anadir = new NODO_ARBOL(nodo_a_anadir); //puntero al nuevo nodo a añadir
	  p_nodo_a_anadir->set_padre(p_nodo_actual); //el padre del nodo a añadir es el nodo actual
	  p_nodo_actual->add_hijo(p_nodo_a_anadir);
	  coste_heuristico = grafo->get_coste_heuristica(nodo_a_anadir, nodo_final);
	  coste_heuristico += get_coste_camino(p_nodo_a_anadir);
	  cola.push_heuristica(p_nodo_a_anadir, coste_heuristico);
	  nodos_generados++;
	  }
      }
    }
    else {
      camino_encontrado = true;
      cout << endl;
      mostrar_camino(p_nodo_actual, coste);
      cout << " (Coste: " << coste << ")" << endl;
      cout << "Nodos generados:  " << nodos_generados << endl;
      cout << "Nodos analizados: " << nodos_analizados << endl;
    }
  }
  if(camino_encontrado == false)
    cout << "Camino no encontrado" << endl;
  limpiar_arbol();
}
void ARBOL::DFS(int i/*= - 1*/, int f/*= -1*/)
{
  COLA cola;
  NODO_ARBOL *p_nodo_actual, *p_nodo_a_anadir;
  int nodo_actual, nodo_a_anadir;
  int nodos_generados = 1, nodos_analizados = 0, coste = 0;
  bool camino_encontrado = false;
  if((i != -1)&&(f != -1)) { //Pasamos el parámetro de los nodos iniciales y finales
    set_nodo_inicial(i);
    set_nodo_final(f);
  }
  cola.push(raiz);
  while((cola.vacia() == false)&&(nodo_actual != nodo_final)) {
    if(imprimir_cola == true)
      cola.imprimir();
    p_nodo_actual = cola.pop(); //nodo actual
    nodos_analizados++;
    nodo_actual = p_nodo_actual->get_id_nodo();
    if(nodo_actual != nodo_final) {
      for(int i = grafo->get_nodo(nodo_actual)->get_num_hijos() - 1; i >= 0; i--) //iterar hijos nodo actual
      {
	nodo_a_anadir = grafo->get_nodo(nodo_actual)->get_hijo(i);
	if(esta_en_el_camino(nodo_a_anadir, p_nodo_actual) == false) {
	  p_nodo_a_anadir = new NODO_ARBOL(nodo_a_anadir); //puntero al nuevo nodo a añadir
	  p_nodo_a_anadir->set_padre(p_nodo_actual); //el padre del nodo a añadir es el nodo actual
	  p_nodo_actual->add_hijo(p_nodo_a_anadir);
	  cola.push_front(p_nodo_a_anadir);
	  nodos_generados++;
	  }
      }
    }
    else {
      camino_encontrado = true;
      cout << endl;
      mostrar_camino(p_nodo_actual, coste);
      cout << " (Coste: " << coste << ")" << endl;
      cout << "Nodos generados:  " << nodos_generados << endl;
      cout << "Nodos analizados: " << nodos_analizados << endl;
    }
  }
  if(camino_encontrado == false)
    cout << "Camino no encontrado" << endl;
  limpiar_arbol();
}
void ARBOL::BFS(int i/*= - 1*/, int f/*= -1*/)
{
  COLA cola;
  NODO_ARBOL *p_nodo_actual, *p_nodo_a_anadir;
  int nodo_actual, nodo_a_anadir;
  int nodos_generados = 1, nodos_analizados = 0, coste = 0;
  bool camino_encontrado = false;
  if((i != -1)&&(f != -1)) { //Pasamos el parámetro de los nodos iniciales y finales
    set_nodo_inicial(i);
    set_nodo_final(f);
  }
  cola.push(raiz);
  while((cola.vacia() == false)&&(nodo_actual != nodo_final)) {
    if(imprimir_cola == true)
      cola.imprimir();
    p_nodo_actual = cola.pop(); //nodo actual
    nodos_analizados++;
    nodo_actual = p_nodo_actual->get_id_nodo();
    if(nodo_actual != nodo_final) {
      for(int i = 0; i < ((grafo->get_nodo(nodo_actual)->get_num_hijos())); i++) //iterar hijos nodo actual
      {
	nodo_a_anadir = grafo->get_nodo(nodo_actual)->get_hijo(i);
	if(esta_en_el_camino(nodo_a_anadir, p_nodo_actual) == false) {
	  p_nodo_a_anadir = new NODO_ARBOL(nodo_a_anadir); //puntero al nuevo nodo a añadir
	  p_nodo_a_anadir->set_padre(p_nodo_actual); //el padre del nodo a añadir es el nodo actual
	  p_nodo_actual->add_hijo(p_nodo_a_anadir);
	  cola.push(p_nodo_a_anadir);
	  nodos_generados++;
	  }
      }
    }
    else {
      camino_encontrado = true;
      cout << endl;
      mostrar_camino(p_nodo_actual, coste);
      cout << " (Coste: " << coste << ")" << endl;
      cout << "Nodos generados:  " << nodos_generados << endl;
      cout << "Nodos analizados: " << nodos_analizados << endl;
    }
  }
  if(camino_encontrado == false)
    cout << "Camino no encontrado" << endl;
  limpiar_arbol();
}
void  ARBOL::set_nodo_inicial(int i)
{
  if(raiz != NULL)
    eliminar_arbol(raiz);
  raiz = new NODO_ARBOL(i);
    
}
void  ARBOL::set_nodo_final(int f)
{
  nodo_final = f;
}
void  ARBOL::set_grafo(GRAFO* grf)
{
  grafo = grf;
}
void ARBOL::set_imprimir_cola(bool b)
{
  imprimir_cola = b;
}
ARBOL::ARBOL(int i, int f, GRAFO* grf)
{
  raiz = new NODO_ARBOL(i); //se inicializa la raiz
  nodo_final = f;
  grafo = grf;
  imprimir_cola = false;
}
ARBOL::ARBOL(GRAFO* grf)
{
  raiz = NULL;
  nodo_final = -1;
  grafo = grf;
  imprimir_cola = false;
}
ARBOL::ARBOL(void)
{
  raiz = NULL;
  nodo_final = -1;
  grafo = NULL;
  imprimir_cola = false;
}
ARBOL::~ARBOL(void)
{
  if(raiz != NULL)
    eliminar_arbol(raiz);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                         NODO  //
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////  public  //
///////////////////////////////////////////////////////////////////////////////////////////////////
void NODO::set_num_hijos(int n_hijos)
{
  num_hijos = n_hijos;
  if(num_hijos != 0)
    hijo = new int[num_hijos];
}
void NODO::set_hijo(int hij)
{
  if(hijos_agregados < num_hijos)
    hijo[hijos_agregados] = hij;
  else
    cout << " Error al agregar hijos. " << endl;
  hijos_agregados++;
}
int NODO::get_num_hijos(void)
{
  return num_hijos;
}
int NODO::get_hijo(int i)
{
  return i < num_hijos ? hijo[i] : -1;
}
void NODO::mostrar_hijos(bool sumar_uno)
{
  for(int i = 0; i < num_hijos; i++)
  {
    if(hijo[i] + sumar_uno < 10)
      cout << " ";
    cout << hijo[i] + sumar_uno;
    if(i != num_hijos - 1)
      cout << "  ->  ";
  }
  cout << endl;
}
NODO::NODO(void)
{
  num_hijos = hijos_agregados = 0;
  hijo = NULL;
}
NODO::~NODO(void)
{
  delete hijo;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                        GRAFO  //
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////  public  //
///////////////////////////////////////////////////////////////////////////////////////////////////
bool GRAFO::exito(void)
{
  return encontrado_archivo;
}
int GRAFO::get_num_nodos(void)
{
  return num_nodos;
}
NODO* GRAFO::get_nodo(int i)
{
  return &nodo[i];
}
int GRAFO::get_coste(int i, int j)
{
  if((i >= 0)&&(i < num_nodos)&&(j >= 0)&&(j < num_nodos))
    return matriz_costos[i][j];
  else
    return INF;
}
int GRAFO::get_coste_heuristica(int i, int j)
{
  if((i >= 0)&&(i < num_nodos)&&(j >= 0)&&(j < num_nodos))
    return matriz_heuristica[i][j];
  else
    return INF;
}
void GRAFO::imprimir(bool sumar_uno)
{
  for(int i = 0; i < num_nodos; i++)
  {
    if(i + sumar_uno < 10)
      cout << " ";
    cout << "    [" << i + sumar_uno << "] ";
    if(nodo[i].get_num_hijos() != 0) {
      cout << "-> ";
      nodo[i].mostrar_hijos(true);
    }
  }
  cout << endl;
}
GRAFO::GRAFO(char nom_adyacencia[], char nom_costos[], char nom_heuristica[])
{
  int no_usar, n_hijos = 0;
  bool** matriz_adyacencia;
  ifstream flujo_adyacencia, flujo_costos, flujo_heuristica;
  encontrado_archivo = false;
  flujo_adyacencia.open(nom_adyacencia);
  flujo_costos.open(nom_costos);
  flujo_heuristica.open(nom_heuristica);
  if(flujo_adyacencia.fail()||flujo_costos.fail()||flujo_heuristica.fail())
    cout << "Error al abrir el fichero." << endl;
  else {
    flujo_adyacencia >> num_nodos; //numero de nodos
    flujo_costos >> no_usar; //desechar el número de nodos
    flujo_heuristica >> no_usar;
    nodo = new NODO[num_nodos]; //inicializar nodos
    matriz_adyacencia = new bool*[num_nodos];
    matriz_costos = new int*[num_nodos];
    matriz_heuristica = new int*[num_nodos];
    for(int i = 0; i < num_nodos; i++) 
    {
      matriz_adyacencia[i] = new bool[num_nodos];
      matriz_costos[i] = new int[num_nodos];
      matriz_heuristica[i] = new int[num_nodos];
    }
    for(int i = 0; i < num_nodos; i++)
    {
      for(int j = 0; j < num_nodos; j++)
      {
	flujo_adyacencia >> matriz_adyacencia[i][j];
	flujo_costos >> matriz_costos[i][j];
	flujo_heuristica >> matriz_heuristica[i][j];
      }
    }
    flujo_adyacencia.close();
    flujo_costos.close();
    flujo_heuristica.close();
    for(int i = 0; i < num_nodos; i++)
    {
      for(int j = 0; j < num_nodos; j++) {
	if(matriz_adyacencia[i][j] == true)
	  n_hijos++;
      }
      nodo[i].set_num_hijos(n_hijos);
      for(int j = 0; j < num_nodos; j++) {
	if(matriz_adyacencia[i][j] == true)
	  nodo[i].set_hijo(j);
      }
      n_hijos = 0;
    }
    for(int i = 0; i < num_nodos; i++) 
      delete matriz_adyacencia[i];
    delete matriz_adyacencia;
    encontrado_archivo = true;
  }  
}
GRAFO::~GRAFO(void) 
{
  for(int i = 0; i < num_nodos; i++)
  {
    delete[] matriz_heuristica[i];
    delete[] matriz_costos[i];
  }
  delete[] nodo;
  delete[] matriz_heuristica;
  delete[] matriz_costos;
  
}