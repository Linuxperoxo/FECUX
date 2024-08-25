//==========================================|
//   FILE: package.cpp                      |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <string>
#include <libconfig.h++>
#include <vector>

#include "../include/caroline/package.hpp"
#include "../include/caroline/vars.hpp"
#include "../include/extra/caroexception.hpp"
#include "../include/utils/files.hpp"

caroline::package::package(const char* _pkg_name) noexcept
  : _name(nullptr), _root(nullptr){ 
  try{
    mount(_pkg_name);
    loadVar();
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
    std::string _buffer = _tree.path().string() + '/' + _pkg_name;
    
    if(std::filesystem::exists(_buffer) && std::filesystem::is_directory(_buffer)){
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

void caroline::package::loadVar(){
  char* _full_locale = static_cast<char*>(malloc(std::strlen(_root) + 1 + std::strlen(INFO_FILE_NAME) + 1)); 
  void* _raw_libconfig = malloc(sizeof(libconfig::Config));
  
  if(_full_locale == nullptr || _raw_libconfig == nullptr){
    throw caroline::caroex(MEMORY_ALLOCATION_ERROR);
  }  

  std::strcpy(_full_locale, _root);
  std::strcat(_full_locale, "/");
  std::strcat(_full_locale, INFO_FILE_NAME);

  if(!files::is_file(_full_locale)){
    std::string _buffer = _full_locale;

    std::free(_raw_libconfig);
    std::free(_full_locale);

    throw caroline::caroex(INFO_FILE_NOT_FOUND, "none", _buffer.c_str());
  }

  libconfig::Config* _libconfig = new(_raw_libconfig) libconfig::Config();

  _libconfig->readFile(_full_locale);
  
  std::vector<const char*> _name = {"version", "source_url", "desc"};
  std::vector<char**> _ptr = {&_version, &_source_url, &_desc};

  std::string _buffer;

  for(size_t i = 0; i < _name.size(); i++){
    if(!_libconfig->lookupValue(_name[i], _buffer) || _buffer.empty()){
      _libconfig->~Config();

      std::free(_raw_libconfig);
      std::free(_full_locale);

      throw caroline::caroexception(INFO_VAR_FAILED);
    }

    *_ptr[i] = static_cast<char*>(malloc(_buffer.size() + 1));

    if(*_ptr[i] == nullptr){
      for(size_t k = 0; k < i; k++){
        std::free(*_ptr[k]);
      }
      _libconfig->~Config();

      std::free(_raw_libconfig);
      std::free(_full_locale);

      throw caroline::caroex(MEMORY_ALLOCATION_ERROR);
    }
    std::strcpy(*_ptr[i], _buffer.c_str());
  }
  _libconfig->~Config();

  std::free(_raw_libconfig);
  std::free(_full_locale);
}

