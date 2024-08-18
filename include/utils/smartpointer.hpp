//==========================================|
//   FILE: smartpointer.hpp                 |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef SMARTPOINTER_HPP
#define SMARTPOINTER_HPP

#include <cstddef>
#include <cstdlib>
#include <utility>

#include "caroexception.hpp"

template <typename T>
class smt_ptr{
private:
  T* _ptr;
  size_t _ptr_size;
public:
  template <typename... Args>
  explicit smt_ptr(const size_t& _alloc_size = sizeof(T), Args&&... args)
    : _ptr(nullptr), _ptr_size(_alloc_size){
    if(_alloc_size < sizeof(T)){
      throw caroexception(ALLOCATION_SIZE_TOO_SMALL);
    }
    
    _ptr = static_cast<T*>(malloc(_alloc_size));

    if(_ptr == nullptr){
      throw caroexception(MEMORY_ALLOCATION_ERROR);
    }

    new(_ptr) T(std::forward<Args>(args)...);
  }

  smt_ptr(smt_ptr&& _other_ptr) noexcept 
    : _ptr(_other_ptr._ptr), _ptr_size(_other_ptr._ptr_size){
    _other_ptr._ptr = nullptr;
    _other_ptr._ptr_size = 0;
  }

  ~smt_ptr(){
    relax();
  }

  void relax() noexcept{
    if(_ptr != nullptr){
      _ptr->~T();
      std::free(_ptr);
      _ptr = nullptr;
    }
  }

  smt_ptr& operator=(smt_ptr&& _other_ptr) noexcept{
    if(this != &_other_ptr){
      relax();
      _ptr = _other_ptr._ptr;
      _ptr = _other_ptr._ptr_size;
      _other_ptr._ptr = nullptr;
      _other_ptr._ptr_size = 0;
    }
    return *this;
  }

  T& operator*() const{
    if(_ptr == nullptr){
      throw caroexception(ATTEMPT_DEREFERENCE_NULLPTR);
    }
    return *_ptr;
  } 

  T* operator->() const{
    if(_ptr == nullptr){
      throw caroexception(ATTEMPT_MEMBER_NULLPTR);
    }
    return _ptr;
  }

  smt_ptr& operator=(const smt_ptr&) = delete;
  smt_ptr(const smt_ptr&) = delete;
};

#endif
