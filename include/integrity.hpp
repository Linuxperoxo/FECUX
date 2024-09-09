//==========================================|
//   FILE: integrity.hpp                    |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef __INTEGRITY_HPP__
#define __INTEGRITY_HPP__

#include "config.hpp"

namespace fecux{
  namespace tools{
    namespace runtime{
      class integrity{
      private:
        integrity()                            = delete;
        integrity(const integrity&)            = delete;
        integrity(integrity&&)                 = delete;
        integrity& operator=(const integrity&) = delete;
        integrity& operator=(integrity&&)      = delete;
        
        static char** read_file(const char** _names, const size_t& _element_size, const char* _file);
      public:
        static void verify_dirs(const fecux::main::config* _config) noexcept;
        static char** verify_config();
        static char** verify_infos(const char* _info_file);
      };
    }
  }
}

#endif
