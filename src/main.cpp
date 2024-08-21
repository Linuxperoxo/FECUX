#include <iostream>

#include "../include/caroline/config.hpp"
#include "../include/caroline/integrity.hpp"

int main(const int argc, const char* argv[]){
  caroline::integrity::check_config_file();
  
  smt_ptr<caroline::configuration> configuration;

  caroline::integrity::check_dirs(configuration.getPtr());
  
  std::cout << configuration->getSource_dir() << '\n';
  std::cout << configuration->getFakeroot_dir() << '\n';
  std::cout << configuration->getCflags() << '\n';
  std::cout << configuration->getCxxflags() << '\n';
  std::cout << configuration->getJobs() << '\n';
  return 0;
}
