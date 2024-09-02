//==========================================|
//   FILE: exception.hpp                    |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include "../utils/string.hpp"
#include "../utils/color.hpp"
#include "../fecux/vars.hpp"

#define MEMORY_ALLOC_ERROR 101
#define CONFIG_FILE_NOT_FOUND 102
#define FAILED_LOAD_OPTION 103

namespace fecux{
  namespace tools{
    class exception{
    private:
      fecux::utils::string _what;
      unsigned int _error_code;
    public:
      inline explicit exception(const unsigned int& _error_code) noexcept
      : _error_code(_error_code){
        switch(_error_code){
          case MEMORY_ALLOC_ERROR:
            _what = "An error occurred while trying to allocate memory.";
          break;
          
          case CONFIG_FILE_NOT_FOUND:
            _what = "Configuration file not found! Check -> ";
            _what = _what + RED + CONFIG_FILE + NC;
          break;
        }
      }
      
      inline explicit exception(fecux::utils::string& _what, const unsigned int& _error_code) noexcept
        : _what(_what), _error_code(_error_code){
        
      }
        
      inline const char* what() const noexcept{
        return *_what;
      }
      
      inline unsigned int error_code() const noexcept{
        return _error_code;
      }
    };
  }
}
