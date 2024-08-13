#include "smartpointer.hpp"
#include "exception.hpp"

template <typename T>
smt_ptr<T>::smt_ptr(const size_t& _allocation_size, void* _allocation_addrs) 
  : _ptr_size(_allocation_size), _ptr(static_cast<T*>(mmap(_allocation_addrs, _allocation_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0))){
  if(_ptr == nullptr){
    throw caroexception("Bad allocation for mmap");
  }
}

template <typename T>
smt_ptr<T>::smt_ptr(smt_ptr<T>&& _other_ptr) noexcept
  : _ptr(_other_ptr._ptr), _ptr_size(_other_ptr._ptr_size){
  _other_ptr._ptr = nullptr;
  _other_ptr._ptr_size = 0;
};

template <typename T>
smt_ptr<T>& smt_ptr<T>::operator=(smt_ptr<T>&& _other_ptr) noexcept{
  if(this != &_other_ptr){
    free();
    
    _ptr = _other_ptr._ptr;
    _ptr_size = _other_ptr._ptr_size;
    
    _other_ptr._ptr = nullptr;
    _other_ptr._ptr_size = 0;
  }
  return *this;
}

template <typename T>
int smt_ptr<T>::free() noexcept{
  if(_ptr != nullptr){
    if(munmap(_ptr, _ptr_size) == -1){
      return -1;
    }
    _ptr = nullptr;
    _ptr_size = 0;
  }
  return 1;
}

template <typename T>
T& smt_ptr<T>::operator*() const noexcept{
  if(_ptr == nullptr){
    throw caroexception("Attempt to dereference a null pointer");
  }
  return *_ptr;  
}

template <typename T>
T* smt_ptr<T>::operator->() const noexcept{
  if(_ptr == nullptr){
    throw caroexception("Attempt to access a member of a null pointer");
  }
  return _ptr;
}

