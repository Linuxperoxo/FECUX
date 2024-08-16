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
  smt_ptr() 
    : _ptr(new (std::nothrow) T){
    if(_ptr == nullptr){
      throw caroexception(MEMORY_ALLOCATION_ERROR);
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

  int store(const T& _value) noexcept{
    if(_ptr != nullptr){
      _ptr->~T();
      _ptr = new (std::nothrow) T;

      if(_ptr == nullptr){
        return -1;
      }
      return 1;
    }  
    return -1;
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
