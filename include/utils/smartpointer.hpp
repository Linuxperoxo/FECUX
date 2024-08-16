//==========================================|
//   FILE: smartpointer.hpp                 |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef SMARTPOINTER_HPP
#define SMARTPOINTER_HPP

#include <cstdlib>
#include <new>

#include "caroexception.hpp"

template <typename T>
class smt_ptr{
private:
  T* _ptr;
public:
  explicit smt_ptr(T* _new_ptr = nullptr)
    : _ptr(_new_ptr){
    if(_new_ptr == nullptr){
      _ptr = new(std::nothrow) T;
      if(_ptr == nullptr){
        throw caroexception(MEMORY_ALLOCATION_ERROR);
      }
    }
  }

  smt_ptr(smt_ptr&& _other_ptr) noexcept 
    : _ptr(_other_ptr._ptr){
    _other_ptr._ptr = nullptr;
  }

  ~smt_ptr(){
    relax();
  }

  void relax() noexcept{
    if(_ptr != nullptr){
      delete _ptr;
      _ptr = nullptr;
    }
  }

  smt_ptr& operator=(smt_ptr&& _other_ptr) noexcept{
    if(this != &_other_ptr){
      relax();
      _ptr = _other_ptr._ptr;
      _other_ptr._ptr = nullptr;
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
