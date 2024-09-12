//==========================================|
//   FILE: package.hpp                      |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef __PACKAGE_HPP__
#define __PACKAGE_HPP__

#include <iostream>

#include "color.hpp"
#include "exception.hpp"
#include "string.hpp"

#define INFO_NUM 4
#define BUILD_POSSIBLE_FUNCTS 3
#define INSTALL_POSSIBLE_FUNCTS 3
#define POSSIBLE_FUNCS BUILD_POSSIBLE_FUNCTS + INSTALL_POSSIBLE_FUNCTS

namespace fecux {
namespace main {
class package {
private:
  typedef struct pkg_info {
    fecux::utils::string _pkg_name;
    fecux::utils::string _pkg_version;
    fecux::utils::string _pkg_url;
    fecux::utils::string _pkg_desc;
    fecux::utils::string _pkg_root;

    inline explicit pkg_info() noexcept
        : _pkg_name(), _pkg_version(), _pkg_url(), _pkg_desc(), _pkg_root() {}

    pkg_info(const pkg_info &) = delete;
    pkg_info(pkg_info &&) = delete;
    pkg_info &operator=(const pkg_info &) = delete;
    pkg_info &operator=(pkg_info &&) = delete;

    ~pkg_info() noexcept = default;
  } info;

  typedef struct pkg_functions {
    const unsigned int _pre_build;
    const unsigned int _build;
    const unsigned int _pos_build;
    const unsigned int _pre_install;
    const unsigned int _install;
    const unsigned int _pos_install;

    inline explicit pkg_functions(const unsigned int &_pre_build,
                                  const unsigned int &_build,
                                  const unsigned int &_pos_build,
                                  const unsigned int &_pre_install,
                                  const unsigned int &_install,
                                  const unsigned int &_pos_install) noexcept
        : _pre_build(_pre_build), _build(_build), _pos_build(_pos_build),
          _pre_install(_pre_install), _install(_install),
          _pos_install(_pos_install) {}

    ~pkg_functions() noexcept = default;

    inline void is_safe() {
      if (_install == 0 && _build == 1) {
        std::cout << YELLOW << "WARNING: " << NC
                  << "The package has no function for installation. It will "
                     "just compile\n";
        return;
      }

      if (_install == 0 && _build == 0) {
        throw fecux::tools::runtime::exception(NONE_MAIN_FUNCTIONS_FOUND);
      }
    }
  } func;

  info *_pkg_info;
  func *_pkg_func;

  void init_struct();
  void package_exist(const char *_pkg_name);
  void populate_info_struct();
  void load_functions();
  void exec_functions(const char **_func_names, const unsigned **_func_ref,
                      const int &_possible_func,
                      const bool &_use_animation = false,
                      const char *_animation_msg = "");
  void exec_build_functions();
  void exec_install_functions();

public:
  explicit package(const char *_pkg_name) noexcept;
  ~package() noexcept;

  const char *name() const noexcept;
  const char *version() const noexcept;
  const char *url() const noexcept;
  const char *desc() const noexcept;
  const char *root() const noexcept;
};
} // namespace main
} // namespace fecux

#endif
