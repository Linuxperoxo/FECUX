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
#include <iostream>

#include "../include/utils/color.hpp"
#include "../include/caroline/package.hpp"
#include "../include/caroline/vars.hpp"
#include "../include/extra/caroexception.hpp"
#include "../include/utils/files.hpp"

caroline::package::package(const char* _pkg) noexcept
  : _pkg_name(nullptr), _pkg_version(nullptr), _pkg_url(nullptr), _pkg_desc(), _pkg_functions(nullptr), _array_size(0), _pkg_root(nullptr){ 
  try{
    mount(_pkg);
    loadVar(_pkg);
    loadFunctions(_pkg);
  }
  
  catch(caroline::caroex& _runtime_error){
    _runtime_error.all();
    this->~package();
    exit(_runtime_error.errorCode());
  }
}

caroline::package::~package() noexcept{
  std::vector<char**> _class_members = {&_pkg_name, &_pkg_version, &_pkg_url, &_pkg_desc, &_pkg_root};
  for(const auto& _member : _class_members){
    if(*_member != nullptr){
      std::free(*_member);
    }
  }

  if(_pkg_functions != nullptr && _array_size > 0){
    for(size_t i = 0; i < _array_size; i++){
      std::free(_pkg_functions[i]);
    }
  }
  std::free(_pkg_functions);
}

void caroline::package::mount(const char* _pkg){
  for(const auto& _tree : std::filesystem::directory_iterator(REPO_DIR)){
    std::string _buffer = _tree.path().string() + '/' + _pkg;
    if(std::filesystem::exists(_buffer) && std::filesystem::is_directory(_buffer)){
      _pkg_root = static_cast<char*>(malloc(std::strlen(_buffer.c_str()) + 1));
      if(_pkg_root == nullptr){
        throw caroline::caroex(MEMORY_ALLOCATION_ERROR);
      }
      std::strcpy(_pkg_root, _buffer.c_str());  
      return;
    }
  }
  std::free(_pkg_root);
  throw caroline::caroex(PACKAGE_NOT_FOUND, "none", "none", _pkg);
}

void caroline::package::loadVar(const char* _pkg){
  char* _full_locale = static_cast<char*>(malloc(std::strlen(_pkg_root) + 1 + std::strlen(INFO_FILE_NAME) + 1)); 
  void* _raw_libconfig = malloc(sizeof(libconfig::Config));
  
  if(_full_locale == nullptr || _raw_libconfig == nullptr){
    std::free(_full_locale);
    std::free(_raw_libconfig);
    throw caroline::caroex(MEMORY_ALLOCATION_ERROR, "none", "none", _pkg_name);
  }  

  std::strcpy(_full_locale, _pkg_root);
  std::strcat(_full_locale, "/");
  std::strcat(_full_locale, INFO_FILE_NAME);

  if(!files::is_file(_full_locale)){
    std::string _buffer(_full_locale);
    std::free(_raw_libconfig);
    std::free(_full_locale);
    throw caroline::caroex(INFO_FILE_NOT_FOUND, "none", _buffer.c_str(), _pkg_name);
  }

  libconfig::Config* _libconfig = new(_raw_libconfig) libconfig::Config();

  _libconfig->readFile(_full_locale);
  
  const char* _vars_file_name[4] = {"name", "version", "source_url", "desc"};
  char** _class_members_ptr[4] = {&_pkg_name, &_pkg_version, &_pkg_url, &_pkg_desc};

  std::string _buffer;

  for(size_t i = 0; i < sizeof(_vars_file_name) / sizeof(_vars_file_name[0]); i++){
    if(!_libconfig->lookupValue(_vars_file_name[i], _buffer) || _buffer.empty()){
      std::cerr << RED "VAR FAILED: ( " NC << _vars_file_name[i] << RED " )" NC << '\n';
      
      _libconfig->~Config();
      
      std::string _buffer(_full_locale);
      std::free(_raw_libconfig);
      std::free(_full_locale);
      throw caroline::caroex(INFO_VAR_FAILED, "none", _buffer.c_str(), _pkg);
    }

    *_class_members_ptr[i] = static_cast<char*>(malloc(_buffer.size() + 1));

    if(*_class_members_ptr[i] == nullptr){
      for(size_t k = 0; k < i; k++){
        std::free(*_class_members_ptr[k]);
      }
      _libconfig->~Config();
      
      std::free(_raw_libconfig);
      std::free(_full_locale);
      throw caroline::caroex(MEMORY_ALLOCATION_ERROR, "none", "none", _pkg);
    }
    std::strcpy(*_class_members_ptr[i], _buffer.c_str());
  }
  _libconfig->~Config();

  std::free(_raw_libconfig);
  std::free(_full_locale);
}

void caroline::package::loadFunctions(const char* _pkg){
  char* _full_locale = static_cast<char*>(malloc(std::strlen(_pkg_root) + 1 + std::strlen(BUILD_FILE_NAME) + 1));
  if(_full_locale == nullptr){
    throw caroline::caroex(MEMORY_ALLOCATION_ERROR, "none", "none", _pkg);
  }

  std::strcpy(_full_locale, _pkg_root);
  std::strcat(_full_locale, "/");
  std::strcat(_full_locale, BUILD_FILE_NAME);

  if(!files::is_file(_full_locale)){
    std::string _buffer(_full_locale);
    std::free(_full_locale);
    throw caroline::caroex(BUILD_FILE_NOT_FOUND, "none", _buffer.c_str(), _pkg);
  }

  const char* _possible_functions[] = {"pre_install", "install", "pos_install", "pre_build", "build", "pos_build"}; 
  _pkg_functions = static_cast<char**>(malloc(sizeof(char*) * 6));
  if(_pkg_functions == nullptr){
    std::string _buffer(_full_locale);
    std::free(_full_locale);
    throw caroline::caroex(MEMORY_ALLOCATION_ERROR, "none", "none", _buffer.c_str());
  }

  bool found = false;

  for(size_t i = 0; i < sizeof(_possible_functions) / sizeof(_possible_functions[0]); i++){
    std::string _command = "source " + std::string(_full_locale) + " && declare -f " + _possible_functions[i] + " &> /dev/null";
    if(system(_command.c_str()) == 0){
      _pkg_functions[_array_size] = static_cast<char*>(std::malloc(std::strlen(_possible_functions[i]) + 1));
      if(_pkg_functions[_array_size] == nullptr){
        std::free(_full_locale);
        throw caroline::caroex(MEMORY_ALLOCATION_ERROR, "none", "none", _pkg);
      }
      std::strcpy(_pkg_functions[_array_size], _possible_functions[i]);
      ++_array_size;
      found = true;
    }
  }

  if(!found){
    std::string _buffer(_full_locale);
    std::free(_full_locale);
    throw caroline::caroex(NONE_FUNCTIONS_FOUND, "none", _buffer.c_str(), _pkg);
  }
  std::free(_full_locale);
}

const char* caroline::package::name() const noexcept{
  return _pkg_name;
}

const char* caroline::package::version() const noexcept{
  return _pkg_version;
}

const char* caroline::package::url() const noexcept{
  return _pkg_url;
}

const char* caroline::package::desc() const noexcept{
  return _pkg_desc;
}

