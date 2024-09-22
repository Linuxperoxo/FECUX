/*

  COPYRIGHT: (c) 2024 per Linuxperoxo.
  AUTHOR: Linuxperoxo
  FILE: files.hpp

*/

#ifndef __FILES_UTILS_HPP__
#define __FILES_UTILS_HPP__

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
  static bool is_file(const char *_file) noexcept;
  static bool is_dir(const char *_dir) noexcept;
  static bool is_empty(const char *_dir) noexcept;
  static void create_dirs(const char *_dir) noexcept;
};

} // namespace tools
} // namespace fecux

#endif
