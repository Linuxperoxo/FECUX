/*

  COPYRIGHT: (c) 2024 per Linuxperoxo.
  AUTHOR: Linuxperoxo
  FILE: exception.hpp

*/

#ifndef __EXCEPTIONS_HPP__
#define __EXCEPTIONS_HPP__

#include "fecux_error_list.hpp"
#include "../utils/string.hpp"

namespace fecux{

class exception{
private:
  fecux::utils::string _what;
  uint8_t _error_code;

  exception() = delete;
public:  
  explicit exception(const uint8_t _error_code) noexcept;
  explicit exception(const exception&) noexcept;
  explicit exception(exception&&) noexcept;

  ~exception() noexcept = default;

  inline const char* what() const noexcept { return *_what; }
  inline uint8_t error_code() const noexcept { return _error_code; }
};

} // namespace fecux

#endif
