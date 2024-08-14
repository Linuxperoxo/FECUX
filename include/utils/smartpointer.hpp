#ifndef SMARTPOINTER_HPP
#define SMARTPOINTER_HPP

#include <cstddef>
#include <cstdlib>

#include "exception.hpp"

template <typename T>
class smt_ptr{
private:
  T* _ptr;
  size_t _ptr_size;
public:
  explicit smt_ptr(const size_t& _alloc_size = sizeof(T)) 
    : _ptr(static_cast<T*>(malloc(_alloc_size))), _ptr_size(_alloc_size){
    if(_ptr == nullptr){
      throw caroexception("Error when trying to allocate memory", MEMORY_ALLOCATION_ERROR_CODE);
    }
  }

  smt_ptr(smt_ptr&& _other_ptr) noexcept 
    : _ptr(_other_ptr._ptr), _ptr_size(_other_ptr._ptr_size){
    _other_ptr = nullptr;
    _ptr_size = 0;
  }

  ~smt_ptr(){
    free();
  }

  int free() noexcept{
    if(_ptr != nullptr){
      free(_ptr);
      _ptr = nullptr;
    }
    return 1;
  }

  smt_ptr& operator=(smt_ptr&& _other_ptr){
    if(this != &_other_ptr){
      free();

      _ptr = _other_ptr._ptr;
      _ptr_size = _other_ptr._ptr_size;

      _other_ptr._ptr = nullptr;
      _other_ptr._ptr_size = 0;
    }
  }

  T* operator->() const{
    if(_ptr == nullptr){
      throw caroexception("Attempt to access a member of a null pointer");
    }
    return _ptr;
  }

  T& operator*() const{
    if(_ptr == nullptr){
      throw caroexception("Attempt to dereference a null pointer", ATTEMPT_DEREFERENCE_NULLPTR);   
    }
    return *_ptr;
  }

  smt_ptr(const smt_ptr&) = delete;
  smt_ptr& operator=(const smt_ptr&) = delete;
};

#endif
