#include <cstdlib>
#include <iostream>

#include "../include/config.hpp"

int main(int argc, char** argv){
  fecux::main::config* _config = static_cast<fecux::main::config*>(std::malloc(sizeof(fecux::main::config)));

//  make_obj<fecux::main::config>(&*_config);
//  expurg_obj(&*_config);

  fecux::utils::string _sla = "sla";
  fecux::utils::string _outro;
  _outro = _sla;

  std::cout << *_outro <<'\n';

  std::free(&*_config);

  return 0;
}
