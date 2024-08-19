#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "../include/utils/caroexception.hpp"
#include "../include/caroline/const.hpp"
#include "../include/utils/color.hpp"

#define MAX_SIZE 256

caroline::caroexception::caroexception(const int& _error_code, const char _what[], const char _file_OR_dir[]) noexcept
  : _exception_what(nullptr), _exception_file(nullptr), _exception_error_code(_error_code){
  
  size_t length_what = std::strlen(_what) + 1;
  size_t length_file_OR_dir = std::strlen(_file_OR_dir) + 1;

  if(std::strcmp(_what, "none") == 0){
    length_what = MAX_SIZE;
  }

  if(std::strcmp(_file_OR_dir, "none") == 0){
    length_file_OR_dir = MAX_SIZE;
  }


  _exception_what = static_cast<char*>(malloc(length_what));
  _exception_file = static_cast<char*>(malloc(length_file_OR_dir));
  
  if(_exception_what == nullptr || _exception_file == nullptr){
    std::free(_exception_what);
    _exception_what = nullptr;

    std::free(_exception_file);
    _exception_file = nullptr;

    std::cerr << RED "CRITICAL ERROR: " NC "Memory allocation failed for exception class!!!\n";
    return;
  }
  
  std::strcpy(_exception_what, _what);
  std::strcpy(_exception_file, _file_OR_dir);
  
  if(std::strcmp(_exception_what, "none") == 0){
    switch(_error_code){
      case MEMORY_ALLOCATION_ERROR:
        std::strcpy(_exception_what, "caroexception: Error when trying to allocate memory");
        break;
      case ATTEMPT_DEREFERENCE_NULLPTR:
        std::strcpy(_exception_what, YELLOW "caroexception: " NC "Attempt to dereference a" GREEN " null pointer" NC);
        break;
      case ATTEMPT_MEMBER_NULLPTR:
        std::strcpy(_exception_what, YELLOW "caroexception: " NC "Attempt to access a member of" GREEN " null pointer" NC);
        break;
      case CONFIG_FILE_NOT_FOUND:
        std::strcpy(_exception_what, YELLOW "caroexception: " NC "Configuration file not found");
        std::strcpy(_exception_file, CONFIG_FILE);
        break;
      case CONFIGURATION_VAR_FAILED:
        std::strcpy(_exception_what, YELLOW "caroexception: " NC "Unable to load variable in configuration file");
        if(std::strcmp(_exception_file, "none") == 0){
          std::strcpy(_exception_file, CONFIG_FILE);
        } else {
          std::strcpy(_exception_file, _file_OR_dir);
        }
        break;
      default:
        std::strcpy(_exception_what, YELLOW "caroexception: " NC "An unknown error occurred");
        break;
    }
  }
}

void caroline::caroexception::getAll() const noexcept{
  std::cerr << "ERROR = {\n";
  std::cerr << "  WHAT: " << _exception_what << '\n';
  std::cerr << "  FILE: " << _exception_file << '\n';
  std::cerr << "  CODE: " << _exception_error_code << '\n';
  std::cerr << "}\n";
}

const char* caroline::caroexception::what() const noexcept{
  return _exception_what;
}

const char* caroline::caroexception::getFile() const noexcept{
  return _exception_file;
}

const int caroline::caroexception::getErrorCode() const noexcept{
  return _exception_error_code;
}
