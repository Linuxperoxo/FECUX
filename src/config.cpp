#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <libconfig.h++>
#include <iostream>

#include "../include/fecux/config.hpp"
#include "../include/fecux/exception.hpp"
#include "../include/fecux/vars.hpp"
#include "../include/fecux/files.hpp"
#include "../include/mem/managerobj.hpp"

#define OPTIONS_SIZE 5

fecux::main::config::config() noexcept
  : _options_struct(nullptr){
  try{
    _options_struct = verify();
  }

  catch(fecux::tools::exception& _runtime_error){
    std::cout << RED << "ERROR: " << NC << _runtime_error.what() << '\n';
    exit(_runtime_error.error_code());
  }

  catch(libconfig::ParseException& _paex){
    std::cout << RED << "ERROR: " << NC << _paex.what() << '\n';
    exit(EXIT_FAILURE);
  }
}

fecux::main::config::~config() noexcept{
  if(_options_struct != nullptr){
    expurg_obj(&*_options_struct);
    std::free(&*_options_struct);
  }
}

fecux::main::config::options* fecux::main::config::verify() const{
  if(!fecux::tools::files::is_file(CONFIG_FILE)){
    throw fecux::tools::exception(CONFIG_FILE_NOT_FOUND);
  }

  libconfig::Config* _libconfig = static_cast<libconfig::Config*>(std::malloc(sizeof(libconfig::Config)));
  options* _options = static_cast<options*>(std::malloc(sizeof(options)));
  fecux::utils::string** _string_vec = static_cast<fecux::utils::string**>(std::malloc(sizeof(fecux::utils::string) * OPTIONS_SIZE));
  char** _options_name = static_cast<char**>(std::malloc(sizeof(char*) * OPTIONS_SIZE));

  if(_libconfig == nullptr || _options == nullptr || _string_vec == nullptr || _options_name == nullptr){
    throw fecux::tools::exception(MEMORY_ALLOC_ERROR);
  }
  make_obj<libconfig::Config>(&*_libconfig);
  make_obj<options>(&*_options);

  _libconfig->readFile(CONFIG_FILE);

  std::strcpy(_options_name[0], "source_dir");
  std::strcpy(_options_name[1], "fakeroot_dir");
  std::strcpy(_options_name[2], "cflags");
  std::strcpy(_options_name[3], "cxxflags");
  std::strcpy(_options_name[4], "jobs");

  _string_vec[0] = &_options->source_dir;
  _string_vec[1] = &_options->fakeroot_dir;
  _string_vec[2] = &_options->cflags;
  _string_vec[3] = &_options->cxxflags;
  _string_vec[4] = &_options->jobs;

  std::string _buffer;

  for(size_t i = 0; i < OPTIONS_SIZE; i++){
    if(!_libconfig->lookupValue(_options_name[i], _buffer) || _buffer.empty()){
      expurg_obj(&*_libconfig);
      expurg_obj(&*_options);

      std::free(&*_libconfig);
      std::free(&*_options);
      std::free(&*_string_vec);
      std::free(&*_options_name);

      fecux::utils::string _error = "Error when trying to load the option -> ";
      _error = _error + RED + _buffer.c_str() + NC + " Check file -> " + RED + CONFIG_FILE + NC;
      throw fecux::tools::exception(_error, FAILED_LOAD_OPTION);
    }
    *_string_vec[i] = _buffer.c_str();
  }
  return &*_options;
}
