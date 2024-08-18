//==========================================|
//   FILE: caroline.hpp                     |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include "config.hpp"
#include "../utils/smartpointer.hpp"

class caroline{
private:
  smt_ptr<config_file> config; 
public:
  explicit caroline();
  ~caroline() = default;
  
  int check_dirs();
};
