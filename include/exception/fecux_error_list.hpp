/*

  COPYRIGHT: (c) 2024 per Linuxperoxo.
  AUTHOR: Linuxperoxo
  FILE: fecux_error_list.hpp

*/

#ifndef __EXCEPTIONS_LIST_HPP__
#define __EXCEPTIONS_LIST_HPP__

#include <cstdint>

constexpr uint8_t NO_EXCEPTION{0};

constexpr uint8_t CONFIG_FILE_NOT_FOUND{101};
constexpr uint8_t CONFIG_OPTION_NOT_LOADDED{102};
constexpr uint8_t REPO_DIR_IS_EMPTY{103};
constexpr uint8_t PACKAGE_NOT_FOUND{104};

#endif
