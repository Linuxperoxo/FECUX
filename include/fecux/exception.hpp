//==========================================|
//   FILE: exception.hpp                    |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include "../utils/string.hpp"

#define MEMORY_ALLOC_ERROR 101

namespace fecux{
  namespace tools{
    class exception{
    private:
      fecux::utils::string _what;
      fecux::utils::string _extra;
      unsigned int _error_code;
    public:
      inline explicit exception(const unsigned int& _error_code) noexcept
      : _error_code(_error_code){
        switch(_error_code){
          case MEMORY_ALLOC_ERROR:
            _what = "An error occurred while trying to allocate memory.";
          break;
        }
      }
        
      inline const char* what() const noexcept{
        return *_what;
      }
      
      inline const char* extra() const noexcept{
        return *_extra;
      }
      
      inline unsigned int error_code() const noexcept{
        return _error_code;
      }
    };
  }
}
