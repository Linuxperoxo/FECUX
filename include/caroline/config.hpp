//==========================================|
//   FILE: config.hpp                       |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace caroline{

struct options{
  static char* source_dir;
  static char* fakeroot_dir;
  static char* cflags;
  static char* cxxflags;
  static char* jobs;

  static bool configured;

  explicit options();

  ~options() noexcept;
};

class configuration{
private:
  options* _option;
public:
  explicit configuration();

  ~configuration() noexcept;

  const char* source_dir() const noexcept;
  const char* fakeroot_dir() const noexcept;
  const char* cflags() const noexcept;
  const char* cxxflags() const noexcept;
  const char* jobs() const noexcept;
};

}

#endif
