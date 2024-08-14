//==========================================|
//   FILE: exception.hpp                    |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <cstring>
#include <exception>

#define MEMORY_ALLOCATION_ERROR_CODE 23
#define CONFIGURATION_VAR_EMPTY 43
#define ATTEMPT_DEREFERENCE_NULLPTR 56
#define ATTEMPT_MEMBER_NULLPTR 67

class caroexception : public std::exception{
private:
  const char* excp_what;
  const char* excp_file;
  const char* excp_what_extra;
  const int excp_error_code;
public:
  explicit caroexception(const int& excp_error_code, const char* excp_file = "none", const char* excp_what_extra = "none") noexcept 
    : excp_error_code(excp_error_code), excp_file(excp_file), excp_what_extra(excp_what_extra){
    switch(excp_error_code){
      case MEMORY_ALLOCATION_ERROR_CODE:
        excp_what = "Error when trying to allocate memory";
        break;
      case CONFIGURATION_VAR_EMPTY:
        excp_what = "Configuration variable is empty. Check config file";
        break;
      case ATTEMPT_DEREFERENCE_NULLPTR:
        excp_what = "Attempt to dereference a null pointer";
        break;
      case ATTEMPT_MEMBER_NULLPTR:
        excp_what = "Attempt to access a member of null pointer";
        break;
    }
  }

  const char* what() const noexcept override{
    return excp_what; 
  }

  const char* what_extra() const noexcept{
    if(std::strcmp(excp_what_extra, "none") != 0){
      return excp_what_extra;
    }
    return "(non-extra)";
  }

  const int getErrorCode() const noexcept{
    return excp_error_code;
  } 

  const char* getFile() const noexcept{
    if(std::strcmp(excp_what, "none") != 0){
      return excp_file;
    }
    return "(non-file)";
  }
};

#endif
