#include <cstdlib>
#include <iostream>

#include "../include/caroline/config.hpp"
#include "../include/caroline/integrity.hpp"

int main(int argc, char* argv[]){
  void* _raw_configuration = malloc(sizeof(caroline::configuration)); 
  
  caroline::configuration* _configuration = new (_raw_configuration) caroline::configuration();
    
  caroline::integrity::check_dirs(*_configuration);

  _configuration->~configuration();
  
  std::free(_configuration);

  return 0;
}
