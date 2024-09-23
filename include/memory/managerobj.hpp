/*

  AUTHOR: Linuxperoxo
  COPYRIGHT: (c) 2024 per Linuxperoxo.
  FILE: managerobj.hpp

*/



/*

  Essa lib eu fiz pensando em facilitar e aproveitar o RAII do C++.

  Nesse projeto eu decidi que iria fazer a gestão da memória manualmente,
  usando malloc e free, porém, eles possuem um probleminha. O primeiro é que
  malloc não chama o construtor de um objeto, e o C++ trabalha muito com construtores
  e destrutores, por sorte, temos o placement new, com ele e com um pouco de templates
  conseguimos acabar com essa dificuldade e fazer uma chamada de construtor para qualquer
  tipo de objeto.

  O placement new funciona da seguinte maneira

  EX: MyClass* _MyClass = static_cast<MyClass*>(std::malloc(sizeof(MyClass)));
      new(_MyClass) MyClass(// Args para o construtor, se tiver);

  Pronto, construtor chamado. O new retorna um ponteiro para o objeto construído

*/



#include <utility>



namespace fecux{
namespace memory{



/*

  Abaixo tem a função que chama o construtor do objeto

  Você pode modificar a função para se encaixar exatamente do jeito que você quer.

  Coloquei um void* como argumento em vez de ObjType* por preferência, em vez de declarar um ponteiro
  que recebe o retorno do malloc posso colocar o próprio malloc como parâmetro

  EX:
    em vez de usar:
      MyClass* _MyClass = static_cast<MyClass*>(std::malloc(sizeof(MyClass)));
      fecux::memory::make_obj<MyClass>(_MyClass);

    posso usar:
      fecux::memory::make_obj<MyClass>(std::malloc(sizeof(MyClass)));
*/



template <typename ObjType, typename ... Args_to_constructor>
inline ObjType* make_obj(void* _addrs_to_make, Args_to_constructor&&... _args_to_constructor) noexcept{
  if(_addrs_to_make != nullptr){
    return new(_addrs_to_make) ObjType(std::forward<Args_to_constructor>(_args_to_constructor)...);
  }
  return nullptr;
}



/*

  Já essa função é a chamada explícita do destrutor do objeto

*/



template <typename ObjType>
inline int expurg_obj(void* _addrs_to_expurg) noexcept{
  if(_addrs_to_expurg != nullptr){
    static_cast<ObjType*>(_addrs_to_expurg)->~ObjType();
    return 1;
  }
  return -1;
}

} // namespace memory
} // namespace fecux
