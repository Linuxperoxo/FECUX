#ifndef CONFIG_FILE_HPP
#define CONFIG_FILE_HPP

#include <libconfig.h++>
#include <vector>

#include "smartpointer.hpp"
#include "../package_manager/const_var.hpp"

struct lines{
  static const char* sync;
  static const char* cflags;
  static const char* cxxflags;
  static const char* jobs;
};

class config_file{
private:
  smt_ptr<struct lines> lines;
public:
  config_file(){
    smt_ptr<libconfig::Config> libconf;

    const std::vector<const char*> var_names = {"sync", "cflags", "cxxflags", "jobs"}; 
    std::vector<const char*> var_ptr = {lines->sync, lines->cflags, lines->cxxflags, lines->jobs};

    try{
      libconf->readFile(CONFIG_FILE_LOC);

      for(size_t i = 0; i < var_names.size(); i++){
        if(!libconf->lookupValue(var_names[i], var_ptr[i])){
          
        }
      }
    }
  }

  ~config_file(){
    lines.free();
  }

  const char* getSync() const{
    return lines->sync;
  }

  const char* getCflags() const{
    return lines->sync;
  }

  const char* getCxxflags() const{
    return lines->cxxflags;
  }

  const char* getJobs() const{
    return lines->jobs;
  }
}; 

#endif
