/*

  COPYRIGHT: (c) 2024 per Linuxperoxo.
  AUTHOR: Linuxperoxo
  FILES: files.cpp

*/

#include <filesystem>

#include "../include/utils/files.hpp"

/*
  
  Esse arquivo é bem autoexplicativo, só estamos compactando
  o código mesmo para facilitar 

*/

bool fecux::utils::files::is_file(const char* _file) noexcept{
  return std::filesystem::exists(_file) && std::filesystem::is_regular_file(_file);
}

bool fecux::utils::files::is_dir(const char* _dir) noexcept{
  return std::filesystem::exists(_dir) && std::filesystem::is_directory(_dir);
}

bool fecux::utils::files::is_empty(const char* _dir) noexcept{
  return std::filesystem::is_empty(_dir);
}

void fecux::utils::files::create_dirs(const char* _dir) noexcept{
  if(!fecux::utils::files::is_dir(_dir)){
    std::filesystem::create_directories(_dir);
  }
  return;
}
