/*

  COPYRIGHT: (c) 2024 per Linuxperoxo.
  AUTHOR: Linuxperoxo
  FILE: make_obj.hpp
  
*/

#ifndef __MAKE_OBJ_HPP__
#define __MAKE_OBJ_HPP__

#include <utility>

namespace fecux{
namespace memory{

/* <=========================================================================>
 */

/*
  @info:
    Constroi um objeto no início do bloco passado;

  @param:
    -*- void *: Recebe um ponteiro genérico para o início do
    bloco onde o objeto será construido;

    -*- Args: Argumentos que seram passado para o construtor;

  @return:
    Se tudo ocorrer bem, retorna um ponteiro para o objeto
    construido, caso contrario, retorna um nullptr;

*/

/* <=======================================================================> */

template <typename ClassType, typename... Args>
inline void *make(void *_addrs_to_make, Args &&...args) noexcept{
  if(_addrs_to_make != nullptr){
    return new (_addrs_to_make) ClassType(std::forward<Args>(args)...);
  }
  return nullptr;
}

/* <=============================================================================>
 */

/*
  @info:
    Chama o destrutor do objeto explicitamente;

  @param:
    -*- void *: Recebe um ponteiro genérico para o inicio do
    bloco onde o objeto está construido;

  @return:
    O retorno é apenas uma simples verificação para vê se o
    destrutor do objeto realmente foi chamado, return 1 para
    tudo certo, o construtor foi chamado, -1 caso o destrutor
    não for chamado;
*/

/* <==============================================================================>
 */

template <typename ClassType>
inline int expurg(void *_addrs_to_expurg) noexcept{
  if(_addrs_to_expurg != nullptr){
    static_cast<ClassType *>(_addrs_to_expurg)->~ClassType();
    return 1;
  }
  return -1;
}

} // namespace memory
} // namespace fecux

#endif
