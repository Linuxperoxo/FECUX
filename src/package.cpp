//==========================================|
//   FILE: package.cpp                      |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <filesystem>
#include <libconfig.h++>
#include <new>

#include "../include/package.hpp"
#include "../include/files_utils.hpp"
#include "../include/fecux_vars.hpp"
#include "../include/exception.hpp"
#include "../include/color.hpp"
#include "../include/managerobj.hpp"
#include "../include/integrity.hpp"

#define NUM_INFOS 4

/*

===========================================================|
CONSTRUCTOR

 */

fecux::main::package::package(const char* _pkg_name) noexcept
  : _pkg_info(nullptr){
  try{
    init_struct();
    package_exist(_pkg_name);
    populate_struct();
  }

  catch(fecux::tools::runtime::exception& _runtime_error){
    std::cerr << RED << "ERROR: " << NC << _runtime_error.what() << '\n';
    exit(_runtime_error.error_code());
  }
}

/*

===========================================================|
DESTROYER

 */

fecux::main::package::~package() noexcept{
  if(_pkg_info != nullptr){
    expurg_obj(_pkg_info);
    std::free(_pkg_info);
  }
}

/*

===========================================================|
CLASS MEMBER FUNCTIONS

 */

void fecux::main::package::init_struct(){
  _pkg_info = static_cast<info*>(std::malloc(sizeof(info)));
  if(_pkg_info == nullptr){ 
    throw std::bad_alloc();
  }
  make_obj<info>(_pkg_info);
}

void fecux::main::package::package_exist(const char* _pkg_name){
  if(fecux::tools::runtime::filesUtils::is_empty(MAIN_REPO_DIR)){
    throw fecux::tools::runtime::exception(MAIN_REPO_IS_EMPTY);
  }
    
  for(const auto& _branch : std::filesystem::directory_iterator(MAIN_REPO_DIR)){
    if(_branch.is_directory()){
      fecux::utils::string _full_dir;
      if(fecux::tools::runtime::filesUtils::is_dir(_full_dir._cat_str(_branch.path().c_str(), "/", _pkg_name))){
        _pkg_info->_pkg_root = _full_dir;
        return;
      }
    }
  }
  fecux::utils::string _what; 
  _what._cat_str("Package-> " , RED, _pkg_name, NC, " not found");
  throw fecux::tools::runtime::exception(_what, PKG_NOT_FOUND);
}

void fecux::main::package::populate_struct(){
  fecux::utils::string _info_file_locale;
  _info_file_locale._cat_str(*_pkg_info->_pkg_root, "/", INFOPKG_FILE);
  if(!fecux::tools::runtime::filesUtils::is_file(*_info_file_locale)){
    fecux::utils::string _what;
    _what._cat_str("Package information file not found in -> ", RED, *_info_file_locale, NC);
    throw fecux::tools::runtime::exception(_what, INFOPKG_FILE_NOT_FOUND);
  }

  try{
    char** _infos_value = fecux::tools::runtime::integrity::verify_infos(*_info_file_locale);
    
    fecux::utils::string* _infos_ref[NUM_INFOS] = {
      &_pkg_info->_pkg_name, 
      &_pkg_info->_pkg_version, 
      &_pkg_info->_pkg_url, 
      &_pkg_info->_pkg_desc
    }; 
    
    for(size_t i = 0; i < NUM_INFOS; i++){
      *_infos_ref[i] = _infos_value[i];
      std::free(_infos_value[i]);
    }
    std::free(_infos_value);
  }

  catch(fecux::tools::runtime::exception& _runtime_error){
    throw fecux::tools::runtime::exception(std::move(_runtime_error));
  }

  catch(std::bad_alloc&){
    throw std::bad_alloc();
  }
} 

/*

===========================================================|
GETS

 */

const char* fecux::main::package::name() const noexcept{
  return *_pkg_info->_pkg_name;
}

const char* fecux::main::package::version() const noexcept{
  return *_pkg_info->_pkg_version;
}

const char* fecux::main::package::url() const noexcept{
  return *_pkg_info->_pkg_url;
}

const char* fecux::main::package::desc() const noexcept{
  return *_pkg_info->_pkg_desc;
}

const char* fecux::main::package::root() const noexcept{
  return *_pkg_info->_pkg_root;
}
