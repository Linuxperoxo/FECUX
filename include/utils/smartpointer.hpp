#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <cstddef>
#include <sys/mman.h> 

template <typename T>
class smt_ptr{
private:
  T* _ptr;
  size_t _ptr_size;
public:
  explicit smt_ptr(const size_t& _allocation_size = sizeof(T), void* _allocation_addrs = nullptr);
  
  smt_ptr(smt_ptr<T>&& _other_ptr) noexcept;
  
  smt_ptr& operator=(smt_ptr<T>&& _other_ptr) noexcept;
  
  int free() noexcept;

  T& operator*() const noexcept;
  T* operator->() const noexcept;

  smt_ptr(const smt_ptr&) = delete;
  smt_ptr& operator=(const smt_ptr&) = delete;
};

//#include "smartpointer.cpp"

#endif
