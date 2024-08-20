#include <iostream>

#include "../include/caroline/config.hpp"

int main(const int argc, const char* argv[]){
  smt_ptr<caroline::configuration> configuration;
  std::cout << configuration->getSource_dir();
  return 0;
}
