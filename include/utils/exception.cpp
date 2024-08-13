#include "exception.hpp"
#include "smartpointer.hpp"

caroexception::caroexception(const char* excp_what, const uint8_t& excp_error_code) : excp_error_code(excp_error_code){
  smt_ptr<char> desc(sizeof(excp_what), nullptr);
}

const char* caroexception::what() const noexcept{
  return excp_what;
}
