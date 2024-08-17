//==========================================|
//   FILE: caroexception.cpp                |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstring>
#include <iostream>

#include "../include/caroline/const_var.hpp"
#include "../include/utils/caroexception.hpp"
#include "../include/utils/color.hpp"

caroexception::caroexception(const int& _error_code, const std::string _what, const std::string _file) noexcept
  : _excep_what(_what), _excep_file(_file), _excep_error_code(_error_code){
  if(_what == "none"){
    switch(_error_code){
      case MEMORY_ALLOCATION_ERROR:
        _excep_what = "Error when trying to allocate memory";
        break;
      case CONFIGURATION_VAR_EMPTY:
        _excep_what = "Configuration variable is empty. Check config file!";
        _excep_file = (_file == "none" ? CONFIG_FILE_LOC : _file);
        break;
      case FILE_NOT_FOUND:
        _excep_what = "Specified file" GREEN " was not found" NC " in the file system";
        break;
      case ATTEMPT_DEREFERENCE_NULLPTR:
        _excep_what = "Attempt to dereference a" GREEN " null pointer" NC;
        break;
      case ATTEMPT_MEMBER_NULLPTR:
        _excep_what = "Attempt to access a member of" GREEN " null pointer" NC;
        break;
      case ALLOCATION_SIZE_TOO_SMALL:
        _excep_what = "Allocation size" GREEN " too small" NC;
        break;
      case REPO_DIR_NOT_FOUND:
        _excep_what = "the repository directory" GREEN " does not exist." NC " Use" GREEN " caro --sync" NC;
        _excep_file = (_file == "none" ? REPO_DIR : _file);
        break;
      case FAILED_TO_CREATE_DIR:
        _excep_what = "An error occurred when trying to create a directory";
        break;
    }
  }  
}

void caroexception::getAll() const noexcept{
  std::cerr << "ERROR_INFOS = {\n";
  std::cerr << RED "  _excep_what: " NC << _excep_what << '\n';
  std::cerr << RED "  _excep_error_code: " NC << _excep_error_code << '\n';
  std::cerr << RED "  _excep_file: " NC << _excep_file << '\n';
  std::cerr << "}\n";
}

const char* caroexception::what() const noexcept{
  return _excep_what.c_str();
}

const char* caroexception::getFile() const noexcept{
  return _excep_file.c_str();
}

const int caroexception::getErrorCode() const noexcept{
  return _excep_error_code;
} 
