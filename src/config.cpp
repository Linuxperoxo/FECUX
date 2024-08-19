#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <libconfig.h++>
#include <vector>

#include "../include/caroline/config.hpp"
#include "../include/caroline/const.hpp"
#include "../include/utils/color.hpp"
#include "../include/utils/files.hpp"
#include "../include/utils/caroexception.hpp"

char* caroline::options::source_dir = nullptr;
char* caroline::options::fakeroot_dir = nullptr;
char* caroline::options::cflags = nullptr;
char* caroline::options::cxxflags = nullptr;
char* caroline::options::jobs = nullptr;

bool caroline::options::configured = false;

caroline::options::options(){
  smt_ptr<libconfig::Config> libconfig;

  std::vector<const char*> options_name = {"source_dir", "fakeroot_dir", "cflags", "cxxflags", "jobs"};
  std::vector<char**> options_ptr = {&source_dir, &fakeroot_dir, &cflags, &cxxflags, &jobs};

  try{
    if(configured){
      return;
    }

    if(!files::is_file(CONFIG_FILE)){
      throw caroline::caroexception(CONFIG_FILE_NOT_FOUND);
    }

    libconfig->readFile(CONFIG_FILE);

    for(size_t i = 0; i < options_name.size(); i++){
      // Maior gambiarra da minha vida
      // Pode dar muita merda manipular tudo desse jeito
      // Mas eu queria usar char* e não string xD
      std::string buffer;
      if(!libconfig->lookupValue(options_name[i], buffer)){
        throw caroline::caroexception(CONFIGURATION_VAR_FAILED); 
      }
      // Sim, eu uso malloc no C++ ~:) Não deveria mas eu uso
      *options_ptr[i] = static_cast<char*>(malloc(buffer.length() + 1));
      if(*options_ptr[i] == nullptr){
        throw caroline::caroexception(MEMORY_ALLOCATION_ERROR);
      }
      // Por fim copiando o buffer para o char*
      std::strcpy(*options_ptr[i], buffer.c_str());
    }
    configured = true;
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

caroline::options::~options(){
  std::vector<char**> clean_ptr = {&source_dir, &fakeroot_dir, &cflags, &cxxflags, &jobs};

  for(const auto& ptr : clean_ptr){
    std::free(*ptr);
    *ptr = nullptr;
  }
}

caroline::configuration::configuration() : options_struct(){
  std::cout << "configuration classe\n";
}

const char* caroline::configuration::getSource_dir() const noexcept{
  return options_struct->source_dir;
}

const char* caroline::configuration::getFakeroot_dir() const noexcept{
  return options_struct->fakeroot_dir;
}

const char* caroline::configuration::getCflags() const noexcept{
  return options_struct->cflags;
}

const char* caroline::configuration::getCxxflags() const noexcept{
  return options_struct->cxxflags;
}

const char* caroline::configuration::getJobs() const noexcept{
  return options_struct->jobs;
}
