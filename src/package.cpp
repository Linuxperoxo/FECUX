/*

  COPYRIGHT: (c) 2024 per Linuxperoxo.
  AUTHOR: Linuxperoxo
  FILE: package.cpp

*/
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <new>

#include "../include/fecux/exception.hpp"
#include "../include/memory/make_obj.hpp"
#include "../include/fecux/package.hpp"
#include "../include/utils/files.hpp"
#include "../include/color.hpp"
#include "../include/env.hpp"

fecux::main::managerPackage::package::package(const char* _pkg_name) noexcept
  : _pkg_infos(nullptr){
    try{
      make_struct(); 
      package_exist(_pkg_name);
    }
    
    catch(fecux::main::exception& _runtime_error){
      std::cerr << RED << "-*- PACKAGE_FAILED: " << NC << _pkg_name << '\n';
      std::cerr << RED << "-*- ERROR: " << NC << _runtime_error.what() << '\n';
      std::cerr << RED << "-*- ERROR_CODE: " << NC << _runtime_error.error_code() << '\n';
      exit(_runtime_error.error_code());
    }

    catch(std::bad_alloc& _bad_alloc){
      std::cerr << RED << "-*- INTERNAL_CRITICAL_ERROR: " << NC << _bad_alloc.what() << '\n';
      exit(EXIT_FAILURE);
    }
  }

fecux::main::managerPackage::package::~package() noexcept{
  fecux::memory::expurg<fecux::main::managerPackage::package::infos>(_pkg_infos);
  std::free(_pkg_infos);
}

void fecux::main::managerPackage::package::make_struct(){
  _pkg_infos = static_cast<infos*>(std::malloc(sizeof(infos)));
  
  if(_pkg_infos == nullptr){
    throw std::bad_alloc();
  }
} 

void fecux::main::managerPackage::package::package_exist(const char* _pkg_name){
  for(const auto& _dir_branch : std::filesystem::directory_iterator(REPO_DIR)){
    if(fecux::utils::files::is_dir(_dir_branch.path().c_str())){
      {
        fecux::utils::string _pkg_root(_dir_branch.path().c_str());
        if(fecux::utils::files::is_dir(_pkg_root.cat_str("/", _pkg_name))){
          _pkg_infos->_pkg_root = std::move(_pkg_root);
          return;
        }
      }  
    }
  }
  throw fecux::main::exception(PKG_NOT_FOUND);
}

void fecux::main::managerPackage::add_package(const char* _pkg_name){
  try{  
    if(_first_node == nullptr){
      _first_node = static_cast<packageNode*>(std::malloc(sizeof(packageNode)));
      if(_first_node == nullptr){
        throw std::bad_alloc();
      }
    }
    _first_node->_pkg = static_cast<package*>(std::malloc(sizeof(package)));
    fecux::memory::make<package>(_first_node->_pkg, _pkg_name);
  }
  
  catch(std::bad_alloc& _bad_alloc){
    std::cerr << RED << "-*- INTERNAL_CRITICAL_ERROR: " << NC << _bad_alloc.what() << '\n';
    exit(EXIT_FAILURE);
  }
}

