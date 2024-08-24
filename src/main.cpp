#include <cstdlib>
#include <iostream>

#include "../include/caroline/config.hpp"

int main(int argc, char* argv[]){
  void* _raw_configuration = malloc(sizeof(caroline::configuration)); 
  
  caroline::configuration* _configuration = new (_raw_configuration) caroline::configuration();
  
  std::cout << _configuration->source_dir() << '\n'; 
  std::cout << _configuration->fakeroot_dir() << '\n';
  std::cout << _configuration->cflags() << '\n';
  std::cout << _configuration->cxxflags() << '\n';
  std::cout << _configuration->jobs() << '\n';
  
  _configuration->~configuration();
  
  std::cout << "PLACEMENT NEW: " << _configuration << '\n';
  std::cout << "ADDRESS ALLOC: " << _raw_configuration << '\n';

  std::free(_configuration);

  return 0;
}
