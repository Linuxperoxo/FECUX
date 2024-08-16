#ifndef CAROEXCEPTION_HPP
#define CAROEXCEPTION_HPP

#define MEMORY_ALLOCATION_ERROR 23
#define CONFIGURATION_VAR_EMPTY 43
#define FILE_NOT_FOUND 55
#define ATTEMPT_DEREFERENCE_NULLPTR 56
#define ATTEMPT_MEMBER_NULLPTR 67

#include <exception>
#include <string>

class caroexception : public std::exception{
private:
  std::string _excep_what;
  std::string _excep_file;
  int _excep_error_code;
public:
  caroexception(const int& _error_code, const std::string _what = "none", const std::string _file = "none") noexcept;

  void getAll() const noexcept;

  const char* what() const noexcept;
  const char* getFile() const noexcept;
  const int getErrorCode() const noexcept;
};

#endif
