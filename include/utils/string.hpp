/*

  COPYRIGHT: (c) 2024 per Linuxperoxo.
  AUTHOR: Linuxperoxo
  FILE: string.hpp

*/

#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <new>

namespace fecux{
namespace utils{

class string{
private:
  char* _string;
  std::size_t _string_len;

  void cpy_str(const char*, const std::size_t);
public:
  string() noexcept;
  
  string(const char* _src);
  string(const string&);
  string(string&&) noexcept;
  
  string& operator=(const char* _src);
  string& operator=(const string&);
  string& operator=(string&&) noexcept;
  


  /*
  
    Essa função é uma função para concatenar strings, ela tem um lista de parámetro,
    que obrigatoriamente tem que receber apenas c_str. Fiz essa função pois sentia 
    uma dificuldade em concatenar strings na lib cstring, a função std::strcat so consegue 
    concatenar 1 string por vez

    EX: std::string(MyString, "Hello,");
        std::string(MyString, " World!");
    
    Isso para uma grande quantidade de strings fica muito chato de fazer, então fiz esse
    para facilitar :)

    Ela não é uma implementação perfeita, mas funciona bem

  */



  template <typename ... strs>
  inline const char* cat_str(strs&&... _strs){
    const char* _strs_array[]{_strs...};
    const std::size_t _strs_len[]{std::strlen(_strs)...};
    std::size_t _full_size{_strs_len};

    for(const auto& _len : _strs_len){
      _full_size += _len;
    }

    char* _buffer{
      static_cast<char*>(std::malloc(_full_size + 1))
    };

    if(_buffer == nullptr){
      throw std::bad_alloc();
    }

    std::size_t _cpy_bytes{_string_len};

    if(_cpy_bytes > 0){
      std::memcpy(_buffer, _string, _string_len);
    }

    for(std::size_t i{0}; i < sizeof(_strs_array) / sizeof(_strs_array[0]); i++){
      std::memcpy(_buffer + _cpy_bytes, _strs_array[i], _strs_len[i]);
      _cpy_bytes += _strs_len[i];
    }
    _buffer[_full_size] = '\0';
    std::free(_string);
    _string = _buffer;

    return _string;
  }



  /*
  
    Aqui fiz algumas sobrecargas de operador que são úteis  

    Deixei todas como inline pq são códigos que possivelmente pode haver repetições, e são bem pequenas
  
  */



  inline const char* operator*() const noexcept { if(_string != nullptr) { return _string; } return ""; }

  inline bool operator==(const char* _src) const noexcept { return std::strcmp(_string, _src) == 0 ? true : false; }
  inline bool operator==(const string& _src) const noexcept { return std::strcmp(_string, _src._string) == 0 ? true : false; }

  inline uint16_t len() const noexcept { return _string_len; }
  


  /*
  
    Essa função não pode não ser tão útil, mas nunca de sabe quando você quer saber onde a string está na memória

    Ela pode ser substituida pela sobrecarga do operator '*', porém se vc quiser ver no std::cout usando o operador '*'
    você vai ter que usar static_cast<void*>(*_MyString), já essa ai você não vai precisar, mas ainda continua não sendo 
    muito útil

  */



  inline void* str_addrs() const noexcept { return _string; }
};

} // namespace utils
} // namespace fecux

#endif
