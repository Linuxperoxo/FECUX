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

namespace fecux{
  namespace tools{
    namespace runtime{
      class exception{
      private:
        fecux::utils::string _what;
        unsigned int _error_code;
        
        exception(const exception&) = delete;
        exception(const exception&&) = delete;
        exception& operator=(const exception&) = delete;
        exception& operator=(const exception&&) = delete;
      public:
        explicit exception(const unsigned int& _error_code) noexcept;
        
        inline explicit exception(fecux::utils::string& _what, const unsigned int& _error_code) noexcept
          : _what(_what),
            _error_code(_error_code){
          }
        
        ~exception() noexcept = default;
        
        const char* what() const noexcept;
        
        unsigned int error_code() const noexcept;
      };
    }    
  }
}

#endif
