//==========================================|
//   FILE: check.cpp                        |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <filesystem>

#include "../include/utils/check.hpp"

bool check::is_dir(const char* _dir){
  return std::filesystem::exists(_dir) && std::filesystem::is_directory(_dir);
}

bool check::is_file(const char* _file){
  return std::filesystem::exists(_file) && std::filesystem::is_regular_file(_file);
}
