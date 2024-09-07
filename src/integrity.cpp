//==========================================|
//   FILE: integrity.cpp                    |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <chrono>
#include <cstdlib>
#include <cstring>
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

#define NUM_CHECK_DIRS 4
#define DELAY 500
#define NUM_INFOS 4

/*
 
===========================================================|
CLASS MEMBER FUNCTIONS
 
 */

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

char** fecux::tools::runtime::integrity::verify_infos(const char* _file){
  libconfig::Config* _libconfig = static_cast<libconfig::Config*>(std::malloc(sizeof(libconfig::Config)));
  char** _infos_array = static_cast<char**>(std::malloc(sizeof(char*) * NUM_INFOS));
  
  if(_libconfig == nullptr || _infos_array == nullptr) throw std::bad_alloc();
  
  make_obj<libconfig::Config>(_libconfig);
  _libconfig->readFile(_file);
  
  const char* _infos_name[NUM_INFOS] = {
    "pkg_name", 
    "pkg_version", 
    "pkg_url", 
    "pkg_desc", 
  };

  std::string _buffer;

  for(int i = 0; i < NUM_INFOS; i++){
    if(!_libconfig->lookupValue(_infos_name[i], _buffer) || _buffer.empty()){
      for(int c = 0; c < i; c++){
        std::free(_infos_array[c]);
      }
      expurg_obj(_libconfig);
      std::free(_libconfig);
      std::free(_infos_array);

      fecux::utils::string _what;
      _what._cat_str("Unable to load the variable -> ", RED, _infos_name[i], NC, " in file -> ", RED, _file, NC);
      throw fecux::tools::runtime::exception(_what, FAILED_TO_LOAD_INFO);
    }

    _infos_array[i] = static_cast<char*>(std::malloc(std::strlen(_buffer.c_str()) + 1));
    
    if(_infos_array[i] == nullptr){
      for(int k = 0; k < i; k++){
        std::free(_infos_array[k]);
      }
      expurg_obj(_libconfig);

      std::free(_libconfig);
      std::free(_infos_array);
    }
    std::strcpy(_infos_array[i], _buffer.c_str());
  }
  return _infos_array;
}
