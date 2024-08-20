//==========================================|
//   FILE: config.hpp                       |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "../tools/smartpointer.hpp"

namespace caroline{

struct options{
  static char* source_dir;
  static char* fakeroot_dir;
  static char* cflags;
  static char* cxxflags;
  static char* jobs;

  static bool configured;

  explicit options() noexcept;
  ~options() noexcept;
};

class configuration{
private:
  const smt_ptr<options> option;
public:
  explicit configuration() noexcept : option(){ /** */ };
  ~configuration() noexcept = default;

  const char* getSource_dir() const noexcept;
  const char* getFakeroot_dir() const noexcept;
  const char* getCflags() const noexcept;
  const char* getCxxflags() const noexcept;
  const char* getJobs() const noexcept;
};

}

#endif
