/*

  COPYRIGHT: (c) 2024 per Linuxperoxo.
  AUTHOR: Linuxperoxo

*/

#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <new>

namespace fecux {
namespace utils {

class string {
private:
  char *_begin_block{nullptr};
  std::size_t _string_len{0};

  void cpy_string(const char *_string);

public:
  string() noexcept;
  string(const char *_string);
  string(const string &_string_class);
  string(string &&_string_class) noexcept;

  string &operator=(const char *_string);
  string &operator=(const string &_string_class);
  string &operator=(string &&_string_class);

  template <typename... Args> inline void cat_str(Args &&...args) {
    const char *const _str_to_cat[]{args...};
    std::size_t _str_len_each[]{std::strlen(args)...};
    std::size_t _full_string_len{_string_len};

    for (const auto &_str_len : _str_len_each) {
      _full_string_len += _str_len;
    }

    char *_buffer{static_cast<char *>(std::malloc(_full_string_len + 1))};

    if (_buffer == nullptr) {
      throw std::bad_alloc();
    }

    size_t _coppied{0};

    if (_begin_block != nullptr || _string_len > 0) {
      std::memcpy(_buffer, _begin_block, _string_len);
      _coppied = _string_len;
    }

    for (std::size_t i = 0; i < sizeof(_str_to_cat) / sizeof(_str_to_cat[0]);
         i++) {
      std::memcpy(_buffer + _coppied, _str_to_cat[i], _str_len_each[i]);
      _coppied += _str_len_each[i];
    }

    std::free(_begin_block);

    _begin_block = _buffer;
    _begin_block[_full_string_len] = '\0';

    _string_len = _full_string_len;
  }

  inline const char *operator*() noexcept { return _begin_block; }
  inline std::size_t str_len() noexcept { return _string_len; }
};

} // namespace utils
} // namespace fecux

#endif
