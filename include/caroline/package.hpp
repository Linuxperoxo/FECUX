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
  char* _version;
  char* _source_url;
  char* _desc;

  char* _root;

  void mount(const char* _pkg_name);
  void loadVar();
public:
  package(const char* _pkg_name) noexcept;
  ~package() noexcept;
}; 

}

#endif
