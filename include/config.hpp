//==========================================|
//   FILE: config.hpp                       |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <cstdlib>

#include "string.hpp"

#define OPTS_NUM 5

namespace fecux{
  namespace main{
    class config{
    private:
    typedef struct options{
        fecux::utils::string _source_dir;
        fecux::utils::string _fakeroot_dir;
        fecux::utils::string _cflags;
        fecux::utils::string _cxxflags;
        fecux::utils::string _jobs;  
        
        inline explicit options() noexcept
          : _source_dir(),
            _fakeroot_dir(),
            _cflags(),
            _cxxflags(),
            _jobs(){
          };
          
        ~options() = default;
      }opts;
      opts* _options;
      
      config(const config&) = delete;
      config(const config&&) = delete;
      config& operator=(const config&) = delete;
      config& operator=(const config&&) = delete;
    public:
      explicit config();
      
      ~config() noexcept;
      
      const char* source_dir() const noexcept;
      const char* fakeroot_dir() const noexcept;
      const char* cflags() const noexcept;
      const char* cxxflags() const noexcept;
      const char* jobs() const noexcept;
    };
  }
}

#endif
