//==========================================|
//   FILE: managerobj.hpp                   |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef __MANAGEROBJ__
#define __MANAGEROBJ__

#include <utility>

template <typename Type, typename ... Args>
void make_obj(void* _addrs, Args&& ... args) noexcept{
  if(_addrs != nullptr){
    new(_addrs) Type(std::forward(args)...);
  }
}

template <typename Type>
void expurg_obj(Type* _addrs) noexcept{
  if(_addrs != nullptr){
    _addrs->~Type();
  }
}

#endif
