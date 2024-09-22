/*

  COPYRIGHT: (c) 2024 per Linuxperoxo.
  AUTHOR: Linuxperoxo
  FILE: package.hpp

*/

#ifndef __PACKAGE_HPP
#define __PACKAGE_HPP

#include <cstdint>

#include "../memory/make_obj.hpp"
#include "../utils/string.hpp"


#define PKG_INFO_NUM 4 

namespace fecux{
namespace main{

class managerPackage{
private:
  class package{
  private:
    struct infos{
    private:
      infos(const infos&) = delete;
      infos(infos&&) = delete;
      infos& operator=(const infos&) = delete;
      infos& operator=(infos&&) = delete;
      
      struct fork{
      private:
        fork(const infos&) = delete;
        fork(infos&&) = delete;
        fork& operator=(const fork&) = delete;
        fork& operator=(fork&&) = delete;
      public:
        package** _fork;
        uint16_t _deps_num;

        explicit fork(const uint16_t _deps_num)
          : _fork(nullptr),
            _deps_num(_deps_num){}

        ~fork() noexcept{
          for(uint16_t i = 0; i < _deps_num; i++){
            fecux::memory::expurg<package>(_fork[i]);
          }
          std::free(_fork);
        }
      }; // end of struct fork

    public:
      fecux::utils::string _pkg_name;
      fecux::utils::string _pkg_version;
      fecux::utils::string _pkg_url;
      fecux::utils::string _pkg_desc;
      fecux::utils::string _pkg_root;

      fork* _pkg_deps;

      explicit infos() noexcept
        : _pkg_name(),
          _pkg_version(),
          _pkg_url(),
          _pkg_desc(),
          _pkg_root(),
          _pkg_deps(nullptr){}

      ~infos() noexcept{
        fecux::memory::expurg<fork>(_pkg_deps);
        std::free(_pkg_deps);
      };
    }; // end of struct infos; 

    package(const package&) = delete;
    package(package&&) = delete;
    package& operator=(const package&) = delete;
    package& operator=(package&&) = delete;

    infos* _pkg_infos;

    void make_struct();
    void package_exist(const char* _pkg_name); 
  public: 
    explicit package(const char* _pkg_name) noexcept;
    
    ~package() noexcept;
  };

  struct packageNode{
  private:
    packageNode(const packageNode&) = delete;
    packageNode(package&&) = delete;
    packageNode& operator=(const packageNode&) = delete;
    packageNode& operator=(package&&) = delete;
  public:
    package* _pkg;
    packageNode* _next_pkg;

    explicit packageNode(package* _pkg) noexcept
      : _pkg(_pkg),
        _next_pkg(nullptr){}

    ~packageNode(){
      fecux::memory::expurg<package>(_pkg);
      std::free(_pkg);
    }
  };

  static inline packageNode* _first_node{nullptr};
public:
  static void add_package(const char* _pkg_name);
};

} // namespace main
} // namespace fecux

#endif

