//==========================================|
//   FILE: managerobj.hpp                   |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef __MANAGEROBJ_HPP__
#define __MANAGEROBJ_HPP__

template <typename Class, typename... ArgsToConstruct>
inline Class *make_obj(void *_addrs_to_construct,
                       ArgsToConstruct... _construct_Args) noexcept {
  if (_addrs_to_construct != nullptr) {
    return new (_addrs_to_construct) Class(_construct_Args...);
  }
  return nullptr;
}

template <typename ClassToExpurg>
inline void expurg_obj(ClassToExpurg *_addrs_to_class) noexcept {
  if (_addrs_to_class != nullptr) {
    _addrs_to_class->~ClassToExpurg();
  }
}

#endif
