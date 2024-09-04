#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

#include "string.hpp"

#define MEMORY_ALLOC_ERROR 101

namespace fecux{
  namespace tools{
    namespace runtime{
      class exception{
      private:
      fecux::utils::string _what;
      unsigned int _error_code;
      public:
        explicit exception(const unsigned int& _error_code) noexcept;
        explicit exception(fecux::utils::string& _what, const unsigned int& _error_code) noexcept;
        
        ~exception() noexcept = default;
        
        inline const char* what() const noexcept{
          return *_what;
        }
        
        inline unsigned int error_code() const noexcept{
          return _error_code;
        }
      };
    }    
  }
}

#endif
