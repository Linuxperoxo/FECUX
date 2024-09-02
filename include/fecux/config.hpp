//==========================================|
//   FILE: config.hpp                       |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include "../utils/string.hpp"

namespace fecux{
  namespace main{
    class config{
    private:
      typedef struct options{
        fecux::utils::string source_dir;
        fecux::utils::string fakeroot_dir;
        fecux::utils::string cflags;
        fecux::utils::string cxxflags;
        fecux::utils::string jobs;
        
        explicit options() noexcept
          : source_dir(), 
            fakeroot_dir(),
            cflags(),
            cxxflags(),
            jobs(){ 
        }
        
        ~options() noexcept = default;
      }options;
      
      options* verify() const; 
      
      options* _options_struct;
    public:
      explicit config() noexcept;
      
      ~config() noexcept;
    };
  }
}

#endif
