//==========================================|
//   FILE: string.hpp                       |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <cstddef>
#include <cstdlib>
#include <cstring>

namespace fecux{
  namespace utils{
    class string{
    private:
      char* _str;
      size_t _str_size;
      
      void _alloc_str(const char* _src_str, const size_t& _src_str_size);
    public:
      string(const char* _src_str) noexcept;
      string(string& _src_str) noexcept;
      string(string&& _src_str) noexcept;
      
      ~string() noexcept;
      
      string& operator=(const char* _src_str) noexcept;
      string& operator=(string& _src_str) noexcept;
      string& operator=(string&& _src_str) noexcept;
      
      inline const char* operator*() noexcept{
        return &*_str;
      }
      
      inline size_t len() noexcept{
        return _str_size;
      }
      
      inline void clean() noexcept{
        std::free(&*_str);
        _str_size = 0;
      }
      
      template <typename... Args>
      const char* _cat_str(Args... args){
        if(*&_str == nullptr){
          return nullptr;
        }
        
        const char* _args_str[] = {(args)...};
        const size_t _args_size[] = {std::strlen(args)...};
        size_t _full_size = _str_size;
        
        for(const auto& _arg_size : _args_size){
          _full_size += _arg_size;
        }
          
        char* _buffer = static_cast<char*>(std::malloc(_full_size + 1));
          
        if(_buffer == nullptr){
          /* Error memory alloc */
        }
        
        std::memcpy(&*_buffer, &*_str, _str_size);
        
        int i = 0;
        size_t _alloced = _str_size;  
        
        for(const auto& _arg_str : _args_str){
          std::memcpy(&*_buffer + _alloced, &*_arg_str, std::strlen(_arg_str));
          _alloced += _args_size[i];
          ++i;
        }  
        
        _buffer[_full_size] = '\0';
        
        std::free(&*_str);
        
        _str = &*_buffer;
        _str_size = _full_size; 
         
        return _str;
      }
    };
  }
}

#endif
