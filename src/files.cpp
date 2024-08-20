//==========================================|
//   FILE: files.cpp                        |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <filesystem>
#include <fstream>

#include "../include/tools/files.hpp"

bool files::is_dir(const char* _dir) noexcept{
  return std::filesystem::exists(_dir) && std::filesystem::is_directory(_dir);
}

bool files::is_file(const char* _file) noexcept{
  return std::filesystem::exists(_file) && std::filesystem::is_regular_file(_file);
}

bool files::create_dir(const char* _dir) noexcept{
  std::filesystem::create_directories(_dir);
  if(files::is_dir(_dir)){
    return true;
  }
  return false;
}

bool files::create_file(const char* _file) noexcept{
  std::ofstream _new_file(_file);
  if(_new_file){
    return true;
  }
  return false;
}
