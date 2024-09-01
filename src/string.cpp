//==========================================|
//   FILE: string.cpp                       |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstring>

#include "../include/utils/string.hpp"
#include "../include/fecux/exception.hpp"

/**
===========================================================|
CONSTRUCTOR
*/

fecux::utils::string::string() noexcept
  : _string_size(0), _string(nullptr){}

fecux::utils::string::string(const char* _new_string)
  : _string_size(std::strlen(_new_string)){
  init(_new_string);
}

fecux::utils::string::string(string& _other_string)
  : _string_size(_other_string._string_size){
  init(_other_string._string);
}

fecux::utils::string::string(string&& _other_string) noexcept
  : _string_size(_other_string._string_size),
    _string(&*_other_string._string){
  _other_string._string = nullptr;
  _other_string._string_size = 0x00;
}

/**
============================================================|
OPERATORS
*/

/**
=============|
OPERATOR '=' |
=============|
*/

fecux::utils::string& fecux::utils::string::operator=(const char* _str){
  push(_str);
  return *this;
} 

fecux::utils::string& fecux::utils::string::operator=(string& _other_string){
  if(&*this != &_other_string){
    push(_other_string._string);
  }
  return *this;
}

fecux::utils::string& fecux::utils::string::operator=(string&& _other_string){
  if(&*this != &_other_string){
    std::free(_string);
    _string = &*_other_string._string;
    _string_size = _other_string._string_size;
    _other_string._string = nullptr;
    _other_string._string_size = 0x00;
  }
  return *this;
}

/**
=============|
OPERATOR '+' |
=============|
*/

fecux::utils::string& fecux::utils::string::operator+(const char* _cat_string){
  cat(_cat_string);
  return *this;
}

fecux::utils::string& fecux::utils::string::operator+(string& _cat_string){
  cat(_cat_string._string);
  return *this;
}

/**
============================================================|
FUNCTIONS
*/

void fecux::utils::string::cat(const char* _str){
  const size_t _str_size = std::strlen(_str);
  char* _buffer = static_cast<char*>(std::malloc(_str_size + _string_size + 0x01));
  if(_buffer == nullptr){
    throw fecux::tools::exception(MEMORY_ALLOC_ERROR);
  }
  std::memcpy(&*_buffer, &*_string, _string_size);
  std::memcpy(&*_buffer + _string_size, &*_str, _str_size);
  _buffer[_string_size + _str_size] = 0x00;
  std::free(_string);
  _string = &*_buffer;
  _string_size += _str_size;
  _buffer = nullptr;
}

void fecux::utils::string::push(const char* _str){
  const size_t _new_string_size = std::strlen(_str);
  char* _buffer = static_cast<char*>(std::malloc(_new_string_size + 0x01));
  if(_buffer == nullptr){
    throw fecux::tools::exception(MEMORY_ALLOC_ERROR);
  }
  std::memcpy(&*_buffer, &*_str, _new_string_size);
  _buffer[_new_string_size] = 0x00;
  std::free(_string);
  _string = &*_buffer;
  _string_size = _new_string_size;
  _buffer = nullptr;  
}

void fecux::utils::string::init(const char* _str){
  _string = static_cast<char*>(std::malloc(_string_size + 0x01));
  if(_string == nullptr){
    throw fecux::tools::exception(MEMORY_ALLOC_ERROR);
  }
  std::memcpy(&*_string, &*_str, _string_size);
  _string[_string_size] = 0x00;
}

