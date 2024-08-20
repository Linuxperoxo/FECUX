//==========================================|
//   FILE: caroexceptio.cpp                 |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "../include/caroline/caroexception.hpp"
#include "../include/caroline/carolinevars.hpp"
#include "../include/utils/color.hpp"

#define MAX_SIZE 128

caroline::caroexception::caroexception(const unsigned int& _error_code, const char _what_array[], const char _file_array[]) noexcept
  : _what(nullptr), _file(nullptr), _error_code(_error_code){
  
  size_t length_what = std::strlen(_what_array) + 1;
  size_t length_file_OR_dir = std::strlen(_file_array) + 1;

  bool generic_what = false;

  if(std::strcmp(_what_array, "none") == 0){
    length_what = MAX_SIZE;
    generic_what = true;
  }

  if(std::strcmp(_file_array, "none") == 0){
    length_file_OR_dir = MAX_SIZE;
  }

  _what = static_cast<char*>(malloc(length_what));
  _file = static_cast<char*>(malloc(length_file_OR_dir));

  if(_what == nullptr || _file == nullptr){
    std::free(_what);
    std::free(_file);

    _what = nullptr;
    _file = nullptr;

    std::cerr << RED "CRITICAL ERROR: " NC "Memory allocation failed for exception class!!!\n";
    return;
  }

  std::strcpy(_what, _what_array);
  std::strcpy(_file, _file_array);

  if(generic_what){
    switch(_error_code){
      case MEMORY_ALLOCATION_ERROR:
        std::strcpy(_what, YELLOW "caroexception: " NC "Error when trying to allocate memory");
        break;
      case ATTEMPT_DEREFERENCE_NULLPTR:
        std::strcpy(_what, YELLOW "caroexception: " NC "Attempt to dereference a" GREEN " null pointer" NC);
        break;
      case ATTEMPT_MEMBER_NULLPTR:
        std::strcpy(_what, YELLOW "caroexception: " NC "Attempt to access a member of" GREEN " null pointer" NC);
        break;
      case CONFIG_FILE_NOT_FOUND:
        std::strcpy(_what, YELLOW "caroexception: " NC "Configuration file not found");
        std::strcpy(_file, CONFIG_FILE);
        break;
      case CONFIGURATION_VAR_FAILED:
        std::strcpy(_what, YELLOW "caroexception: " NC "Unable to load variable in configuration file");
        if(std::strcmp(_file, "none") == 0){
          std::strcpy(_file, CONFIG_FILE);
        }
        break;
      default:
        std::strcpy(_what, YELLOW "caroexception: " NC "An unknown error occurred");
        break;
    }
  }
}

void caroline::caroexception::getAll() const noexcept{
  std::cerr << RED "WHAT: ( " NC << _what << RED " )" NC << '\n';
  std::cerr << RED "FILE: ( " NC << _file << RED " )" NC << '\n';
  std::cerr << RED "CODE: ( " NC << _error_code << RED " )" NC <<'\n';
}

const char* caroline::caroexception::what() const noexcept{
  return _what;
}

const char* caroline::caroexception::getFile() const noexcept{
  return _file;
}

const unsigned int caroline::caroexception::getErrorCode() const noexcept{
  return _error_code;
}
