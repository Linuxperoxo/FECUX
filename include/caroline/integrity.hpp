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
  static void check_config();
  static void check_dirs(const caroline::configuration& _configuration_buffer);
  static int genConfigFile() noexcept;
}; 

}

#endif
