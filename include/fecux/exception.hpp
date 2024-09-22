/*

  COPYRIGHT: (c) 2024 per Linuxperoxo.
  AUTHOR: Linuxperoxo
  FILE: exception.hpp

*/

#ifndef __EXECEPTION_HPP__
#define __EXECEPTION_HPP__

#include <cstdint>

#include "../utils/string.hpp"

#define CONFIG_FILE_NOT_FOUND 101
#define OPTIONS_NOT_LOADDED 102
#define REPO_DIR_IS_EMPTY 103
#define PKG_NOT_FOUND 104

namespace fecux{
namespace main{

class exception{
private:
  fecux::utils::string _what;
  uint16_t _error_code;
  
  exception(const exception&) = delete;
  exception& operator=(const exception&) = delete;
  exception& operator=(exception&&) = delete;
public:
  explicit exception(const uint16_t _error_code) noexcept;
  explicit exception(fecux::utils::string& _what, const uint16_t _error_code) noexcept;
  explicit exception(fecux::main::exception&& _exception_class) noexcept;
 
  const char* what() noexcept;
  uint16_t error_code() const noexcept;
};

} // namespace main
} // namespace fecux

#endif
