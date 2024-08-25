//==========================================|
//   FILE: caroexception.hpp                |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef CAROEXCEPTION 
#define CAROEXCEPTION

#include <exception>

#define MEMORY_ALLOCATION_ERROR 14
#define CONFIG_FILE_NOT_FOUND 15
#define CONFIGURATION_VAR_FAILED 16
#define REPO_DIR_NOT_EXIST 17
#define PACKAGE_NOT_FOUND 18
#define INFO_FILE_NOT_FOUND 19
#define INFO_VAR_FAILED 20

namespace caroline{

typedef class caroexception : public std::exception{
private:
  char* _exception_what;
  char* _exception_file;
  char* _exception_pkg;
  unsigned int _exception_error_code;
public:
  explicit caroexception(const unsigned int& _error_code, const char* _what = "none", const char* _file = "none", const char* _pkg = "none") noexcept;

  ~caroexception() noexcept;

  void all() const noexcept;

  const char* what() const noexcept override;
  const char* file() const noexcept;
  
  unsigned int errorCode() const noexcept;
}caroex;

}

#endif
