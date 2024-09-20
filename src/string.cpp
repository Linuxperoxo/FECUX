

#include "../include/utils/string.hpp"

/* <=====================================================================> */

/* CONSTRUCTOR */

fecux::utils::string::string() noexcept {}

fecux::utils::string::string(const char *_string)
    : _string_len(std::strlen(_string)) {
  cpy_string(_string);
}

fecux::utils::string::string(const string &_string_class)
    : _string_len(_string_class._string_len) {
  cpy_string(_string_class._begin_block);
}

fecux::utils::string::string(string &&_string_class) noexcept
    : _string_len(_string_class._string_len),
      _begin_block(_string_class._begin_block) {
  _string_class._begin_block = nullptr;
  _string_class._string_len = 0;
}

/* <=================================================================> */

/* OPERATOR '=' */

fecux::utils::string &fecux::utils::string::operator=(const char *_string) {
  _string_len = std::strlen(_string);
  cpy_string(_string);

  return *this;
}

fecux::utils::string &
fecux::utils::string::operator=(const fecux::utils::string &_string_class) {
  _string_len = _string_class._string_len;
  cpy_string(_string_class._begin_block);

  return *this;
}

fecux::utils::string &fecux::utils::string::operator=(string &&_string_class) {
  if (this != &_string_class) {
    _string_len = _string_class._string_len;
    _begin_block = _string_class._begin_block;

    _string_class._string_len = 0;
    _string_class._begin_block = nullptr;
  }
  return *this;
}

/* <=================================================================> */

/* FUNCTIONS MEMBER */

void fecux::utils::string::cpy_string(const char *_string) {
  _begin_block = static_cast<char *>(std::malloc(_string_len + 1));
  if (_begin_block == nullptr) {
    throw std::bad_alloc();
  }
  std::memcpy(_begin_block, _string, _string_len);
  _begin_block[_string_len] = '\0';
}
