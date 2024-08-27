//==========================================|
//   FILE: package.hpp                      |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include <cstddef>

namespace caroline{

class package{
private:
  char* _pkg_name;
  char* _pkg_version;
  char* _pkg_url;
  char* _pkg_desc;

  char** _pkg_functions;
  size_t _array_size;

  char* _pkg_root;

  void mount(const char* _pkg);
  void loadVar(const char* _pkg);
  void loadFunctions(const char* _pkg);
public:
  package(const char* _pkg) noexcept;
  ~package() noexcept;

  const char* name() const noexcept;
  const char* version() const noexcept;
  const char* url() const noexcept;
  const char* desc() const noexcept;
}; 

}

#endif
