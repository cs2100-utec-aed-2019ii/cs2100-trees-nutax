/*

Por José Ignacio Huby Ochoa
UTEC - Lima, Perú
CS - Algorítmos y estructura de datos

Trabajo PRINCIPAL: Implementación de BST

Trabajo EXTRA: Implementación de BT (madre de BST), iteradores, using/typefs, interfaces y clases abstractas

Trabajo a FUTURO: Si bien se emplea en (pocos) casos using (una versión moderna del typedef), no se implementó traits en esta versión por cuestiones de tiempo.

*/



#include <iostream>
#include <cassert>
#include "lista.h"
#include <string>

void seccion(std::string titulo){
  std::cout<<std::endl;
  std::cout<<std::endl;
  std::cout<<std::endl;
  std::cout<<"----------";
  std::cout<<std::endl;
  std::cout<<"Sección:"<<'\t'<<titulo;
  std::cout<<std::endl;
  std::cout<<"----------";
  std::cout<<std::endl;
}

void acotacion(std::string oracion){
  std::cout<<std::endl;
  std::cout<<"[ "<<oracion<<" ]";
  std::cout<<std::endl;

}

int main() {

  seccion("Contenedores no abstractos");
  Huby::binary_tree<int> bt;
  acotacion("Se crea un binary tree");
  Huby::binary_search_tree<int> bst;
  acotacion("Se crea un binary search tree, hijo de binary tree");

  seccion("Iteradores de contenedores");
  Huby::binary_tree<int>::iterator it_bt;
  acotacion("Se crea un iterador de binary tree");
  Huby::binary_search_tree<int>::iterator it_bst;
  acotacion("Se crea un iterador de binary search tree");


  seccion("Insertar elementos en binary tree");
  
  bt.insert(4, [](int a, int b){return a<10-b;});
  acotacion("Se inserta 2 en el binary tree, bajo una función de comparación X a<10-b");
  bt.insert(2, [](int a, int b){return a<b*10;});
  acotacion("Se inserta 4 en el binary tree, bajo una función de comparación X a<b*10");
  bt.insert(8, [](int a, int b){return a>b*12;});
  acotacion("Se inserta 8 en el binary tree, bajo una función de comparación X a>b*12");

  seccion("Insertar un nuevo elemento en binary search tree");
  bst.insert(2);
  acotacion("Se inserta 2 en el binary search tree");
  bst.insert(1);
  acotacion("Se inserta 1 en el binary search tree");
  bst.insert(0);
  acotacion("Se inserta 0 en el binary search tree");
  bst.insert(4);
  acotacion("Se inserta 4 en el binary search tree");
  bst.insert(3);
  acotacion("Se inserta 3 en el binary search tree");
  bst.insert(5);
  acotacion("Se inserta 5 en el binary search tree");

  seccion("Tamaño");
  std::cout<<bt.size();
  acotacion("Se imprime el tamaño en binary tree");
  std::cout<<bst.size();
  acotacion("Se imprime el tamaño en binary search tree");


  seccion("Imprimir preorder");
  bt.print_preorder();
  acotacion("Se imprime preorder binary tree");
  bst.print_preorder();
  acotacion("Se imprime preorder binary search tree");

  seccion("Imprimir inorder");
  bt.print_inorder();
  acotacion("Se imprime inorder binary tree");
  bst.print_inorder();
  acotacion("Se imprime inorder binary search tree");

  seccion("Imprimir posorder");
  bt.print_posorder();
  acotacion("Se imprime posorder binary tree");
  bst.print_posorder();
  acotacion("Se imprime posorder binary search tree");

  seccion("Iterar");
  it_bt = bt.begin();
  std::cout<<*(bt.begin())<<"->"<<*(--it_bt);
  acotacion("Se itera una vez hacia la izquierda desde begin en binary tree");
  it_bst = bst.begin();
  --it_bst;
  std::cout<<*(bst.begin())<<"->"<<*(--it_bst);
  acotacion("Se itera dos veces hacia la izquierda/menor lado desde begin en binary search tree");

  seccion("Next in level");
  std::cout<<*(it_bt);
  it_bt = bt.next_in_level(it_bt);
  std::cout<<"->"<<*(it_bt);
  acotacion("Se itera hasta el siguiente elemento en el mismo nivel en binary tree (si es que hay)");

  std::cout<<*(it_bst);
  it_bst = bst.next_in_level(it_bst);
  std::cout<<"->"<<*(it_bst);
  acotacion("Se itera hasta el siguiente elemento en el mismo nivel en binary search tree");

  seccion("Parents");
  bst.parents(it_bst);
  acotacion("Se itera por todos los parientes del iterador en binary search tree");
  acotacion("No se implementó en binary tree normal (no el search), porque resulta muy poco eficiente iterar sin una regla fija");

  seccion("Find");
  it_bst = bst.find(2);
  std::cout<<*it_bst;
  acotacion("Se busca el número 2 en binary search tree");
  acotacion("No se implementó en binary tree normal (no el search), porque resulta muy poco eficiente sin una regla fija");

  seccion("Erase");
  bst.erase(it_bst);
  std::cout<<*it_bst;
  acotacion("Se elimina el nodo y se retorna un iterador al actual sucesor. En caso de ser hoja, retorna su madre.");
  acotacion("No se implementó en binary tree normal (no el search), porque resulta muy poco eficiente sin una regla fija");

  seccion("Complete");
  std::cout<<((bt.complete()) ? "Es completo" : "No es completo");
  acotacion("Se verifica de manera recursiva si es completo o no en binary tree");
  std::cout<<((bst.complete()) ? "Es completo" : "No es completo");
  acotacion("Se verifica de manera recursiva si es completo o no en binary search tree");

  seccion("Balanced");
  std::cout<<((bt.balanced()) ? "Es balanceado" : "No es balanceado");
  acotacion("Se verifica de manera recursiva si es balanceado o no en binary tree");
  std::cout<<((bst.balanced()) ? "Es balanceado" : "No es balanceado");
  acotacion("Se verifica de manera recursiva si es balanceado o no en binary search tree");

  seccion("Comparar si es BST");
  using madre = Huby::binary_tree<int>;
  using hijo = Huby::binary_search_tree<int>;
  madre* bt_poli = new hijo;
  hijo* intento = dynamic_cast<hijo*>(bt_poli);
  acotacion("Se intenta convertir binary tree polimófico a binary search tree polimórfico");
  if(intento != nullptr)
    acotacion("Se logra convertir binary tree polimófico a binary search tree polimórfico");
  else
    acotacion("No se logra convertir binary tree polimófico a binary search tree polimórfico");
  
  

  seccion("Convertir BT a BST con misma estructura");
  Huby::binary_tree<int> nuevo_bt;
  acotacion("Se crea nuevo BT");

  nuevo_bt.insert(4, [](int a, int b){return a>b;});
  nuevo_bt.insert(2, [](int a, int b){return a*a*a>b;});
  nuevo_bt.insert(6, [](int a, int b){return a+1>b;});
  nuevo_bt.insert(1, [](int a, int b){return a+1>b;});
  nuevo_bt.insert(12, [](int a, int b){return a+1>b;});
  acotacion("Se añaden elementos en BT");
  nuevo_bt.print_inorder();
  acotacion("Se imprime en BT");

  Huby::binary_search_tree<int> nuevo_bst;
  acotacion("Se crea nuevo BST");
  nuevo_bst =  nuevo_bt;
  acotacion("Se iguala BST a un BT existente");
  nuevo_bst.print_inorder();
  acotacion("Se imprime en BST");
  
}