namespace Huby{
namespace interfaz{
  template<typename tipo>
  struct nodo{
    typedef tipo value_t;
    virtual tipo& operator* () = 0;
  };
}


namespace abstraccion{
  template<typename tipo>
  class nodo: public interfaz::nodo<tipo>{
    protected:
    tipo valor;
    nodo(tipo valor): valor{valor}{};
    public:
    virtual tipo& operator* (){return valor;}
  };

  namespace arbol{
  template<typename tipo>
  class nodo: public abstraccion::nodo<tipo>{
    public:
    nodo(tipo valor): abstraccion::nodo<tipo>{valor}{};
    virtual bool esHoja() = 0;
  };
}
}


namespace arbol_binario{
  template<typename tipo>
  class nodo: public abstraccion::arbol::nodo<tipo>{
    public:
    nodo* der = nullptr;
    nodo* izq = nullptr;

    nodo(tipo valor): abstraccion::arbol::nodo<tipo>{valor}{};
    virtual bool esHoja()override{return der == nullptr && izq == nullptr;}
    bool tieneDosHijos(){return (der != nullptr && izq != nullptr);}
    

  };
}

}