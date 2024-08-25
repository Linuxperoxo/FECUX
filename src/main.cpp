//==========================================|
//   FILE: main.cpp                         |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstdlib>
#include <new>

#include "../include/caroline/config.hpp"
#include "../include/caroline/integrity.hpp"
#include "../include/caroline/package.hpp"

int main(int argc, char* argv[]){
  void* _raw_configuration = malloc(sizeof(caroline::configuration)); 
  
  caroline::configuration* _configuration = new (_raw_configuration) caroline::configuration();
    
  caroline::integrity::check_dirs(*_configuration);

  void* _raw_package = malloc(sizeof(caroline::package));

  caroline::package* _package = new(_raw_package) caroline::package("neofetch");

  _package->~package();

  std::free(_raw_package);

  _configuration->~configuration();
  
  std::free(_raw_configuration);

  return 0;
}
