//==========================================|
//   FILE: integrity.cpp                    |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstdlib>
#include <iostream>
#include <libconfig.h++>
#include <vector>
#include <thread>
#include <chrono>

#include "../include/caroline/integrity.hpp"
#include "../include/caroline/config.hpp"
#include "../include/caroline/vars.hpp"
#include "../include/extra/caroexception.hpp"
#include "../include/utils/files.hpp"
#include "../include/utils/color.hpp"

void caroline::integrity::check_config(){
  try{
    if(!files::is_file(CONFIG_FILE)){
      throw caroline::caroex(CONFIG_FILE_NOT_FOUND);
    }
    
    void* _raw_libconfig = malloc(sizeof(libconfig::Config));

    if(_raw_libconfig == nullptr){
      throw caroline::caroex(MEMORY_ALLOCATION_ERROR);
    }

    libconfig::Config* _libconfig = new(_raw_libconfig) libconfig::Config();

    _libconfig->readFile(CONFIG_FILE);

    const std::vector<const char*> _options_names = {"source_dir", "fakeroot_dir", "cflags", "cxxflags", "jobs"};

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

void caroline::integrity::check_dirs(){
  try{
    void* _raw_configuration_buffer = malloc(sizeof(caroline::configuration));

    if(_raw_configuration_buffer == nullptr){
      throw caroline::caroex(MEMORY_ALLOCATION_ERROR);
    }

    caroline::configuration* _configuration_buffer = new(_raw_configuration_buffer) caroline::configuration();

    std::vector<const char*> _dirs = {_configuration_buffer->source_dir(), _configuration_buffer->fakeroot_dir(), REPO_DIR, WORLD_DIR};

    for(const auto& dir : _dirs){
      if(!files::is_dir(dir)){
        if(dir == REPO_DIR){
          _configuration_buffer->~configuration();
          
          std::free(_raw_configuration_buffer);
          
          _configuration_buffer = nullptr;
          _raw_configuration_buffer = nullptr;

          throw caroline::caroex(REPO_DIR_NOT_EXIST);  
        }
        std::cerr << YELLOW "WARNING: " NC "Directory " YELLOW << dir << NC " not found!\n";
        std::cerr << GREEN "::: " NC "Creating " YELLOW << dir << NC << '\n';
        
        files::create_dir(dir);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
      }
    }
    _configuration_buffer->~configuration();

    std::free(_raw_configuration_buffer);

    _configuration_buffer = nullptr;
    _raw_configuration_buffer = nullptr;
  }

  catch(caroline::caroex& _runtime_error){
    _runtime_error.all();
    exit(_runtime_error.errorCode());
  }
}
