/*

  COPYRIGHT: (c) 2024 per Linuxperoxo.
  AUTHOR: Linuxperoxo
  FILE: files.hpp

*/

#ifndef __FILES_UTILS_HPP__
#define __FILES_UTILS_HPP__

#include <filesystem>

namespace fecux{
namespace utils{

class files{
private:
  files() = delete;
  files(const files&) = delete;
  files(files&&) = delete;
  files& operator=(const files&) = delete;
  files& operator=(files&&) = delete;
 
  ~files() = delete;

public:



  /*

    Essas funções são apenas para compactar a chamada de outras funções

  */



  inline static bool is_file(const char *_file) noexcept{
    return std::filesystem::exists(_file) && std::filesystem::is_regular_file(_file);
  }

  inline static bool is_dir(const char *_dir) noexcept{
    return std::filesystem::exists(_dir) && std::filesystem::is_directory(_dir);
  }

  inline static bool is_empty(const char *_dir) noexcept{
    return std::filesystem::exists(_dir) && std::filesystem::is_empty(_dir);
  }

  inline static void create_dirs(const char *_dir) noexcept{
    if(!fecux::utils::files::is_dir(_dir)){
      std::filesystem::create_directories(_dir);
    }
  }
};

} // namespace tools
} // namespace fecux

#endif

