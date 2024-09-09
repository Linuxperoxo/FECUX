#include <cstdlib>

#include "../include/config.hpp"
#include "../include/managerobj.hpp"
#include "../include/integrity.hpp"
#include "../include/package.hpp"

int main(int argc, char** argv){
  fecux::main::config* _config = static_cast<fecux::main::config*>(std::malloc(sizeof(fecux::main::config)));  
  fecux::main::package* _package = static_cast<fecux::main::package*>(std::malloc(sizeof(fecux::main::package)));
  
  make_obj<fecux::main::config>(_config); fecux::tools::runtime::integrity::verify_dirs(_config);
  make_obj<fecux::main::package>(_package, "neofetch");

  expurg_obj(_package);
  expurg_obj(_config);
  
  std::free(_package);
  std::free(_config);

  return 0;
}

