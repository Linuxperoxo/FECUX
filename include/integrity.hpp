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
        integrity() = delete;
        integrity(const integrity&)            = delete;
        integrity(integrity&&)                 = delete;
        integrity& operator=(const integrity&) = delete;
        integrity& operator=(integrity&&)      = delete;
      public:
        static void verify_dirs(const fecux::main::config* _config) noexcept;
      };
    }
  }
}

#endif
