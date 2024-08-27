//==========================================|
//   FILE: config.cpp                       |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstddef>
#include <cstdlib>
#include <libconfig.h++>
#include <string>
#include <cstring>

#include "../include/caroline/config.hpp"
#include "../include/extra/caroexception.hpp"
#include "../include/caroline/vars.hpp"
#include "../include/caroline/integrity.hpp"

char* caroline::options::source_dir = nullptr;
char* caroline::options::fakeroot_dir = nullptr;
char* caroline::options::cflags = nullptr;
char* caroline::options::cxxflags = nullptr;
char* caroline::options::jobs = nullptr;

bool caroline::options::configured = false;

caroline::options::options(){
  try{
    if(configured){
      return;
    }

    caroline::integrity::check_config();

    const char* _names[] = {"source_dir", "fakeroot_dir", "cflags", "cxxflags", "jobs"};
    char** _ptrs[] = {&source_dir, &fakeroot_dir, &cflags, &cxxflags, &jobs};

    void* _raw_libconfig = malloc(sizeof(libconfig::Config));
    if(_raw_libconfig == nullptr){
      throw caroline::caroex(MEMORY_ALLOCATION_ERROR);
    }

    libconfig::Config* _libconfig = new(_raw_libconfig) libconfig::Config();
    _libconfig->readFile(CONFIG_FILE);

    for(size_t i = 0; i < sizeof(_names) / sizeof(_names[0]); i++){
      std::string _buffer;
      _libconfig->lookupValue(_names[i], _buffer);
      *_ptrs[i] = static_cast<char*>(malloc(std::strlen(_buffer.c_str()) + 1));
      if(*_ptrs[i] == nullptr){
        for(size_t k = 0; k < i; k++){
          std::free(*_ptrs[i]);
        }
        _libconfig->~Config();
        std::free(_raw_libconfig);
        throw caroline::caroex(MEMORY_ALLOCATION_ERROR);
      }
      std::strcpy(*_ptrs[i], _buffer.c_str());
    }
    _libconfig->~Config();
    std::free(_raw_libconfig);  
    configured = true;
  }

  catch(caroline::caroex& _runtime_error){
    _runtime_error.all();
    exit(_runtime_error.errorCode());
  }
}

caroline::options::~options() noexcept{
  char** ptrs[] = {&source_dir, &fakeroot_dir, &cflags, &cxxflags, &jobs};

  for(const auto& ptr : ptrs){
    std::free(*ptr);
    *ptr = nullptr;
  }
}

caroline::configuration::configuration()
  : _option(nullptr){

  try{
    _option = static_cast<options*>(malloc(sizeof(options)));
    if(_option == nullptr){
      throw caroline::caroex(MEMORY_ALLOCATION_ERROR);
    }
    new(_option) options();
  } 

  catch(caroline::caroex& _runtime_error){
    _runtime_error.all();
    exit(_runtime_error.errorCode());
  }
}

caroline::configuration::~configuration() noexcept{
  _option->~options();
  std::free(_option);
}

const char* caroline::configuration::source_dir() const noexcept{
  return _option->source_dir;
}

const char* caroline::configuration::fakeroot_dir() const noexcept{
  return _option->fakeroot_dir;
} 

const char* caroline::configuration::cflags() const noexcept{
  return _option->cflags;
}

const char* caroline::configuration::cxxflags() const noexcept{
  return _option->cxxflags;
}

const char* caroline::configuration::jobs() const noexcept{
  return _option->jobs;
}
