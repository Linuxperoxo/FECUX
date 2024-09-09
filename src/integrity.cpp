//==========================================|
//   FILE: integrity.cpp                    |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <new>
#include <string>
#include <thread>
#include <iostream>
#include <libconfig.h++>

#include "../include/integrity.hpp"
#include "../include/color.hpp"
#include "../include/fecux_vars.hpp"
#include "../include/files_utils.hpp"
#include "../include/managerobj.hpp"
#include "../include/exception.hpp"
#include "../include/package.hpp"

#define NUM_CHECK_DIRS 4
#define DELAY 500

/*
 
===========================================================|
CLASS MEMBER FUNCTIONS
 
 */

char** fecux::tools::runtime::integrity::read_file(const char** _names, const size_t& _element_size, const char* _file){
  libconfig::Config* _libconfig = static_cast<libconfig::Config*>(std::malloc(sizeof(libconfig::Config)));
  char** _src = static_cast<char**>(std::malloc(sizeof(char*) * _element_size));

  if(_libconfig == nullptr || _src == nullptr){
    if(_libconfig != nullptr) std::free(_libconfig);
    if(_src != nullptr) std::free(_src);
    throw std::bad_alloc();
  }

  make_obj<libconfig::Config>(_libconfig); _libconfig->readFile(_file);

  std::string _buffer;

  for(size_t i = 0; i < _element_size; i++){
    if(!_libconfig->lookupValue(_names[i], _buffer) || _buffer.empty()){
      for(size_t c = 0; c < i; c++){
        std::free(_src[c]);
      }
      expurg_obj(_libconfig);
      std::free(_libconfig);
      std::free(_src);

      fecux::utils::string _what;
      _what._cat_str("Unable to load the variable -> ", RED, _names[i], NC, " in file -> ", RED, _file, NC);
      throw fecux::tools::runtime::exception(_what, FAILED_TO_LOAD_VAR);
    }
    
    const size_t _str_size = std::strlen(_buffer.c_str());  

    _src[i] = static_cast<char*>(std::malloc(_str_size));
    
    if(_src[i] == nullptr){
      for(size_t k = 0; k < i; k++){
        std::free(_src[k]);
      }
      expurg_obj(_libconfig);
      std::free(_libconfig);
      std::free(_src);
      throw std::bad_alloc();
    }
    std::memcpy(_src[i], _buffer.c_str(), _str_size);
  }
  return _src;
}

void fecux::tools::runtime::integrity::verify_dirs(const fecux::main::config *_config) noexcept{
  const char* _dirs[NUM_CHECK_DIRS] = {
    _config->source_dir(), 
    _config->fakeroot_dir(), 
    MAIN_REPO_DIR, 
    WORLD_DIR
  };

  for(int i = 0; i < NUM_CHECK_DIRS; i++){
    if(!fecux::tools::runtime::filesUtils::is_dir(_dirs[i])){
      fecux::tools::runtime::filesUtils::create_dirs(_dirs[i]);
      std::cerr << YELLOW << "::: " << NC << GREEN << _dirs[i] << NC << " Created! :)\n";
      std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
    }
  }
}

char** fecux::tools::runtime::integrity::verify_config(){
  const char* _options_name[OPTS_NUM] = {
    "source_dir", 
    "fakeroot_dir", 
    "cflags", 
    "cxxflags", 
    "jobs"
  };
  return read_file(_options_name, OPTS_NUM, CONFIG_FILE);
}

char** fecux::tools::runtime::integrity::verify_infos(const char* _info_file){
  const char* _infos_name[INFO_NUM] = {
    "pkg_name", 
    "pkg_version", 
    "pkg_url", 
    "pkg_desc", 
  };
  return read_file(_infos_name, INFO_NUM, _info_file);
}
