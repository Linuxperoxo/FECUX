//==========================================|
//   FILE: package.cpp                      |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <libconfig.h++>
#include <new>
#include <thread>

#include "../include/animation.hpp"
#include "../include/fecux_vars.hpp"
#include "../include/files_utils.hpp"
#include "../include/integrity.hpp"
#include "../include/managerobj.hpp"
#include "../include/package.hpp"

/*

===========================================================|
CONSTRUCTOR

 */

fecux::main::package::package(const char *_pkg_name) noexcept
    : _pkg_info(nullptr) {
  try {
    init_struct();
    package_exist(_pkg_name);
    populate_info_struct();
    load_functions();
    exec_build_functions();
    exec_install_functions();
  }

  catch (fecux::tools::runtime::exception &_runtime_error) {
    std::cerr << RED << "PACKAGE FAILED: " << NC << _pkg_name << '\n';
    std::cerr << RED << "ERROR: " << NC << _runtime_error.what() << '\n';
    exit(_runtime_error.error_code());
  }

  catch (libconfig::ParseException &_paex) {
    std::cerr << RED << "PACKAGE FAILED: " << NC << _pkg_name << '\n';
    std::cerr << RED << "ERROR: " << NC << _paex.what() << " in file -> " << RED
              << _paex.getFile() << NC << " line -> " << RED << _paex.getLine()
              << NC << '\n';
    exit(EXIT_FAILURE);
  }

  catch (std::bad_alloc &_bad_alloc) {
    std::cerr << RED << "PACKAGE FAILED: " << NC << _pkg_name << '\n';
    std::cerr << RED << "ERROR: " << NC << _bad_alloc.what() << '\n';
  }
}

/*

===========================================================|
DESTROYER

 */

fecux::main::package::~package() noexcept {
  if (_pkg_info != nullptr) {
    expurg_obj(_pkg_info);
    expurg_obj(_pkg_func);

    std::free(_pkg_info);
    std::free(_pkg_func);
  }
}

/*

===========================================================|
CLASS MEMBER FUNCTIONS

 */

void fecux::main::package::init_struct() {
  _pkg_info = static_cast<info *>(std::malloc(sizeof(info)));
  if (_pkg_info == nullptr) {
    throw std::bad_alloc();
  }
  make_obj<info>(_pkg_info);
}

void fecux::main::package::package_exist(const char *_pkg_name) {
  if (fecux::tools::runtime::filesUtils::is_empty(MAIN_REPO_DIR)) {
    throw fecux::tools::runtime::exception(MAIN_REPO_IS_EMPTY);
  }

  for (const auto &_branch :
       std::filesystem::directory_iterator(MAIN_REPO_DIR)) {
    if (_branch.is_directory()) {
      fecux::utils::string _full_dir;
      if (fecux::tools::runtime::filesUtils::is_dir(
              _full_dir._cat_str(_branch.path().c_str(), "/", _pkg_name))) {
        _pkg_info->_pkg_root = _full_dir;
        return;
      }
    }
  }
  throw fecux::tools::runtime::exception(PKG_NOT_FOUND);
}

void fecux::main::package::populate_info_struct() {
  fecux::utils::string _info_file_locale;
  _info_file_locale._cat_str(*_pkg_info->_pkg_root, "/", INFOPKG_FILE);

  if (!fecux::tools::runtime::filesUtils::is_file(*_info_file_locale)) {
    fecux::utils::string _what;
    _what._cat_str("Package information file not found in -> ", RED,
                   *_info_file_locale, NC);
    throw fecux::tools::runtime::exception(_what, INFOPKG_FILE_NOT_FOUND);
  }

  char **_infos_value =
      fecux::tools::runtime::integrity::verify_infos(*_info_file_locale);

  fecux::utils::string *_infos_ref[INFO_NUM] = {
      &_pkg_info->_pkg_name, &_pkg_info->_pkg_version, &_pkg_info->_pkg_url,
      &_pkg_info->_pkg_desc};

  for (size_t i = 0; i < INFO_NUM; i++) {
    *_infos_ref[i] = _infos_value[i];
    std::free(_infos_value[i]);
  }
  std::free(_infos_value);
}

