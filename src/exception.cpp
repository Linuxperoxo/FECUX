//==========================================|
//   FILE: exception.cpp                    |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <utility>

#include "../include/color.hpp"
#include "../include/exception.hpp"
#include "../include/fecux_vars.hpp"
#include "../include/string.hpp"

/*

===========================================================|
CONSTRUCTOR

 */

fecux::tools::runtime::exception::exception(
    const unsigned int &_error_code) noexcept
    : _what(), _error_code(_error_code) {
  switch (_error_code) {
  case CONFIG_FILE_NOT_FOUND:
    _what._cat_str("Configuration file was not found in -> ", RED, CONFIG_FILE,
                   NC);
    break;

  case MAIN_REPO_IS_EMPTY:
    _what._cat_str("Your current repository is empty, if you don't have any "
                   "custom repository you should use ",
                   GREEN, "fecux -s", NC, " to sync your local repository");
    break;

  case PKG_NOT_FOUND:
    _what._cat_str("Package not found in local repository");
    break;

  case NONE_MAIN_FUNCTIONS_FOUND:
    _what._cat_str(
        "The build file must have at least one of these functions -> [ ", RED,
        "install, build", NC, " ]");
    break;
  }
}

fecux::tools::runtime::exception::exception(exception &&_other) noexcept
    : _what(std::move(_other._what)), _error_code(_other._error_code) {
  _other._error_code = 0;
}

fecux::tools::runtime::exception::exception(
    fecux::utils::string &_what, const unsigned int &_error_code) noexcept
    : _what(_what), _error_code(_error_code) {}

/*

===========================================================|
GETS

 */

const char *fecux::tools::runtime::exception::what() const noexcept {
  return *_what;
}

unsigned int fecux::tools::runtime::exception::error_code() const noexcept {
  return _error_code;
}
