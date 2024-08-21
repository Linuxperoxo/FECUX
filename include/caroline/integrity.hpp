//==========================================|
//   FILE: integrity.hpp                    |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef INTEGRITY_HPP
#define INTEGRITY_HPP

#include "config.hpp"

namespace caroline{

class integrity{
public:
  static void check_all(const caroline::configuration* configuration);
  static void check_config_file();
  static void check_dirs(const caroline::configuration* configuration);
  static int genConfigFile();
};

}

#endif
