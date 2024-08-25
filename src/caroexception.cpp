//==========================================|
//   FILE: caroexceptio.cpp                 |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstddef>
#include <cstring>
#include <iostream>
#include <vector>
#include <cstdlib>

#include "../include/extra/caroexception.hpp"
#include "../include/utils/color.hpp"
#include "../include/caroline/vars.hpp"

#define GENERIC_WHAT 128
#define GENERIC_FILE 64

caroline::caroexception::caroexception(const unsigned int& _error_code, const char* _what, const char* _file, const char* _pkg) noexcept
  : _exception_what(nullptr), _exception_file(nullptr), _exception_pkg(nullptr), _exception_error_code(_error_code){
  const size_t _what_len = (std::strcmp(_what, "none") == 0 ? GENERIC_WHAT : std::strlen(_what) + 1);
  const size_t _file_len = (std::strcmp(_file, "none") == 0 ? GENERIC_FILE : std::strlen(_file) + 1);
  const size_t _pkg_len = std::strlen(_pkg) + 1;

  const bool _generic = (std::strcmp(_what, "none") == 0 ? true : false);

  std::vector<char**> ptr = {&_exception_what, &_exception_file, &_exception_pkg};
  std::vector<const size_t*> size = {&_what_len, &_file_len, &_pkg_len};

  for(size_t i = 0; i < ptr.size(); i++){
    *ptr[i] = static_cast<char*>(malloc(*size[i]));
    if(*ptr[i] == nullptr){
      std::cerr << RED "CRITICAL ERROR: " NC "Memory allocation error for the " YELLOW "CAROEXCEPTION " NC "class\n";
      
      std::free(_exception_what);
      _exception_what = nullptr;
      
      std::free(_exception_file);
      _exception_file = nullptr;
      
      return;
    }
  }

  std::strcpy(_exception_what, _what);
  std::strcpy(_exception_file, _file);
  std::strcpy(_exception_pkg, _pkg);

  if(_generic){
    switch(_exception_error_code){
      case MEMORY_ALLOCATION_ERROR:
        std::strcpy(_exception_what, YELLOW "caroexception: " NC "Error when trying to allocate memory");
        break;

      case CONFIG_FILE_NOT_FOUND:
        std::strcpy(_exception_what, YELLOW "caroexception: " NC "Configuration file not found");
        std::strcpy(_exception_file, CONFIG_FILE);  
        break;

      case CONFIGURATION_VAR_FAILED:
        std::strcpy(_exception_what, YELLOW "caroexception: " NC "Unable to load variable in configuration file");
        if(std::strcmp(_file, "none") == 0){
          std::strcpy(_exception_file, CONFIG_FILE);
        }
        break;

      case REPO_DIR_NOT_EXIST:
        std::strcpy(_exception_what, YELLOW "caroexception: " NC "Local repository does not exist in your filesystem use " YELLOW "caro -s" NC);
        std::strcpy(_exception_file, REPO_DIR);
        break;

      case PACKAGE_NOT_FOUND:
        std::strcpy(_exception_what, YELLOW "caroexception: " NC "Specified package does not exist in the local repository or is stale");
        std::strcpy(_exception_file, REPO_DIR);
        std::strcpy(_exception_pkg, _pkg);
        break;
      
      case INFO_FILE_NOT_FOUND:
        std::strcpy(_exception_what, YELLOW "caroexception: " NC "Package info file not found, use " YELLOW "caro -s " NC "to synchronize local repository");
        std::strcpy(_exception_file, _file);
        break;

      case INFO_VAR_FAILED:
        std::strcpy(_exception_what, YELLOW "caroexception: " NC "Unable to load variable in infopkg file");
        std::strcpy(_exception_file, _file);
        break;
    }
  }
}

caroline::caroexception::~caroexception() noexcept{
  std::free(_exception_what);
  _exception_what = nullptr;

  std::free(_exception_file);
  _exception_file = nullptr;
}

void caroline::caroexception::all() const noexcept{
  std::cerr << RED "PKG FAILED: ( " NC << _exception_pkg << RED " )" NC << '\n';
  std::cerr << RED "WHAT: ( " NC << _exception_what << RED " )" NC << '\n';
  std::cerr << RED "FILE: ( " NC << _exception_file << RED " )" NC << '\n';
  std::cerr << RED "CODE: ( " NC << _exception_error_code << RED " )" NC <<'\n';
}

const char* caroline::caroexception::what() const noexcept{
  return _exception_what;
}

const char* caroline::caroexception::file() const noexcept{
  return _exception_file;
}

unsigned int caroline::caroexception::errorCode() const noexcept{
  return _exception_error_code;
}
