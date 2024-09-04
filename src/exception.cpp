#include "../include/exception.hpp"

fecux::tools::runtime::exception::exception(const unsigned int& _error_code) noexcept
  : _what(), 
    _error_code(_error_code){
  switch(_error_code){
    case MEMORY_ALLOC_ERROR:
      _what = "There was a problem with memory allocation somewhere in the code";
    break;
  }
}

fecux::tools::runtime::exception::exception(fecux::utils::string& _what, const unsigned int& _error_code) noexcept
  : _what(_what), _error_code(_error_code){}
