#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "../utils/smartpointer.hpp"

namespace caroline{
  struct options{
    static char* source_dir;
    static char* fakeroot_dir;
    static char* cflags;
    static char* cxxflags;
    static char* jobs;

    static bool configured;

    options();
    ~options();
  };

  class configuration{
  private:
    const smt_ptr<options> options_struct;
  public:
    configuration();
    
    const char* getSource_dir() const noexcept;
    const char* getFakeroot_dir() const noexcept;
    const char* getCflags() const noexcept;
    const char* getCxxflags() const noexcept;
    const char* getJobs() const noexcept;
  };
}

#endif
