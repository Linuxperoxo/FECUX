//==========================================|
//   FILE: package.cpp                      |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstdlib>
#include <iostream>
#include <filesystem>
#include <new>

#include "../include/package.hpp"
#include "../include/files_utils.hpp"
#include "../include/fecux_vars.hpp"
#include "../include/exception.hpp"
#include "../include/color.hpp"

/*

===========================================================|
CONSTRUCTOR

 */

fecux::main::package::package(const char* _pkg_name) noexcept
  : _pkg_info(nullptr){
  try{
    _pkg_info = init_struct();
    _pkg_info->_pkg_root = package_exist(_pkg_name);
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
    std::free(_pkg_info);
  }
}

/*

===========================================================|
CLASS MEMBER FUNCTIONS

 */

fecux::main::package::info* fecux::main::package::init_struct(){
  info* _tmp_ptr = static_cast<info*>(std::malloc(sizeof(info)));
  if(_tmp_ptr == nullptr) throw std::bad_alloc();

  return _tmp_ptr;
}

const char* fecux::main::package::package_exist(const char* _pkg_name){
  if(fecux::tools::runtime::filesUtils::is_empty(MAIN_REPO_DIR)) throw fecux::tools::runtime::exception(MAIN_REPO_IS_EMPTY);
    
  for(const auto& _branch : std::filesystem::directory_iterator(MAIN_REPO_DIR)){
    if(_branch.is_directory()){
      fecux::utils::string _full_dir = _branch.path().c_str();
      if(fecux::tools::runtime::filesUtils::is_dir(_full_dir._cat_str("/", _pkg_name))) return *_full_dir;
    }
  }
  fecux::utils::string _what = "Package -> "; 
  _what._cat_str(RED, _pkg_name, NC, " not found");
  throw fecux::tools::runtime::exception(_what, PKG_NOT_FOUND);
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
