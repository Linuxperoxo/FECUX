#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <new>

#include "../include/caroline/config.hpp"

int main(int argc, char* argv[]){
  caroline::configuration* configuration = static_cast<caroline::configuration*>(malloc(sizeof(caroline::configuration)));
  
  new (configuration) caroline::configuration();
  
  std::cout << configuration->source_dir() << '\n'; 
  std::cout << configuration->fakeroot_dir() << '\n';
  std::cout << configuration->cflags() << '\n';
  std::cout << configuration->cxxflags() << '\n';
  std::cout << configuration->jobs() << '\n';
  
//  std::free(configuration);

  return 0;
}
