/*

  COPYRIGHT: (c) 2024 per Linuxperoxo.
  AUTHOR: Linuxperoxo
  FILE: string.hpp

*/

#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <cstddef>
#include <new>
#include <cstring>
#include <cstdlib>

namespace fecux{
namespace utils{

class string{
private:
  char* _string;
  std::size_t _string_len;

  void cpy_string(const char* _src_str);

public:
  string() noexcept;
  string(const char* _src_str);
  string(const string& _str_class);
  string(string&& _str_class) noexcept;

  inline ~string() noexcept{
    std::free(_string);
  }

  string& operator=(const char* _src_str);
  string& operator=(const string& _str_class);
  string& operator=(string&& _str_class) noexcept;

  template<typename... strings_to_cat>
  const char* cat_str(strings_to_cat&&... _str_to_cat){
    const char* _strs[]{_str_to_cat...};
    std::size_t _strs_len[]{std::strlen(_str_to_cat)...};
    std::size_t _full_len{_string_len};

    for(std::size_t i = 0; i < sizeof(_strs_len) / sizeof(_strs_len[0]); i++){
      _full_len += _strs_len[i];
    }

    char* _buffer{
      static_cast<char*>(std::malloc(_full_len + 1))
    };

    if(_buffer == nullptr){
      throw std::bad_alloc();
    }

    std::size_t _bytes_coppied{0};

    if(_string != nullptr){
      std::memcpy(_buffer, _string, _string_len);
      _bytes_coppied += _string_len;
    }

    for(std::size_t i = 0; i < sizeof(_strs_len) / sizeof(_strs_len[0]); i++){
      std::memcpy(_buffer + _bytes_coppied, _strs[i], _strs_len[i]);
      _bytes_coppied += _strs_len[i];
    }
    std::free(_string);
    
    _buffer[_full_len] = '\0';
    
    _string = _buffer;
    _string_len = _full_len;

    return _string;
  }

  inline const char* operator*() const noexcept { return _string; }
  inline std::size_t len() const noexcept { return _string_len; }
};

} // namespace utils
} // namespace fecux

#endif
