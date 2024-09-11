//==========================================|
//   FILE: string.cpp                       |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstdarg>
#include <cstddef>
#include <iostream>
#include <new>

#include "../include/color.hpp"
#include "../include/string.hpp"

/*

===========================================================|
CONSTRUCTOR

 */

fecux::utils::string::string() noexcept : _str(nullptr), _str_size(0) {}

fecux::utils::string::string(const char *_src_str) noexcept
    : _str(nullptr), _str_size(std::strlen(_src_str)) {
  try {
    _mov_str(_src_str, _str_size);
  }

  catch (std::bad_alloc &_bad_alloc) {
    std::cout << RED << "CRITICAL ERROR: " << NC << "Memory alloc error "
              << _bad_alloc.what() << '\n';
    exit(EXIT_FAILURE);
  }
}

fecux::utils::string::string(const fecux::utils::string &_src_str) noexcept
    : _str(nullptr), _str_size(_src_str._str_size) {
  try {
    _mov_str(_src_str._str, _str_size);
  }

  catch (std::bad_alloc &_bad_alloc) {
    std::cout << RED << "CRITICAL ERROR: " << NC << "Memory alloc error "
              << _bad_alloc.what() << '\n';
    exit(EXIT_FAILURE);
  }
}

fecux::utils::string::string(string &&_src_str) noexcept
    : _str(_src_str._str), _str_size(_src_str._str_size) {
  _src_str._str = nullptr;
  _src_str._str_size = 0;
}

/*

===========================================================|
DESTROYER

 */

fecux::utils::string::~string() noexcept { std::free(_str); }

/*

============================================================|
OPERATORS

 */

/*

=============|
OPERATOR '=' |
=============|

 */

fecux::utils::string &
fecux::utils::string::operator=(const char *_src_str) noexcept {
  try {
    _mov_str(_src_str, std::strlen(_src_str));
  }

  catch (std::bad_alloc &_bad_alloc) {
    std::cout << RED << "CRITICAL ERROR: " << NC << "Memory alloc error "
              << _bad_alloc.what() << '\n';
    exit(EXIT_FAILURE);
  }

  return *this;
}

fecux::utils::string &
fecux::utils::string::operator=(const fecux::utils::string &_src_str) noexcept {
  try {
    _mov_str(_src_str._str, _src_str._str_size);
  }

  catch (std::bad_alloc &_bad_alloc) {
    std::cout << RED << "CRITICAL ERROR: " << NC << "Memory alloc error "
              << _bad_alloc.what() << '\n';
    exit(EXIT_FAILURE);
  }

  return *this;
}

fecux::utils::string &
fecux::utils::string::operator=(fecux::utils::string &&_src_str) noexcept {
  if (&*_src_str._str == nullptr) {
    return *this;
  }

  if (&*_str != nullptr) {
    std::free(&*_str);
    _str = nullptr;
  }

  _str = &*_src_str._str;
  _str_size = _src_str._str_size;

  _src_str._str = nullptr;
  _src_str._str_size = 0;

  return *this;
}

/*

=============|
OPERATOR '*' |
=============|

 */

const char *fecux::utils::string::operator*() const noexcept { return &*_str; }

/*

============================================================|
CLASS MEMBER FUNCTIONS

*/

void fecux::utils::string::_mov_str(const char *_src_str,
                                    const size_t &_src_str_size) {
  char *_buffer_str = static_cast<char *>(std::malloc(_src_str_size + 1));

  if (_buffer_str == nullptr) {
    throw std::bad_alloc();
  }

  std::memcpy(_buffer_str, _src_str, _src_str_size);

  if (_str != nullptr) {
    std::free(_str);
    _str = nullptr;
  }

  _buffer_str[_src_str_size] = '\0';
  _str = _buffer_str;
  _str_size = _src_str_size;
}

void fecux::utils::string::clean() noexcept {
  if (_str != nullptr) {
    std::free(_str);
    _str = nullptr;
    _mov_str("", 0);
  }
}

/*

===========================================================|
GETS

 */

size_t fecux::utils::string::len() const noexcept { return _str_size; }
