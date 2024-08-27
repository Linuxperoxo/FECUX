//==========================================|
//   FILE: integrity.cpp                    |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstdlib>
#include <iostream>
#include <libconfig.h++>
#include <thread>
#include <chrono>
#include <fstream>

#include "../include/caroline/integrity.hpp"
#include "../include/caroline/vars.hpp"
#include "../include/extra/caroexception.hpp"
#include "../include/utils/files.hpp"
#include "../include/utils/color.hpp"

void caroline::integrity::check_config(){
  try{
    if(!files::is_file(CONFIG_FILE)){
      if(genConfigFile() == 1){
        std::cerr << YELLOW "WARNING: " NC "Configuration file was created in " << GREEN << CONFIG_FILE << NC << ". GO CUSTOMIZE IT! >:)\n";
      }
      throw caroline::caroex(CONFIG_FILE_NOT_FOUND);
    }
    
    void* _raw_libconfig = malloc(sizeof(libconfig::Config));

    if(_raw_libconfig == nullptr){
      throw caroline::caroex(MEMORY_ALLOCATION_ERROR);
    }

    libconfig::Config* _libconfig = new(_raw_libconfig) libconfig::Config();

    _libconfig->readFile(CONFIG_FILE);

    const char* _options_names[5] = {"source_dir", "fakeroot_dir", "cflags", "cxxflags", "jobs"};

    std::string _buffer;

    for(const auto& _name : _options_names){
      if(!_libconfig->exists(_name) || !_libconfig->lookupValue(_name, _buffer) || _buffer.empty()){
        std::cerr << RED "VAR FAILED: ( " NC << _name << RED " )" NC << '\n';
        
        _libconfig->~Config();

        std::free(_raw_libconfig);
        
        _libconfig = nullptr;
        
        throw caroline::caroex(CONFIGURATION_VAR_FAILED);
      }
    }
    _libconfig->~Config();
    
    std::free(_raw_libconfig);
    _raw_libconfig = nullptr;
    _libconfig = nullptr;
  }

  catch(caroline::caroex& _runtime_error){
    _runtime_error.all();
    exit(_runtime_error.errorCode());
  }

  catch(libconfig::ParseException& _paex){
    std::cerr << RED "ERROR: " NC "Parse  error in config file " GREEN << _paex.getFile() << NC << "! " RED << _paex.getError() << NC " line " RED << _paex.getLine() << NC << '\n';
    exit(EXIT_FAILURE);
  }
}

void caroline::integrity::check_dirs(const caroline::configuration& _configuration_buffer){
  try{
    const char* _dirs[4] = {_configuration_buffer.source_dir(), _configuration_buffer.fakeroot_dir(), REPO_DIR, WORLD_DIR};

    for(const auto& dir : _dirs){
      if(!files::is_dir(dir)){
        if(dir == REPO_DIR){
          throw caroline::caroex(REPO_DIR_NOT_EXIST);  
        }
        std::cerr << YELLOW "WARNING: " NC "Directory " YELLOW << dir << NC " not found!\n";
        std::cerr << GREEN "::: " NC "Creating " YELLOW << dir << NC << '\n';
        
        files::create_dir(dir);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
      }
    }
  }

  catch(caroline::caroex& _runtime_error){
    _runtime_error.all();
    exit(_runtime_error.errorCode());
  }
}

int caroline::integrity::genConfigFile() noexcept{
  void* _raw_ofstream = malloc(sizeof(std::ofstream));

  if(_raw_ofstream == nullptr){
    return -1;
  }
  
  std::ofstream* _ofstream = new(_raw_ofstream) (std::ofstream);

  _ofstream->open(CONFIG_FILE);

  if(!_ofstream->is_open()){
    std::free(_raw_ofstream);
    return -1;
  }
  
  *_ofstream << "# Directory responsible for storing\n# all downloaded sources\n# default (\"/var/lalapkg/source_dir\")\nsource_dir=\"/var/lalapkg/source_dir\"\n\n";
  *_ofstream << "# Directory where the package will be installed\n# default(\"/tmp/lalapkg/fakeroot\")\nfakeroot_dir=\"/tmp/lalapkg/fakeroot\"\n\n";
  *_ofstream << "# Optimization flags for C code\ncflags=\"-march=native -O2 -pipe\"\n\n";
  *_ofstream << "# Optimization flags for C++ code\ncxxflags=\"-march=native -O2 -pipe\"\n\n";
  *_ofstream << "# Number of threads to use\njobs=\"-j$(nproc)\"\n";

  _ofstream->close();

  std::free(_raw_ofstream);
  return 1;
}
