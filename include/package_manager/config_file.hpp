//==========================================|
//   FILE: config_file.hpp                  |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef CONFIG_FILE_HPP
#define CONFIG_FILE_HPP

#include <cstddef>
#include <iostream>
#include <libconfig.h++>
#include <vector>

#include "../utils/smartpointer.hpp"
#include "../utils/exception.hpp"
#include "../utils/color.hpp"
#include "const_var.hpp"

struct lines{
  static const char* source;
  static const char* fakeroot;
  static const char* cflags;
  static const char* cxxflags;
  static const char* jobs;
};

typedef class config_file{
private:
  smt_ptr<struct lines> lines;
public:
  config_file(){
    smt_ptr<libconfig::Config> libconfig;
    
    const std::vector<const char*> config_name = {"source_dir", "fakeroot", "cflags", "cxxflags", "jobs"};
    std::vector<const char*> config_ptr = {lines->source, lines->fakeroot, lines->cflags, lines->cxxflags, lines->jobs};

    try{
      libconfig->readFile(CONFIG_FILE_LOC);
      for(size_t i = 0; i < config_name.size(); i++){
        if(!libconfig->lookupValue(config_name[i], config_ptr[i])){
          throw caroexception(CONFIGURATION_VAR_EMPTY, CONFIG_FILE_LOC, config_name[i]);
        }
      }
    }

    catch(caroexception& runtime_error){
      std::cout << RED "ERROR: " NC << runtime_error.what() << ' ' << runtime_error.what_extra() << ' ' << GREEN << runtime_error.getFile() << NC << "\nError code: " << runtime_error.getErrorCode() << '\n';
      exit(CONFIGURATION_VAR_EMPTY);
    }
  }

  ~config_file(){
    lines.free();
  }

  const char* getSourceDir() const{
    return lines->source;
  }

  const char* getFakerootDir() const{
    return lines->fakeroot;
  }

  const char* getCflags() const{
    return lines->cflags;
  }

  const char* getCxxflags() const{
    return lines->cxxflags;
  }

  const char* getJobs() const{
    return lines->jobs;
  }

}cfg;

#endif
