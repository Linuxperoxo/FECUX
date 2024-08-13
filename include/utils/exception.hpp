#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <cstdint>
#include <exception>

class caroexception : public std::exception{
private:
  const char* excp_what;
  const uint8_t excp_error_code; 
public:
  caroexception(const char* excp_what, const uint8_t& excp_error_code = 0);

  const char* what() const noexcept override; 
};

#endif
