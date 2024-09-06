//==========================================|
//   FILE: files_utils.cpp                  |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <filesystem>

#include "../include/files_utils.hpp"


/*
 
===========================================================|
CLASS MEMBER FUNCTIONS
 
 */

bool fecux::tools::runtime::filesUtils::is_file(const char* _file) noexcept{
  return std::filesystem::exists(_file) && std::filesystem::is_regular_file(_file);
}

bool fecux::tools::runtime::filesUtils::is_dir(const char* _dir) noexcept{
  return std::filesystem::exists(_dir) && std::filesystem::is_directory(_dir);
}

bool fecux::tools::runtime::filesUtils::is_empty(const char* _dir) noexcept{
  if(is_dir(_dir)) return std::filesystem::is_empty(_dir);
  return false;
}

void fecux::tools::runtime::filesUtils::create_dirs(const char *_dir) noexcept{
  if(is_dir(_dir)) return;
  std::filesystem::create_directories(_dir);
}

