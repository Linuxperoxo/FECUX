//==========================================|
//   FILE: package.hpp                      |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef __PACKAGE_HPP__
#define __PACKAGE_HPP__

#include "string.hpp"

namespace fecux{
  namespace main{
    class package{
    private:
      typedef struct pkg_info{    
        fecux::utils::string _pkg_name;
        fecux::utils::string _pkg_version;
        fecux::utils::string _pkg_url;
        fecux::utils::string _pkg_desc;
        fecux::utils::string _pkg_root; 
      }info;
      
      info* _pkg_info;
      
      info* init_struct();
      const char* package_exist(const char* _pkg_name); 
    public:
      explicit package(const char* _pkg_name) noexcept;
      ~package() noexcept;
      
      const char* name() const noexcept;
      const char* version() const noexcept;
      const char* url() const noexcept;
      const char* desc() const noexcept;
      const char* root() const noexcept;
    };
  }
}

#endif
