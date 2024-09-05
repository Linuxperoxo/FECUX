//==========================================|
//   FILE: config.cpp                       |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstdlib>
#include <new>
#include <iostream>
#include <libconfig.h++>
#include <string>

#include "../include/exception.hpp"
#include "../include/config.hpp"
#include "../include/color.hpp"
#include "../include/managerobj.hpp"
#include "../include/fecux_vars.hpp"
#include "../include/files_utils.hpp"

/*
 
===========================================================|
CONSTRUCTOR
 
 */

fecux::main::config::config()
  : _options(nullptr){
  _options = static_cast<opts*>(std::malloc(sizeof(opts)));
  libconfig::Config* _libconfig = static_cast<libconfig::Config*>(std::malloc(sizeof(libconfig::Config)));
  try{
    if(_options == nullptr || _libconfig == nullptr){
      throw std::bad_alloc();
    }
    
    if(!fecux::tools::runtime::filesUtils::is_file(CONFIG_FILE)){
      std::free(&*_libconfig);
      std::free(&*_options);

      throw fecux::tools::runtime::exception(CONFIG_FILE_NOT_FOUND);
    }

    make_obj<libconfig::Config>(&*_libconfig);
    make_obj<opts>(&*_options);
    
    _libconfig->readFile(CONFIG_FILE);
    
    const char* _conf_file_opts_name[OPTS_NUM] = {"source_dir", "fakeroot_dir", "cflags", "cxxflags", "jobs"};
    fecux::utils::string* _config_file_opts_ref[OPTS_NUM] = {&_options->_source_dir, &_options->_fakeroot_dir, &_options->_cflags, &_options->_cxxflags, &_options->_jobs};
    
    std::string _buffer;
    
    for(size_t i = 0; i < OPTS_NUM; i++){
      if(!_libconfig->lookupValue(_conf_file_opts_name[i], _buffer) || _buffer.empty()){
        expurg_obj(&*_libconfig);
        expurg_obj(&*_options);

        std::free(&*_libconfig);
        std::free(&*_options);

        fecux::utils::string _what = "An error occurred while trying to load the option -> ";
        _what._cat_str(RED, _conf_file_opts_name[i], NC, "! Check config file -> ", RED, CONFIG_FILE, NC);

        throw fecux::tools::runtime::exception(_what, FAILED_TO_LOAD_OPT);
      }
      *_config_file_opts_ref[i] = _buffer.c_str();
    }
    expurg_obj(&*_libconfig);
    std::free(&*_libconfig);
  }

  catch(fecux::tools::runtime::exception& _runtime_error){
    std::cout << RED << "ERROR: " << NC << _runtime_error.what() << '\n';
    exit(_runtime_error.error_code());
  }

  catch(std::bad_alloc& _bad_alloc){
    std::cout << RED << "CRITICAL ERROR: " << NC << "Memory alloc error " << _bad_alloc.what() << '\n';
    exit(EXIT_FAILURE);
  }

  catch(libconfig::ParseException& _paex){
    std::cout << RED << "ERROR: " << NC << _paex.what() << " file -> " << RED << _paex.getFile() << NC << " line -> " << RED << _paex.getLine() << NC << '\n';
    exit(EXIT_FAILURE);
  }
}

/*

===========================================================|
DESTROYER

 */

fecux::main::config::~config() noexcept{
  expurg_obj(&*_options);
  std::free(&*_options);
}

/*
 
===========================================================|
GETS
 
 */

const char* fecux::main::config::source_dir() const noexcept{
  return *_options->_source_dir;
}

const char* fecux::main::config::fakeroot_dir() const noexcept{
  return *_options->_fakeroot_dir; 
}

const char* fecux::main::config::cflags() const noexcept{
  return *_options->_cflags;
}

const char* fecux::main::config::cxxflags() const noexcept{
  return *_options->_cxxflags;
}

const char* fecux::main::config::jobs() const noexcept{
  return *_options->_jobs;
}
