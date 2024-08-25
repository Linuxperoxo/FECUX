//==========================================|
//   FILE: package.cpp                      |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <string>

#include "../include/caroline/package.hpp"
#include "../include/caroline/vars.hpp"
#include "../include/extra/caroexception.hpp"

caroline::package::package(const char* _pkg_name) noexcept
  : _name(nullptr), _root(nullptr){ 
  try{
    mount(_pkg_name);
  }
  
  catch(caroline::caroex& _runtime_error){
    _runtime_error.all();
    exit(_runtime_error.errorCode());
  }
}

caroline::package::~package() noexcept{
  std::free(_name);
  std::free(_root);
}

void caroline::package::mount(const char* _pkg_name){
  _name = static_cast<char*>(malloc(std::strlen(_pkg_name) + 1));

  if(_name == nullptr){
    throw caroline::caroex(MEMORY_ALLOCATION_ERROR);
  }

  for(const auto& _tree : std::filesystem::directory_iterator(REPO_DIR)){
    std::string _buffer = _tree.path().string() + '/';
    
    if(std::filesystem::exists(_buffer + _pkg_name) && std::filesystem::is_directory(_buffer + _pkg_name)){
      _root = static_cast<char*>(malloc(std::strlen(_buffer.c_str()) + 1));

      if(_root == nullptr){
        std::free(_name);

        _name = nullptr;

        throw caroline::caroex(MEMORY_ALLOCATION_ERROR);
      }
      std::strcpy(_root, _buffer.c_str());
      std::strcpy(_name, _pkg_name);
      
      return;
    }
  }
  std::free(_name);
  std::free(_root);

  _name = nullptr;
  _root = nullptr;

  throw caroline::caroex(PACKAGE_NOT_FOUND, "none", "none", _pkg_name);
}

