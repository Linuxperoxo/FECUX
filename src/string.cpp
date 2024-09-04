//==========================================|
//   FILE: string.cpp                       |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstdarg>
#include <iostream>

#include "../include/string.hpp"
#include "../include/color.hpp"

/*
 
===========================================================|
CONSTRUCTOR
 
 */

fecux::utils::string::string() noexcept
  : _str(nullptr), 
    _str_size(0){}

fecux::utils::string::string(const char* _src_str) noexcept
  : _str(nullptr),
    _str_size(std::strlen(_src_str)){
  try{
    _alloc_str(_src_str, _str_size);
  }

  catch(std::bad_alloc& _runtime_error){
    std::cout << RED << "ERROR: " << NC << _runtime_error.what() << '\n';
    exit(EXIT_FAILURE);
  }
}

fecux::utils::string::string(fecux::utils::string& _src_str) noexcept 
  : _str(nullptr),
    _str_size(_src_str._str_size){
  try{
    _alloc_str(_src_str._str, _src_str._str_size);
  } 

  catch(std::bad_alloc& _runtime_error){
    std::cout << RED << "ERROR: " << NC << _runtime_error.what() << '\n';
    exit(EXIT_FAILURE);
  }
}

fecux::utils::string::string(string&& _src_str) noexcept
  : _str(nullptr),
    _str_size(_src_str._str_size){
  _src_str._str = nullptr;
  _src_str._str_size = 0;
}


/*

===========================================================|
DESTROYER

 */

fecux::utils::string::~string() noexcept{
  clean();
}

/*

============================================================|
OPERATORS

 */

/*
 
=============|
OPERATOR '=' |
=============|
 
 */

fecux::utils::string& fecux::utils::string::operator=(const char* _src_str) noexcept{
  try{
    _alloc_str(_src_str, std::strlen(_src_str));
  }

  catch(std::bad_alloc& _runtime_error){
    std::cout << RED << "ERROR: " << NC << _runtime_error.what() << '\n';
    exit(EXIT_FAILURE);
  }

  return *this;
}

fecux::utils::string& fecux::utils::string::operator=(fecux::utils::string& _src_str) noexcept{
  try{
    _alloc_str(_src_str._str, _src_str._str_size);
  } 

  catch(std::bad_alloc& _runtime_error){
    std::cout << RED << "ERROR: " << NC << _runtime_error.what() << '\n';
    exit(EXIT_FAILURE);
  }

  return *this;
}

fecux::utils::string& fecux::utils::string::operator=(fecux::utils::string&& _src_str) noexcept{
  if(&*_src_str._str == nullptr){
    return *this;
  }

  if(&*_str != nullptr){
    std::free(&*_str);
    _str = nullptr;
  }

  _str = &*_src_str._str;
  _str_size = _src_str._str_size;

  _src_str._str = nullptr;
  _src_str._str_size = 0;

  return *this;
}


/*
 
============================================================|
CLASS MEMBER FUNCTIONS 

*/

inline void fecux::utils::string::_alloc_str(const char* _src_str, const size_t& _src_str_size){
  char* _buffer_str = static_cast<char*>(std::malloc(_src_str_size + 1));
  
  if(_buffer_str == nullptr){
    throw std::bad_alloc();
  }

  if(&*_str != nullptr){
    std::free(&*_str);
    _str = nullptr;
  }

  std::memcpy(&*_buffer_str, &*_src_str, _src_str_size);
  
  _buffer_str[_str_size] = '\0';
  _str = _buffer_str;
}

