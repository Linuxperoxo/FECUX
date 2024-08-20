//==========================================|
//   FILE: config.cpp                       |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstdlib>
#include <vector>
#include <cstring>
#include <string>
#include <libconfig.h++>

#include "../include/caroline/config.hpp"
#include "../include/caroline/carolinevars.hpp"

char* caroline::options::source_dir = nullptr;
char* caroline::options::fakeroot_dir = nullptr;
char* caroline::options::cflags = nullptr;
char* caroline::options::cxxflags = nullptr;
char* caroline::options::jobs = nullptr;

bool caroline::options::configured = false;

caroline::options::options() noexcept{
  smt_ptr<libconfig::Config> _libconfig;

  std::vector<const char*> _ptr_names = {"source_dir", "fakeroot_dir", "cflags", "cxxflags", "jobs"};
  std::vector<char**> _ptr_ref = {&source_dir, &fakeroot_dir, &cflags, &cxxflags, &jobs};

  if(configured){
    return;
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
      
    _libconfig->lookupValue(_ptr_names[i], _buffer);
      
    /** Sim, eu uso malloc no C++ ~:) Não deveria mas eu uso */
    *_ptr_ref[i] = static_cast<char*>(malloc(std::strlen(_buffer.c_str()) + 1));
         
    /** Por fim copiando o buffer para o char* */
    std::strcpy(*_ptr_ref[i], _buffer.c_str());
    configured = true;
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
