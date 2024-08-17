//==========================================|
//   FILE: config.cpp                       |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstddef>
#include <cstdlib>
#include <libconfig.h++>
#include <iostream>
#include <vector>

#include "../include/utils/color.hpp"
#include "../include/utils/check.hpp"
#include "../include/caroline/config.hpp"
#include "../include/caroline/const_var.hpp"
#include "../include/utils/caroexception.hpp"

configs::configs(){
  smt_ptr<libconfig::Config> libconfig;

  std::vector<std::string> config_names = {"source_dir", "fakeroot_dir", "cflags", "cxxflags", "jobs"};
  std::vector<std::string*> config_value = {&source_dir, &fakeroot_dir, &cflags, &cxxflags, &jobs};

  try {
    if(!check::is_file(CONFIG_FILE_LOC)){
      throw caroexception(FILE_NOT_FOUND, "none", CONFIG_FILE_LOC);
    }

    libconfig->readFile(CONFIG_FILE_LOC);

    for(size_t i = 0; i < config_names.size(); i++){
      if(!libconfig->lookupValue(config_names[i], *config_value[i])){
        throw caroexception(CONFIGURATION_VAR_EMPTY, "none", "var load failed " GREEN + config_names[i] + NC " in file " GREEN + CONFIG_FILE_LOC + NC);
      }
    }
  }

  catch(caroexception& _runtime_error){
    _runtime_error.getAll();
    exit(_runtime_error.getErrorCode());
  }

  catch(libconfig::ParseException& _paex){
    std::cerr << RED "ERROR: " NC "Parse error in config file " GREEN << _paex.getFile() << NC "! " RED << _paex.getError() << NC " line " RED << _paex.getLine() << NC << '\n';
  }
}

std::string config_file::getSourceDir() const noexcept{
  return config_struct->source_dir;
}

std::string config_file::getFakerootDir() const noexcept{
  return config_struct->fakeroot_dir;
}

std::string config_file::getCflags() const noexcept{
  return config_struct->cflags;
}

std::string config_file::getCxxflags() const noexcept{
  return config_struct->cxxflags;
}

std::string config_file::getJobs() const noexcept{
  return config_struct->jobs;
}
