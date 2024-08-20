//==========================================|
//   FILE: config.cpp                       |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <libconfig.h++>

#include "../include/caroline/config.hpp"
#include "../include/caroline/carolinevars.hpp"
#include "../include/tools/files.hpp"
#include "../include/caroline/caroexception.hpp"
#include "../include/utils/color.hpp"

char* caroline::options::source_dir = nullptr;
char* caroline::options::fakeroot_dir = nullptr;
char* caroline::options::cflags = nullptr;
char* caroline::options::cxxflags = nullptr;
char* caroline::options::jobs = nullptr;

bool caroline::options::configured = false;

caroline::options::options(){
  smt_ptr<libconfig::Config> _libconfig;

  std::vector<const char*> _ptr_names = {"source_dir", "fakeroot_dir", "cflags", "cxxflags", "jobs"};
  std::vector<char**> _ptr_ref = {&source_dir, &fakeroot_dir, &cflags, &cxxflags, &jobs};

  try{
    if(configured){
      return;
    }

    if(!files::is_file(CONFIG_FILE)){
      throw caroline::caroexception(CONFIG_FILE_NOT_FOUND);   
    }
    _libconfig->readFile(CONFIG_FILE);

    for(size_t i = 0; i < _ptr_names.size(); i++){
      /**
        Maior gambiarra da minha vida
        Pode dar muita merda manipular tudo desse jeito
        Mas eu queria dificultar e usar char* e não string xD
      
        O libconfig aceita somente string infelizmente ele não aceita c_str :(
        Então esse buffer será apenas para armazenar o valor e depois vou copiar para
        Um c_str
      */
      std::string _buffer;
      
      if(!_libconfig->lookupValue(_ptr_names[i], _buffer)){
        std::cerr << RED "VAR FAILED: ( " NC << _ptr_names[i] << RED " )" NC << '\n';
        throw caroline::caroexception(CONFIGURATION_VAR_FAILED); 
      }
      /** Sim, eu uso malloc no C++ ~:) Não deveria mas eu uso */
      *_ptr_ref[i] = static_cast<char*>(malloc(std::strlen(_buffer.c_str()) + 1));
      
      if(*_ptr_ref[i] == nullptr){
        throw caroline::caroexception(MEMORY_ALLOCATION_ERROR);
      }
      
      /** Por fim copiando o buffer para o char* */
      std::strcpy(*_ptr_ref[i], _buffer.c_str());

      configured = true;
    }
  }

  catch(caroline::caroexception& _runtime_error){
    _runtime_error.getAll();
    exit(_runtime_error.getErrorCode());
  }

  catch(libconfig::ParseException& _paex){
    std::cerr << RED "ERROR: " NC "Parse error in config file " GREEN << _paex.getFile() << NC "! " RED << _paex.getError() << NC " line " RED << _paex.getLine() << NC << '\n';
    exit(EXIT_FAILURE);
  }
}

caroline::options::~options() noexcept{
  std::vector<char**> _ptr = {&source_dir, &fakeroot_dir, &cflags, &cxxflags, &jobs};

  for(size_t i = 0; i < _ptr.size(); i++){
    std::free(*_ptr[i]);
    *_ptr[i] = nullptr;
  }
}

const char* caroline::configuration::getSource_dir() const noexcept{
  return option->source_dir;
}

const char* caroline::configuration::getFakeroot_dir() const noexcept{
  return option->fakeroot_dir;
}

const char* caroline::configuration::getCflags() const noexcept{
  return option->cflags;
}

const char* caroline::configuration::getCxxflags() const noexcept{
  return option->cxxflags;
}

const char* caroline::configuration::getJobs() const noexcept{
  return option->jobs;
}
