//==========================================|
//   FILE: package.hpp                      |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef PACKAGE_HPP
#define PACKAGE_HPP

namespace caroline{

class package{
private:
  char* _name;
  char* _root;

  void mount(const char* _pkg_name);
public:
  package(const char* _pkg_name) noexcept;
  ~package() noexcept;
}; 

}

#endif
