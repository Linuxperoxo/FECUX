//==========================================|
//   FILE: config.cpp                       |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstdlib>
#include <iostream>
#include <libconfig.h++>
#include <new>

#include "../include/color.hpp"
#include "../include/config.hpp"
#include "../include/exception.hpp"
#include "../include/integrity.hpp"
#include "../include/managerobj.hpp"

/*

===========================================================|
CONSTRUCTOR

 */

fecux::main::config::config() : _options(nullptr) {
  _options = static_cast<opts *>(std::malloc(sizeof(opts)));
  try {
    if (_options == nullptr) {
      throw std::bad_alloc();
    }

    make_obj<opts>(_options);

    fecux::utils::string *_options_struct_ptr[OPTS_NUM] = {
        &_options->_source_dir, &_options->_fakeroot_dir, &_options->_cflags,
        &_options->_cxxflags, &_options->_jobs};

    char **_options_loaded = fecux::tools::runtime::integrity::verify_config();

    for (int i = 0; i < OPTS_NUM; i++) {
      *_options_struct_ptr[i] = _options_loaded[i];
      std::free(_options_loaded[i]);
    }
    std::free(_options_loaded);
  }

  catch (fecux::tools::runtime::exception &_runtime_error) {
    std::cout << RED << "ERROR: " << NC << _runtime_error.what() << '\n';
    exit(_runtime_error.error_code());
  }

  catch (std::bad_alloc &_bad_alloc) {
    std::cout << RED << "CRITICAL ERROR: " << NC << "Memory alloc error "
              << _bad_alloc.what() << '\n';
    exit(EXIT_FAILURE);
  }

  catch (libconfig::ParseException &_paex) {
    std::cout << RED << "ERROR: " << NC << _paex.what() << " file -> " << RED
              << _paex.getFile() << NC << " line -> " << RED << _paex.getLine()
              << NC << '\n';
    exit(EXIT_FAILURE);
  }
}

/*

===========================================================|
DESTROYER

 */

fecux::main::config::~config() noexcept {
  expurg_obj(&*_options);
  std::free(&*_options);
}

/*

===========================================================|
GETS

 */

const char *fecux::main::config::source_dir() const noexcept {
  return *_options->_source_dir;
}

const char *fecux::main::config::fakeroot_dir() const noexcept {
  return *_options->_fakeroot_dir;
}

const char *fecux::main::config::cflags() const noexcept {
  return *_options->_cflags;
}

const char *fecux::main::config::cxxflags() const noexcept {
  return *_options->_cxxflags;
}

const char *fecux::main::config::jobs() const noexcept {
  return *_options->_jobs;
}
