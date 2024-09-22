#include "../include/fecux/integrity.hpp"
#include "../include/fecux/package.hpp"

int main(int argc, char** argv){
  fecux::main::integrity::check_health();
  fecux::main::managerPackage::add_package("neofetch");
  return 0;
}
