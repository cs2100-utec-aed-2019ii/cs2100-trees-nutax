#include "nodo.h"
#include "iterador.h"
#include <iostream>
#include <functional>
#include <cstdlib>

namespace Huby{

namespace interfaz{
  template<typename T>
  struct lista{

	virtual bool empty() = 0;
	virtual unsigned int size() = 0;
	virtual void clear() = 0;

  };
}


namespace abstraccion{
  template<typename tipo>
  class arbolito: public interfaz::lista<tipo>{
    public:
    unsigned int sz = 0;
    virtual bool empty(){return false;};
    virtual unsigned int size() {return this->sz;};
    virtual void clear() {};
  };
}

template<typename tipo>
class binary_tree: public abstraccion::arbolito<tipo>{
    protected:
    using nodo = arbol_binario::nodo<tipo>;
    nodo* raiz = nullptr;
    public: 

    class iterator: public abstraccion::iterador<nodo>{
      public:
      iterator(nodo* _pointer = nullptr):abstraccion::iterador<nodo>(_pointer){}

      iterator& operator++(){this->pointer = this->pointer->der; return *this;}
      iterator& operator--(){this->pointer = this->pointer->izq;return *this;}
      void anadirIzq(const tipo& valor){
        this->pointer->izq = new nodo(valor);
      }
      void anadirIzq(iterator it){
        this->pointer->izq = it.pointer;
      }
      void anadirDer(const tipo& valor){
        this->pointer->der = new nodo(valor);
      }
      void anadirDer(iterator it){
        this->pointer->der = it.pointer;
      }
      bool esHoja(){
        return this->pointer->esHoja();
      }
      bool tieneDosHijos(){
        return this->pointer->tieneDosHijos();
      }
    };

    iterator begin(){
      iterator temporal(this->raiz);
      return temporal;
    }
    
    bool complete(){
      if (this->sz == 0) 
              return (true);
      int index = 0;
      iterator inicio = this->begin();
      return complete(index, inicio);
    }

      bool complete (unsigned int index, iterator& actual) 
      {
        if(actual==nullptr){
          return true;
        }
          if (index >= this->sz) 
              return (false); 

          iterator iz = actual;
          iterator de = actual;
          return (complete(2*index + 1, --iz) && complete( 2*index + 2, ++de)); 
      } 
    void insert(const tipo& valor, std::function<bool(tipo, tipo)> comparacion){
      if(this->raiz == nullptr){
        this->raiz = new nodo(valor);
        this->sz++;
      }else{
        
        iterator actual(this->raiz);
        iterator madre(this->raiz);
        
        while(actual != nullptr){
          
          if(comparacion){
            
            --actual;
            if(actual != nullptr){
            --madre;
          }
          }else{
            
            ++actual;
            if(actual != nullptr){
            ++madre;
          }
          }
          
        }
        if(comparacion){
          madre.anadirIzq(valor);
          this->sz++;
        }else{
          madre.anadirDer(valor);
          this->sz++;
        }

      }

      }

    void print_preorder(iterator& it){
      iterator actual = it;
      iterator izq = it;
      iterator der = it;
      --izq; ++der;
      if(actual != nullptr){
        std::cout<<*actual<<'\t';
      }
      if(izq != nullptr){
        print_preorder(izq);
      }
      if(der != nullptr){
        print_preorder(der);
      }
    }

    void siguiente_inorder(iterator& it, iterator actual, int& estado){
      iterator izq = actual;
      iterator der = actual;
      --izq; ++der;
      if(izq != nullptr){
        siguiente_inorder(it, izq, estado);
      }
      if(actual != nullptr){
        if(actual == it){
          estado = 1;
        }else{
          if(estado == 1){
            it = actual;
            estado = 2;
          }
        }
      }
      if(der != nullptr){
        siguiente_inorder(it, der, estado);
      }
    }

    void siguiente_inorder(iterator& it){
      iterator inicio = this->begin();
      int estado = 0;
      siguiente_inorder(it, inicio, estado);
    }

    void print_inorder(iterator& it){
      iterator actual = it;
      iterator izq = it;
      iterator der = it;
      --izq; ++der;
      if(izq != nullptr){
        print_inorder(izq);
      }
      if(actual != nullptr){
        std::cout<<*actual<<'\t';
      }
      if(der != nullptr){
        print_inorder(der);
      }
    }

    void print_posorder(iterator& it){
      iterator actual = it;
      iterator izq = it;
      iterator der = it;
      --izq; ++der;
      if(izq != nullptr){
        print_posorder(izq);
      }
      if(der != nullptr){
        print_posorder(der);
      }
      if(actual != nullptr){
        std::cout<<*actual<<'\t';
      }
    }
    

    void print_preorder(void){
      std::cout<<std::endl;
      std::cout<<"Preorder: "<<'\t';
      iterator temp = this->begin();
     print_preorder(temp);
     std::cout<<std::endl;
    }

    void print_posorder(void){
      std::cout<<std::endl;
      std::cout<<"Posorder: "<<'\t';
      iterator temp = this->begin();
      print_posorder(temp);
      std::cout<<std::endl;
    }

