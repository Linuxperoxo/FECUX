#include "config.hpp"
#include "../utils/smartpointer.hpp"

class caroline{
private:
  smt_ptr<config_file> config; 
public:
  explicit caroline();
  
  int check_dirs();
};
