//==========================================|
//   FILE: files.hpp                        |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef FILES_HPP
#define FILES_HPP

class files{
public:
  static bool is_dir(const char* _dir) noexcept;
  static bool is_file(const char* _file) noexcept;
  static bool create_dir(const char* _dir) noexcept;
  static bool create_file(const char* _file) noexcept;
};

#endif
