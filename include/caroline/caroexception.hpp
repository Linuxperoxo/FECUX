//==========================================|
//   FILE: caroexception.hpp                |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef CAROEXCEPTION_HPP
#define CAROEXCEPTION_HPP

#include <exception>

namespace caroline{

#define MEMORY_ALLOCATION_ERROR 10
#define ATTEMPT_DEREFERENCE_NULLPTR 13
#define ATTEMPT_MEMBER_NULLPTR 14
#define CONFIG_FILE_NOT_FOUND 15
#define CONFIGURATION_VAR_FAILED 16

class caroexception : public std::exception{
private:
  char* _what;
  char* _file;
  unsigned int _error_code;
public:
  explicit caroexception(const unsigned int& _error_code, const char _what_array[] = "none", const char _file_array[] = "none") noexcept;

  void getAll() const noexcept;

  const char* what() const noexcept override;
  const char* getFile() const noexcept;
  const unsigned int getErrorCode() const noexcept;
};

}
#endif
