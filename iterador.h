namespace Huby{
namespace abstraccion{
  template <typename T>
  class iterador{
    public:
    typedef T node_t;
    typedef typename node_t::value_t value_t;
    
    node_t * pointer;  

    iterador(node_t* _pointer = nullptr):pointer(_pointer){
    }

    ~iterador(void){
    }

    virtual bool operator!= (iterador it){
      return pointer != it.pointer;
    }

    virtual bool operator== (iterador it){
      return pointer == it.pointer;
    }

    virtual value_t& operator* (void) {
      return *(*pointer);
    }

    virtual void operator=(iterador it) {
      pointer = it.pointer;
    }

    void destroy(){
      delete pointer;
    }

  };
}
}
