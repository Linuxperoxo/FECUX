//==========================================|
//   FILE: smartpointer.hpp                 |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef SMARTPOINTER_HPP
#define SMARTPOINTER_HPP

#include <cstddef>
#include <cstdlib>
#include <new>

#include "../caroline/caroexception.hpp"

/**
 * A classe `smt_ptr` é um ponteiro inteligente que gerencia a alocação e desalocação de memória para um objeto
 * do tipo T. Ela implementa o conceito básico de um ponteiro inteligente com construtor, move constructor, 
 * move assignment operator e operadores de acesso. Não suporta cópias.
 */
template <typename T>
class smt_ptr {
private:
  T* _ptr;          // Ponteiro para o objeto gerenciado
  size_t _ptr_size; // Tamanho da memória alocada

public:
  /**
   * Construtor da classe `smt_ptr` que aloca memória para armazenar um objeto do tipo T e o constrói na 
   * memória alocada. O uso de `std::forward` permite que os argumentos sejam passados de forma perfeita para 
   * o construtor de T.
   *
   * @param _alloc_size Tamanho da memória a ser alocada. Por padrão, é o tamanho de T.
   * @param args Argumentos para o construtor de T, passados de forma perfeita.
   */
  template <typename... Args>
  explicit smt_ptr(const size_t _alloc_size = sizeof(T), Args&&... args)
    : _ptr(nullptr), _ptr_size(_alloc_size) {

    // Aloca memória dinamicamente para armazenar um objeto do tipo T.
    // `malloc` retorna um ponteiro void*, que é convertido para T*.
    _ptr = static_cast<T*>(malloc(_alloc_size));

    if(_ptr == nullptr){
      // Lança uma exceção personalizada se a alocação falhar
      throw caroline::caroexception(MEMORY_ALLOCATION_ERROR);
    }

    // Constrói um objeto do tipo T na memória alocada.
    // O operador new com sintaxe de "placement" constrói o objeto diretamente na memória alocada.
    
    try{
      new(_ptr) T(std::forward<Args>(args)...);
    }
    
    catch(...){
      std::free(_ptr);
      _ptr = nullptr;
      throw caroline::caroexception(MEMORY_ALLOCATION_ERROR);
    }
  }

  /**
   * Move constructor que transfere a posse do ponteiro de `_other_ptr` para o objeto atual.
   * O ponteiro em `_other_ptr` é definido como nullptr após a transferência.
   *
   * @param _other_ptr Objeto `smt_ptr` de onde o ponteiro é movido.
   */
  smt_ptr(smt_ptr&& _other_ptr) noexcept
    : _ptr(_other_ptr._ptr), _ptr_size(_other_ptr._ptr_size) {
    _other_ptr._ptr = nullptr; // Define o ponteiro em `_other_ptr` como nullptr
    _other_ptr._ptr_size = 0;  // Define o tamanho em `_other_ptr` como 0
  }

  /**
   * Move assignment operator que libera a memória do objeto atual, transfere os dados do 
   * ponteiro de `_other_ptr` para o objeto atual e define o ponteiro em `_other_ptr` como nullptr.
   *
   * @param _other_ptr Objeto `smt_ptr` de onde o ponteiro é movido.
   * @return Referência ao objeto atual.
   */
  smt_ptr& operator=(smt_ptr&& _other_ptr) noexcept{
    if (this != &_other_ptr) {
      // Libera a memória do objeto atual
      release();

      // Atribui os novos elementos para o objeto atual
      _ptr = _other_ptr._ptr;
      _ptr_size = _other_ptr._ptr_size;
      _other_ptr._ptr = nullptr; // Define o ponteiro em `_other_ptr` como nullptr
      _other_ptr._ptr_size = 0;  // Define o tamanho em `_other_ptr` como 0
    }
    return *this;
  }

  T* getPtr() const noexcept{
    return _ptr;
  }

  /**
   * Libera a memória alocada e destrói o objeto. Define o ponteiro como nullptr após a liberação.
   */
  void release() const noexcept{
    if (_ptr != nullptr) {
      _ptr->~T();   // Chama o destrutor do objeto T na memória alocada
      std::free(_ptr); // Libera a memória alocada
      _ptr = nullptr; // Define o ponteiro como nullptr
    }
  }

  /**
   * Operador de desreferenciação que retorna uma referência ao objeto gerenciado. Lança uma exceção se o ponteiro
   * for nullptr.
   *
   * @return Referência ao objeto gerenciado.
   */
  T& operator*() const{
    if (_ptr == nullptr) {
      throw caroline::caroexception(ATTEMPT_DEREFERENCE_NULLPTR);
    }
    return *_ptr;
  }

  /**
   * Operador de acesso a membros que retorna um ponteiro para o objeto gerenciado. Lança uma exceção se o ponteiro
   * for nullptr.
   *
   * @return Ponteiro para o objeto gerenciado.
   */
  T* operator->() const{
    if (_ptr == nullptr) {
      throw caroline::caroexception(ATTEMPT_MEMBER_NULLPTR);
    }
    return _ptr;
  }

  // Proíbe a cópia da classe `smt_ptr`
  smt_ptr& operator=(const smt_ptr&) = delete; // Desativa o operador de atribuição por cópia
  smt_ptr(const smt_ptr&) = delete; // Desativa o construtor de cópia
};

#endif
