//==========================================|
//   FILE: integrity.hpp                    |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef INTEGRITY_HPP
#define INTEGRITY_HPP

namespace caroline{

class integrity{
public:
  //static int check_all();
  static void check_config_file();
  //static int check_dirs();
  static int genConfigFile();
};

}

#endif
