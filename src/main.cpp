#include <cstdlib>

#include "../include/config.hpp"
#include "../include/managerobj.hpp"

int main(int argc, char** argv){
  fecux::main::config* _config = static_cast<fecux::main::config*>(std::malloc(sizeof(fecux::main::config)));  

  make_obj<fecux::main::config>(&*_config);
  expurg_obj(&*_config);
  
  std::free(&*_config);

  return 0;
}
