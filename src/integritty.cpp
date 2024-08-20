//==========================================|
//   FILE: integrity.cpp                    |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstdlib>
#include <iostream>
#include <libconfig.h++>
#include <string>
#include <vector>
#include <fstream>

#include "../include/caroline/integrity.hpp"
#include "../include/tools/files.hpp"
#include "../include/caroline/caroexception.hpp"
#include "../include/tools/smartpointer.hpp"
#include "../include/caroline/carolinevars.hpp"
#include "../include/utils/color.hpp"

//int caroline::integrity::check_all(){}

void caroline::integrity::check_config_file(){
  try{
    if(!files::is_file(CONFIG_FILE)){
      if(integrity::genConfigFile() == 1){
        std::cerr << YELLOW "WARNING: " NC "Configuration file was created in " << GREEN << CONFIG_FILE << NC << ". GO CUSTOMIZE IT! >:)\n";
      }
      throw caroline::caroexception(CONFIG_FILE_NOT_FOUND);
    }
    
    smt_ptr<libconfig::Config> _libconfig;
  
    _libconfig->readFile(CONFIG_FILE);

    std::vector<const char*> _options_name = {"source_dir", "fakeroot_dir", "cflags", "cxxflags", "jobs"};

    std::string _buffer;

    for(const auto& _option : _options_name){
      if(!_libconfig->exists(_option) || !_libconfig->lookupValue(_option, _buffer) || _buffer.empty()){
        std::cerr << RED "VAR FAILED: ( " NC << _option << RED " ) " NC << '\n';
        throw caroline::caroexception(CONFIGURATION_VAR_FAILED);
      }
    }
  }

  catch(caroline::caroexception& _runtime_error){
    _runtime_error.getAll();
    exit(_runtime_error.getErrorCode());
  }

  catch(libconfig::ParseException& _paex){
    std::cerr << RED "ERROR: " NC "Parse  error in config file " GREEN << _paex.getFile() << NC << "! " RED << _paex.getError() << NC " line " RED << _paex.getLine() << NC << '\n';
    exit(EXIT_FAILURE);
  }
}

//int caroline::integrity::check_dirs(){}

int caroline::integrity::genConfigFile(){
  smt_ptr<std::ofstream> newConfigFile(sizeof(std::ofstream), CONFIG_FILE);
  
  if(!*newConfigFile){
    return -1;
  }

  *newConfigFile << "source_dir=\"\"\n";
  *newConfigFile << "fakeroot_dir=\"\"\n";
  *newConfigFile << "cflags=\"\"\n";
  *newConfigFile << "cxxflags=\"\"\n";
  *newConfigFile << "jobs=\"\"\n";

  newConfigFile->close();
  return 1;
}