void fecux::main::package::load_functions() {
  fecux::utils::string _build_file_locale;
  _build_file_locale._cat_str(*_pkg_info->_pkg_root, "/", BUILDPKG_FILE);

  if (!fecux::tools::runtime::filesUtils::is_file(*_build_file_locale)) {
    fecux::utils::string _what;
    _what._cat_str("Build file was not found in -> ", RED, *_build_file_locale,
                   NC);
    throw fecux::tools::runtime::exception(_what, BUILDPKG_FILE_NOT_FOUND);
  }

  const char *_functs_name[POSSIBLE_FUNCS] = {"pre_build", "build",
                                              "pos_build", "pre_install",
                                              "install",   "pos_install"};

  int _enable_functs[POSSIBLE_FUNCS];
  bool _found = false;

  fecux::utils::string _command;

  for (int i = 0; i < POSSIBLE_FUNCS; i++) {
    _command._cat_str("source ", *_build_file_locale, " && declare -f ",
                      _functs_name[i], " &> /dev/null");
    _enable_functs[i] = system(*_command) == 0 ? 1 : 0;
    _found = _enable_functs[i] == 1 ? true : _found;
    _command.clean();
  }

  if (!_found) {
    fecux::utils::string _what;
    _what._cat_str(
        "No function found in the build file -> ", RED, *_build_file_locale, NC,
        "! The file can contain these functions -> [ ", RED,
        "pre_build, build, pos_build, pre_install, install, pos_install", NC,
        " ]. Mandatory functions are -> [ ", RED, "build, install", NC, " ]");
    throw fecux::tools::runtime::exception(_what, NONE_FUNCTION_FOUND);
  }

  _pkg_func = static_cast<func *>(std::malloc(sizeof(func)));

  if (_pkg_func == nullptr) {
    throw std::bad_alloc();
  }

  make_obj<func>(_pkg_func, _enable_functs[0], _enable_functs[1],
                 _enable_functs[2], _enable_functs[3], _enable_functs[4],
                 _enable_functs[5]);
  _pkg_func->is_safe();
}

void fecux::main::package::exec_functions(const char **_func_names,
                                          const unsigned **_func_ref,
                                          const int &_possible_func,
                                          const bool &_use_animation,
                                          const char *_animation_msg) {
  std::atomic<bool> *_running{nullptr};
  std::thread *_animation_thread{nullptr};

  auto clean = [_running, _animation_thread]() -> void {
    if (_running != nullptr) {
      _running->store(false);
      _animation_thread->join();

      expurg_obj(_running);
      expurg_obj(_animation_thread);

      std::free(_running);
      std::free(_animation_thread);
    }
  };

  if (_use_animation) {
    _running = static_cast<std::atomic<bool> *>(
        std::malloc(sizeof(std::atomic<bool>)));
    _animation_thread =
        static_cast<std::thread *>(std::malloc(sizeof(std::thread)));
    if (_running == nullptr || _animation_thread == nullptr) {
      std::free(_running);
      std::free(_animation_thread);
      throw std::bad_alloc();
    }
    make_obj<std::atomic<bool>>(_running, true);
    make_obj<std::thread>(_animation_thread, fecux::utils::animation::run,
                          _running, _animation_msg);
  }

  fecux::utils::string _build_file_locale;
  fecux::utils::string _command;

  _build_file_locale._cat_str(*_pkg_info->_pkg_root, "/", BUILDPKG_FILE);

  for (int i = 0; i < _possible_func; i++) {
    if (*_func_ref[i] == 1) {
      _command._cat_str("source ", *_build_file_locale, " && ", _func_names[i]);
      if (_use_animation) {
        _command._cat_str(" &> /dev/null");
      }

      if (system(*_command) != 0) {
        fecux::utils::string _what;
        clean();
        _what._cat_str("An error occurred in functions -> ", RED,
                       _func_names[i], NC, " file -> ", RED,
                       *_build_file_locale, NC, ". Check it! :/");
        throw fecux::tools::runtime::exception(_what, ERROR_FUNCTION_BUILD);
      }
      _command.clean();
    }
  }
  clean();
}

void fecux::main::package::exec_build_functions() {
  const char *_build_functions_name[BUILD_POSSIBLE_FUNCTS]{"pre_build", "build",
                                                           "pos_build"};

  const unsigned int *_build_functions_ref[BUILD_POSSIBLE_FUNCTS]{
      &_pkg_func->_pre_build, &_pkg_func->_build, &_pkg_func->_pos_build};

  exec_functions(_build_functions_name, _build_functions_ref,
                 BUILD_POSSIBLE_FUNCTS);
}

void fecux::main::package::exec_install_functions() {
  const char *_install_functions_name[INSTALL_POSSIBLE_FUNCTS]{
      "pre_install", "install", "pos_install"};

  const unsigned int *_install_functions_ref[INSTALL_POSSIBLE_FUNCTS]{
      &_pkg_func->_pre_install, &_pkg_func->_install, &_pkg_func->_pos_install};

  exec_functions(_install_functions_name, _install_functions_ref,
                 INSTALL_POSSIBLE_FUNCTS);
}

/*

===========================================================|
GETS

 */

const char *fecux::main::package::name() const noexcept {
  return *_pkg_info->_pkg_name;
}

const char *fecux::main::package::version() const noexcept {
  return *_pkg_info->_pkg_version;
}

const char *fecux::main::package::url() const noexcept {
  return *_pkg_info->_pkg_url;
}

const char *fecux::main::package::desc() const noexcept {
  return *_pkg_info->_pkg_desc;
}

const char *fecux::main::package::root() const noexcept {
  return *_pkg_info->_pkg_root;
}
