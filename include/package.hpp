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
      
        inline explicit pkg_info() noexcept
          : _pkg_name(),
            _pkg_version(),
            _pkg_url(),
            _pkg_desc(),
            _pkg_root(){
          
        }
        
        pkg_info(const pkg_info&)            = delete;
        pkg_info(pkg_info&&)                 = delete;
        pkg_info& operator=(const pkg_info&) = delete;
        pkg_info& operator=(pkg_info&&)      = delete;
        
        ~pkg_info() noexcept = default;
      }info;
      
      info* _pkg_info;
      
      void init_struct();
      void package_exist(const char* _pkg_name); 
      void populate_struct();
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
