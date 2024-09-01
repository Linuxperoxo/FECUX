//==========================================|
//   FILE: string.hpp                       |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <cstddef>
#include <cstring>
#include <cstdlib>

namespace fecux{
  namespace utils{
    class string{
    private:
      char* _string{nullptr};
      size_t _string_size{0};
      
      void cat(const char* _str);
      void push(const char* _str);
      void init(const char* _str);
    public:
      string() noexcept;
      string(const char* _new_string);
      string(string& _other_string);
      string(string&& _other_string) noexcept;
      
      inline ~string() noexcept{
        std::free(_string);
      }
      
      string& operator=(const char* _new_string);
      string& operator=(string& _other_string);
      string& operator=(string&& _other_string);       
      string& operator+(const char* _cat_string);
      string& operator+(string& _cat_string);
      
      inline const char* operator*() const noexcept{
        return _string;
      }  
       
      inline size_t len() const noexcept{
        return _string_size;
      }
    };
  }
}
#endif
