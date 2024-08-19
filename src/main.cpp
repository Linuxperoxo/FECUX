#include <iostream>

#include "../include/caroline/config.hpp"

int main(){
  smt_ptr<caroline::configuration> config;
  std::cout << config->getSource_dir() << '\n';
  std::cout << config->getFakeroot_dir() << '\n';
  std::cout << config->getCflags() << '\n';
  std::cout << config->getCxxflags() << '\n';
  std::cout << config->getJobs() << '\n';
  return 0;
}