    void print_inorder(void){
      std::cout<<std::endl;
      std::cout<<"Inorder: "<<'\t';
      iterator temp = this->begin();
      print_inorder(temp);
      std::cout<<std::endl;
    }

    void next_in_level(iterator& it, iterator actual, int& nivel, int n, bool& listo){
      

      if(nivel != -1){
        if(nivel == n){
          it = actual;
          listo = true;
          return;
        }
      }else{
        if(it == actual){
          nivel = n;
          return;
        }
      }

      if(!listo){
      iterator izq = actual;
      if(--izq != nullptr)
        this->next_in_level(it, izq, nivel, n + 1, listo);
      }

      if(!listo){
      if(++actual != nullptr)
        this->next_in_level(it, actual, nivel, n + 1, listo);
      }

    }


    virtual iterator next_in_level(iterator it){
      iterator inicio = this->begin();
      int nivel = -1;
      bool listo = false;
      this->next_in_level(it, inicio, nivel, 0, listo);
      return it;
    }
    
    void count(iterator& it, int& n){
      iterator izq = it;
      iterator der = it;
      --izq; ++der;
      if(it != nullptr){
        n++;
      }
      if(izq != nullptr){
        count(izq, n);
      }
      if(der != nullptr){
        count(der, n);
      }
    }

    bool balanced(iterator& it){
      if(it == nullptr)return true;
      int a = 0;
      int b = 0;
      iterator iz = it;
      iterator de = it;
      if(--iz != nullptr)count(iz, a);
      if(++de != nullptr)count(de, b);
      return ( abs(a - b) <= 1 ) && balanced(iz) && balanced(de);
    }

    bool balanced(){
      iterator inicio = this->begin();
      return balanced(inicio);
    }

    
  };


template<typename tipo>
class binary_search_tree: public binary_tree<tipo>{
public:
using nodo = typename binary_tree<tipo>::nodo;
using iterator = typename binary_tree<tipo>::iterator;

iterator find(const tipo& valor){
      iterator actual(this->raiz);
      while(actual != nullptr){
        if(valor < *actual ){
          --actual;
        }else{
          if(valor > *actual ){
            ++actual;
          }else{
            return actual;
          }
        }
      }
      return actual;
    };
	  void insert(const tipo& valor){
      if(this->raiz == nullptr){
        this->raiz = new nodo(valor);
        this->sz++;
      }else{
        
        iterator actual(this->raiz);
        iterator madre(this->raiz);
        
        while(actual != nullptr){
          
          if(valor < *actual){
            
            --actual;
            if(actual != nullptr){
            --madre;
          }
          }else{
            
            ++actual;
            if(actual != nullptr){
            ++madre;
          }
          }
          
        }
        if(valor < *madre){
          madre.anadirIzq(valor);
        }else{
          madre.anadirDer(valor);
        }
        this->sz++;

      }
    }

    void parents(iterator& it){
      std::cout<<std::endl;
      std::cout<<"Parents of "<<*it<<':'<<'\t';
      iterator actual(this->raiz);
      while(actual != nullptr){
        if(*it < *actual ){
          std::cout<<*actual<<'\t';
          --actual;
        }else{
          if(*it > *actual ){
            std::cout<<*actual<<'\t';
            ++actual;
          }else{
            return;
          }
        }
      }
    };

    iterator mother(iterator& it){
      iterator actual(this->raiz);
        iterator madre(this->raiz);
        while(actual != it){
          
          if(*it < *actual){
            --actual;
            if(actual != it){
            --madre;
          }
          }else{
            ++actual;
            if(actual != it){
            ++madre;
          }
          }
        }
        return madre;
    }

    void erase(iterator& it){
        iterator madre = this->mother(it);
        iterator hermano_menor = madre;
        --hermano_menor;
        bool dir = (hermano_menor == it);
        //true izq, false der
        iterator sucesor;
        if(!it.esHoja()){
          if(!(it.tieneDosHijos())){
            iterator iz = it;
            iterator de = it;
            --iz;
            sucesor = (iz != nullptr) ? iz : --de;
        }else{
          sucesor = it;
          this->siguiente_inorder(sucesor);
          *it = *sucesor;
          sucesor.destroy();
          this->sz--;
          return;
        }
        }
        if(it == madre){
          this->raiz = sucesor.pointer;
          it.destroy();
          it = sucesor;
        }else{
          if(dir) madre.anadirIzq(sucesor); else madre.anadirDer(sucesor);
          it.destroy();
          it = (sucesor != nullptr) ? sucesor : madre;
        }
        this->sz--;
        
        
    }
    
    void bt_insertar(iterator it){
      iterator izq = it;
      iterator der = it;
      --izq; ++der;
      if(izq != nullptr){
        bt_insertar(izq);
      }
      if(der != nullptr){
        bt_insertar(der);
      }
      if(it != nullptr){
        this->insert(*it);
      }
    }

    void operator=(binary_tree<tipo> bt){
      bt_insertar(bt.begin());
    }

    void insert(const tipo& valor, std::function<bool(tipo, tipo)> comparacion) = delete;
};

}


