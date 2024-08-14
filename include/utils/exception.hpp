#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <cstdint>
#include <exception>

#define MEMORY_ALLOCATION_ERROR_CODE 23
#define ATTEMPT_DEREFERENCE_NULLPTR 56

class caroexception : public std::exception{
private:
  const char* excp_what;
  const uint8_t excp_error_code; 
public:
  explicit caroexception(const char* excp_what, const uint8_t& excp_error_code = 0) noexcept 
    : excp_what(excp_what), excp_error_code(excp_error_code){

  }

  const char* what() const noexcept override{
    return excp_what; 
  } 
};

#endif
