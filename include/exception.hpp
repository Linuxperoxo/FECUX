//==========================================|
//   FILE: exception.cpp                    |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

#include "string.hpp"

#define CONFIG_FILE_NOT_FOUND 101
#define FAILED_TO_LOAD_OPT 102
#define MAIN_REPO_IS_EMPTY 103
#define PKG_NOT_FOUND 104
#define INFOPKG_FILE_NOT_FOUND 105
#define FAILED_TO_LOAD_VAR 106

namespace fecux{
  namespace tools{
    namespace runtime{
      class exception{
      private:
        fecux::utils::string _what;
        unsigned int _error_code;
        
        exception(const exception&)            = delete;
        exception& operator=(const exception&) = delete;
        exception& operator=(exception&&)      = delete;
      public:
        explicit exception(const unsigned int& _error_code) noexcept;
        explicit exception(exception&& _other) noexcept;
        explicit exception(fecux::utils::string& _what, const unsigned int& _error_code) noexcept;   
        
        ~exception() noexcept = default;
        
        const char* what() const noexcept; 
        unsigned int error_code() const noexcept;
      };
    }    
  }
}

#endif
