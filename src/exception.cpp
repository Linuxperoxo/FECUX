//==========================================|
//   FILE: exception.cpp                    |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include "../include/exception.hpp"
#include "../include/color.hpp"
#include "../include/fecux_vars.hpp"

/*
 
===========================================================|
CONSTRUCTOR
 
 */

fecux::tools::runtime::exception::exception(const unsigned int& _error_code) noexcept
  : _what(), 
    _error_code(_error_code){
  switch(_error_code){
    case CONFIG_FILE_NOT_FOUND:
      _what = "Configuration file was not found in -> ";
      _what._cat_str(RED, CONFIG_FILE, NC);
    break;
    
    case MAIN_REPO_IS_EMPTY:
      _what = "Your current repository is empty, if you don't have any custom repository you should use ";
      _what._cat_str(GREEN, "fecux -s", NC, " to sync your local repository");
    break;
  }
}

/*
 
===========================================================|
GETS
 
 */

const char* fecux::tools::runtime::exception::what() const noexcept{
  return *_what;
}

unsigned int fecux::tools::runtime::exception::error_code() const noexcept{
  return _error_code;
}
